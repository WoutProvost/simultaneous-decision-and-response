#include "Application.h"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {	
	QApplication application(argc, argv);

	// Parse command line options and arguments
	parseOptions(argc, argv);

	// Create and show main window
	MainWindow mainWindow(fileName, maxGraphs, experiment, maxExperiments, gateGrippingRobots, temperatureSensingRobots);
	mainWindow.show();

	return application.exec();
}

void parseOptions(int argc, char **argv) {
	command = argv[0];

	static struct option options[] = {
		{"help", no_argument, NULL, 'h'},
		{"max-graphs", required_argument, NULL, 'a'},
		{"experiment", required_argument, NULL, 'e'},
		{"max-experiments", required_argument, NULL, 'm'},
		{"gate-gripping-robots", required_argument, NULL, 'g'},
		{"temperature-sensing-robots", required_argument, NULL, 't'},
		{0, 0, 0, 0}
	};

	// A leading ':' disables printing error messages and returns ':' instead of '?' to indicate a missing option argument
	int option;
	while((option = getopt_long(argc, argv, ":ha:e:m:g:t:", options, NULL)) != -1) {
		switch(option) {
			case 'h': {
				cout << "Usage: " << argv[0] << " [options] [file]" << endl
				<< endl
				<< "Options:" << endl
				<< "  Mandatory arguments to long options are mandatory for short options too." << endl
				<< "  -h,  --help                              display this help message" << endl
				<< "  -a,  --max-graphs=NUM                    the amount of graphs to plot" << endl
				<< "  -e,  --experiment=NUM                    the current experiment number" << endl
				<< "  -m,  --max-experiments=NUM               the total amount of experiments" << endl
				<< "  -g,  --gate-gripping-robots=NUM          the amount of gate gripping robots" << endl
				<< "  -t,  --temperature-sensing-robots=NUM    the amount of temperature sensing robots" << endl
				<< endl
				<< "File:" << endl
				<< "  With no file, or when file is -, read standard input." << endl;
				exit(EXIT_SUCCESS);
				break;
			}
			case 'a': {
				maxGraphs = atoi(optarg);
				break;
			}
			case 'e': {
				experiment = atoi(optarg);
				break;
			}
			case 'm': {
				maxExperiments = atoi(optarg);
				break;
			}
			case 'g': {
				gateGrippingRobots = atoi(optarg);
				break;
			}
			case 't': {
				temperatureSensingRobots = atoi(optarg);
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