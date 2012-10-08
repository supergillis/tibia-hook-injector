#include "Initializer.h"
#include "Injector.h"

#ifdef Q_OS_WIN
#include "WindowsInjector.h"
#define PlatformInjector WindowsInjector
#endif

Initializer::Initializer(const QString& libraryPath, const QString& tibiaPath, const QString& workingDirectory, QObject* parent):
	QObject(parent),
	libraryPath_(libraryPath),
	tibiaPath_(tibiaPath),
    workingDirectory_(workingDirectory) {
}

void Initializer::run() {
	Injector* injector = new PlatformInjector(libraryPath_);
    injector->startAndAttach(tibiaPath_, QStringList(), workingDirectory_);

    connect(injector, SIGNAL(finished(int)), SIGNAL(finished()));
}
