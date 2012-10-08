#include "UnixInjector.h"

#include <stdlib.h>

UnixInjector::UnixInjector(const QString& libraryPath, QObject* parent):
    Injector(libraryPath, parent),
    process_(NULL) {
}

void UnixInjector::startAndAttach(const QString& application, const QStringList& arguments, const QString& workingDirectory) {
    // Clean up old process first
    if (process_ != NULL) {
        delete process_;
    }

    process_ = new QProcess(this);

    connect(process_, SIGNAL(finished(int, QProcess::ExitStatus)), SIGNAL(finished(int)));

    // TODO LD_PRELOAD with setenv
    //setenv();

    process_->setWorkingDirectory(workingDirectory);
    process_->start(application, arguments);
}
