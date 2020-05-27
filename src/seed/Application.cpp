#include "Application.h"

int main(int argc, char *argv[]) {
	// Parse command line options and arguments
	parseOptions(argc, argv);

	// Set the srand value
	if(srandSeed == 0) {
		srandSeed = time(nullptr);
	}
	srand(srandSeed);

	size_t pos = inputFileName.find(".argos");
	if(pos != inputFileName.length() - 6) {
		printError("File extension '.argos' needed.");
	}
	
	for(int i = 0; i < amount; i++) {
		ifstream input(inputFileName);
		if(!input.is_open()) {
			printError("Error opening file '" + inputFileName + "'.");
		}

		string outputFileName(inputFileName.substr(0, pos) + "_" + to_string(i+1) + ".argos");
		ofstream output(outputFileName);
		if(!output.is_open()) {
			printError("Error opening file '" + outputFileName + "'.");
		}

		string logFileName = inputFileName.substr(0, inputFileName.length() - 6);
		size_t pos2 = logFileName.find_last_of('/');
		if(pos2 != string::npos) {
			logFileName = logFileName.erase(0, pos2 + 1);
		}

		string line;
		smatch logFileMatch;
		regex randomSeedRegex("random_seed\\s*=\\s*[\"']\\s*\\d*\\s*[\"']");
		regex logFileRegex("file\\s*=\\s*[\"']\\s*(.*?)\\s*[\"']");
		while(getline(input, line)) {
			line = regex_replace(line, randomSeedRegex, string("random_seed=\"") + to_string(rand()) + "\"");
			if(regex_search(line, logFileMatch, logFileRegex)) {
				string logFilePrefix;
				size_t pos3 = logFileMatch.str(1).find_last_of('/');
				if(pos3 != string::npos) {
					logFilePrefix = logFileMatch.str(1).substr(0, pos3 + 1);
				}
				line = regex_replace(line, logFileRegex, string("file=\"") + logFilePrefix + logFileName + "_" + to_string(i+1) + ".csv" + "\"");
			}
			output << line << endl;
		}
		input.close();
		output.close();
	}
	return 0;
}

void parseOptions(int argc, char **argv) {
	command = argv[0];

	static struct option options[] = {
		{"help", no_argument, NULL, 'h'},
		{"amount", required_argument, NULL, 'n'},
		{"srand", required_argument, NULL, 's'},
		{0, 0, 0, 0}
	};

	// A leading ':' disables printing error messages and returns ':' instead of '?' to indicate a missing option argument
	int option;
	while((option = getopt_long(argc, argv, ":hn:s:", options, NULL)) != -1) {
		switch(option) {
			case 'h': {
				cout << "Usage: " << command << " [options] [file]" << endl
				<< endl
				<< "Options:" << endl
				<< "  Mandatory arguments to long options are mandatory for short options too." << endl
				<< "  -h,  --help                              display this help message" << endl
				<< "  -n,  --amount=NUM                        the amount of files to generate (10 = default)" << endl
				<< "  -s,  --srand=NUM                         the value passed to srand (0 = time, 1 = default)" << endl
				<< endl
				<< "File:" << endl
				<< "  The source file used to generate one or more .argos files from." << endl;
				exit(EXIT_SUCCESS);
				break;
			}
			case 'n': {	
				amount = atoi(optarg);	
				break;	
			}
			case 's': {	
				srandSeed = atoi(optarg);	
				break;	
			}
			case ':': {
				printError("Missing argument for option '" + string(argv[optind-1]) + "'.");
				break;
			}
			case '?': {
				printError("Unrecognized option '" + string(argv[optind-1]) + "'.");
				break;
			}
		}
	}

	// Handle non-option arguments
	if(optind < argc) {
		inputFileName = argv[optind];
	} else {
		printError("Missing file operand.");
	}
}

void printError(string message) {
	cerr << command << ": " << message << endl
	<< "Try '" << command << " --help' for more information." << endl;
	exit(EXIT_FAILURE);
}