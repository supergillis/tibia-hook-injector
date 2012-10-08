#include "WindowsInjector.h"

#include <QDebug>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

WindowsInjector::WindowsInjector(const QString& libraryPath, QObject* parent):
	Injector(libraryPath, parent),
	process_(NULL) {
}

void WindowsInjector::startAndAttach(const QString& application, const QStringList& arguments, const QString& workingDirectory) {
	// Clean up old process first
	if (process_ != NULL) {
		delete process_;
	}

    process_ = new QProcess(this);

	attachTimer_ = new QTimer(this);
	attachTimer_->setSingleShot(true);
	attachTimer_->setInterval(500);

	connect(attachTimer_, SIGNAL(timeout()), this, SLOT(attachToSpawnedProcess()));
	connect(process_, SIGNAL(started()), attachTimer_, SLOT(start()));
	connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), SIGNAL(finished(int)));

    process_->setWorkingDirectory(workingDirectory);
    process_->start(application, arguments);
}

void WindowsInjector::attachToSpawnedProcess() {
	if (process_->state() == QProcess::NotRunning) {
		qDebug() << "Failed to start process:" << process_->error();
	}
	else {
		attach(process_->pid());
	}
}

void WindowsInjector::attach(Q_PID processId) {
	wchar_t path[_MAX_PATH];
	const int pathLength = libraryPath().toWCharArray(path);
	path[pathLength] = 0;

    HMODULE library = ::LoadLibraryW(path);
    FARPROC hook = ::GetProcAddress(library, "hook_constructor");

	typedef void(*Installer)(HINSTANCE, DWORD);
	Installer installer = reinterpret_cast<Installer>(hook);
	(*installer)(library, processId->dwThreadId);
}
