#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextStream>

class Initializer: public QObject {
	Q_OBJECT

public:
    Initializer(const QString& libraryPath, const QString& tibiaPath, const QString& workingDirectory, QObject* parent = 0);

	virtual ~Initializer() {}

public slots:
	void run();

signals:
	void finished();

private:
	QString libraryPath_;
	QString tibiaPath_;
    QString workingDirectory_;
};

#endif
