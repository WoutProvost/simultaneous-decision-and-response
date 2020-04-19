#include "Application.h"
#include <iostream>
#include "MainWindow.h"
#include <getopt.h>

using std::cout;
using std::endl;
using std::cerr;

// General variables and constants
QString command;
QString fileName;

int main(int argc, char **argv) {	
	QApplication application(argc, argv);

	// Parse command line options and arguments
	parseOptions(argc, argv);

	// Create and show main window
	MainWindow mainWindow(fileName);
	mainWindow.show();

	return application.exec();
}

void parseOptions(int argc, char **argv) {
	command = argv[0];

	static struct option options[] = {
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};

	// A leading ':' disables printing error messages and returns ':' instead of '?' to indicate a missing option argument
	int option;
	while((option = getopt_long(argc, argv, ":he:m:", options, NULL)) != -1) {
		switch(option) {
			case 'h': {
				cout << "Usage: " << argv[0] << " [options] [file]" << endl
				<< endl
				<< "Options:" << endl
				<< "  Mandatory arguments to long options are mandatory for short options too." << endl
				<< "  -h,  --help                              display this help message" << endl
				<< endl
				<< "File:" << endl
				<< "  With no file, or when file is -, read standard input." << endl;
				exit(EXIT_SUCCESS);
				break;
			}
			case ':': {
				printError("Missing argument for option '" + QString(argv[optind-1]) + "'.");
				break;
			}
			case '?': {
				printError("Unrecognized option '" + QString(argv[optind-1]) + "'.");
				break;
			}
		}
	}

	// Handle non-option arguments
	if(optind < argc) {
		fileName = argv[optind];
	} else {
		fileName = "-";
	}
}

void printError(QString message) {
	cerr << command.toStdString() << ": " << message.toStdString() << endl
	<< "Try '" << command.toStdString() << " --help' for more information." << endl;
	exit(EXIT_FAILURE);
}