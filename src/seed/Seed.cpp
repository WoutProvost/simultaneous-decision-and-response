#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " [amount] [file]" << endl;
		return 1;
	}

	string inputFileName(argv[2]);
	size_t pos = inputFileName.find(".argos");
	if(pos == string::npos) {
		cerr << "File extension '.argos' needed." << endl;
		return 1;
	}
	
	for(int i = 0; i < stoi(argv[1]); i++) {
		string outputFileName(inputFileName.substr(0, pos) + to_string(i+1) + ".argos");
		ifstream input(inputFileName);
		ofstream output(outputFileName);

		if(!input.is_open()) {
			cerr << "Error opening file '" << inputFileName << "'." << endl;
			return 1;
		}

		if(!output.is_open()) {
			cerr << "Error opening file '" << outputFileName << "'." << endl;
			return 1;
		}

		string line;
		regex randomSeedRegex("random_seed\\s*=\\s*[\"']\\s*\\d+\\s*[\"']");
		regex logFileRegex("log_file\\s*=\\s*[\"']\\s*.+?\\s*[\"']");
		while(getline(input, line)) {
			line = regex_replace(line, randomSeedRegex, string("random_seed=\"") + to_string(rand()) + "\"");
			line = regex_replace(line, logFileRegex, string("log_file=\"") + "../logs/log" + to_string(i+1) + ".csv" + "\"");
			output << line << endl;
		}
		input.close();
		output.close();
	}
	return 0;
}