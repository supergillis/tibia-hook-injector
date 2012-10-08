#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QTimer>

#include "Initializer.h"

int main(int argc, char** argv) {
	QCoreApplication application(argc, argv);

    QStringList arguments = QCoreApplication::arguments();

	if (arguments.length() < 3) {
        qDebug() << "usage: tibia-hook-injector --library <library-path> --tibia <executable> --directory <working-dir>";
		return 1;
	}

    QString libraryPath;
    QString tibiaPath;
    QString workingDirectory;
    for (int index = 0; index < arguments.length(); ++index) {
        if (arguments[index] == "--library") {
            libraryPath = arguments[++index];
        }
        else if (arguments[index] == "--tibia") {
            tibiaPath = arguments[++index];
        }
        else if (arguments[index] == "--directory") {
            workingDirectory = arguments[++index];
        }
    }

    if (libraryPath.isNull() || tibiaPath.isNull()) {
        qDebug() << "usage: tibia-hook-injector --library <library-path> --tibia <executable> --directory <working-dir>";
        return 2;
    }

    if (workingDirectory.isNull()) {
        // Initialize working directory
        workingDirectory = QFileInfo(tibiaPath).canonicalPath();
    }

    Initializer* initializer = new Initializer(libraryPath, tibiaPath, workingDirectory, &application);
    QObject::connect(initializer, SIGNAL(finished()), &application, SLOT(quit()));
    QTimer::singleShot(0, initializer, SLOT(run()));

	return application.exec();
}
