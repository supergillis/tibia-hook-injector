#ifndef UNIXINJECTOR_H
#define UNIXINJECTOR_H

#include "Injector.h"

#include <QProcess>

class UnixInjector: public Injector {
    Q_OBJECT

public:
    UnixInjector(const QString& libraryPath, QObject* parent = 0);

    void startAndAttach(const QString& application, const QStringList& arguments, const QString& workingDirectory = QString());
    void attach(Q_PID processId) {};

private:
    QProcess* process_;
};

#endif
