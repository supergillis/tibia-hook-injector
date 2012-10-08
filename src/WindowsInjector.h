#ifndef WINDOWSINJECTOR_H
#define WINDOWSINJECTOR_H

#include "Injector.h"

#include <QProcess>
#include <QTimer>

class WindowsInjector: public Injector {
	Q_OBJECT

public:
	WindowsInjector(const QString& libraryPath, QObject* parent = 0);

    void startAndAttach(const QString& application, const QStringList& arguments, const QString& workingDirectory = QString());
	void attach(Q_PID processId);

private slots:
	void attachToSpawnedProcess();

private:
	QProcess* process_;
	QTimer* attachTimer_;
};

#endif
