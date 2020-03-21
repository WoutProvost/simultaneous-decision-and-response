#include "PlotApplication.h"
#include "MainWindow.h"

void PlotApplication::start() {
	// int argc;
	// char **argv;
	// QApplication application(argc, argv);
	// MainWindow mainWindow;
	// mainWindow.show();
	// application.exec();
}

int main(int argc, char **argv) {
	QApplication application(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return application.exec();
}