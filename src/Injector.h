#ifndef INJECTOR_H
#define INJECTOR_H

#include <QObject>
#include <QProcess>

class Injector: public QObject {
	Q_OBJECT

public:
	Injector(const QString& libraryPath, QObject* parent = 0):
		QObject(parent),
		libraryPath_(libraryPath) {}

	virtual ~Injector() {}

    virtual void startAndAttach(const QString& application, const QStringList& arguments, const QString& workingDirectory = QString()) = 0;
	virtual void attach(Q_PID processId) = 0;

	const QString& libraryPath() const { return libraryPath_; }

signals:
	void finished(int exitCode);

private:
	QString libraryPath_;
};

#endif
