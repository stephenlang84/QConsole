#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <libs/QConsole/qconsole.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	auto out = QConsole::qStdOut(&a);

	QConsole console;
	QObject::connect(&console, &QConsole::readyRead, [&](){
		auto data = console.read(console.bytesAvailable());
		out->write("Echo: " + data);
		if(data.contains("exit"))
			qApp->quit();
	});
	QObject::connect(&console, &QConsole::readChannelFinished,
					 qApp, &QCoreApplication::quit);
	if(!console.open()) {
		qCritical() << console.errorString();
		return EXIT_FAILURE;
	}
	out->write("Ready to go!\n");
	out->flush();
	return a.exec();
}
