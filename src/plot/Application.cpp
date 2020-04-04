#include "Application.h"

int main(int argc, char **argv) {
	QApplication application(argc, argv);

	parseOptions(argc, argv);

	MainWindow mainWindow(QString(fileName.c_str()), maxGraphs, experiment, maxExperiments, gateGrippingRobots, temperatureSensingRobots);
	mainWindow.show();

	return application.exec();
}

void printError(string command, string message) {
	cerr << command << ": " << message << endl
	<< "Try '" << command << " --help' for more information." << endl;
	exit(EXIT_FAILURE);
}

void parseOptions(int argc, char **argv) {
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
				cout << "Usage: " << argv[0] << " [OPTIONS] FILE" << endl
				<< endl
				<< "-h     | --help                              display this help message" << endl
				<< "-a NUM | --max-graphs NUM                    the amount of graphs to plot" << endl
				<< "-e NUM | --experiment NUM                    the current experiment number" << endl
				<< "-m NUM | --max-experiments NUM               the total amount of experiments" << endl
				<< "-g NUM | --gate-gripping-robots NUM          the amount of gate gripping robots" << endl
				<< "-t NUM | --temperature-sensing-robots NUM    the amount of temperature sensing robots" << endl;
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
				printError(argv[0], "Missing argument for option '" + string(argv[optind-1]) + "'.");
				break;
			}
			case '?': {
				printError(argv[0], "Unrecognized option '" + string(argv[optind-1]) + "'.");
				break;
			}
		}
	}

	// Handle non-option arguments
	if(optind < argc) {
		fileName = argv[optind];
	} else {
		printError(argv[0], "Missing file operand.");
	}
}