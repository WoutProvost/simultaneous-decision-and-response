#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define THRESHOLD			0.8
#define THRESHOLD_MARGIN	0.05

int main(int argc, char *argv[]) {
	int finishedExperiments = 0;
	int finalDecisions[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
	int finalResponses[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
	int earliestDecisions = 0;
	int earliestResponses = 0;

	for(int arg = 1; arg < argc; arg++) {
		ifstream input(argv[arg]);
		if(!input.is_open()) {
			cerr << "Error opening file '" << argv[arg] << "'." << endl;
			exit(EXIT_FAILURE);
		}

		int lineCount = 0;
		int earliestDecisionTime[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
		int earliestResponseTime[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
		string line;
		while(getline(input, line)) {
			if(!line.empty() && line.rfind("#", 0) != 0 && line.rfind("!", 0) != 0 && line.rfind("0", 0)) {
				lineCount++;
				size_t pos = line.find_first_of(',');
				string prefix = line.substr(0, pos);
				line = line.erase(0, pos);
				stringstream data(line);
				char c;
				double decisionData[3];
				double responseData[3];

				// Decision
				data >> c >> decisionData[0] >> c >> decisionData[1] >> c >> decisionData[2];
				if(earliestDecisionTime[1] == 0 && decisionData[1] >= THRESHOLD) {
					earliestDecisionTime[1] = lineCount;
				} else if(earliestDecisionTime[1] != 0 && decisionData[1] < THRESHOLD - THRESHOLD_MARGIN) {
					earliestDecisionTime[1] = 0;
				}
				if(earliestDecisionTime[2] == 0 && decisionData[2] >= THRESHOLD) {
					earliestDecisionTime[2] = lineCount;
				} else if(earliestDecisionTime[2] != 0 && decisionData[2] < THRESHOLD - THRESHOLD_MARGIN) {
					earliestDecisionTime[2] = 0;
				}

				// Response
				data >> c >> responseData[0] >> c >> responseData[1] >> c >> responseData[2];
				if(earliestResponseTime[1] == 0 && responseData[1] >= THRESHOLD) {
					earliestResponseTime[1] = lineCount;
				} else if(earliestResponseTime[1] != 0 && responseData[1] < THRESHOLD - THRESHOLD_MARGIN) {
					earliestResponseTime[1] = 0;
				}
				if(earliestResponseTime[2] == 0 && responseData[2] >= THRESHOLD) {
					earliestResponseTime[2] = lineCount;
				} else if(earliestResponseTime[2] != 0 && responseData[2] < THRESHOLD - THRESHOLD_MARGIN) {
					earliestResponseTime[2] = 0;
				}

				// Final result
				if(prefix == "3.6e+06") {
					finishedExperiments++;

					// Decision
					if(decisionData[1] >= THRESHOLD) {
						finalDecisions[1]++;
						earliestDecisions += earliestDecisionTime[1];
					} else if(decisionData[2] >= THRESHOLD) {
						finalDecisions[2]++;
						earliestDecisions += earliestDecisionTime[2];
					} else {
						finalDecisions[0]++;
					}

					// Response
					if(responseData[1] >= THRESHOLD) {
						finalResponses[1]++;
						earliestResponses += earliestResponseTime[1];
					} else if(responseData[2] >= THRESHOLD) {
						finalResponses[2]++;
						earliestResponses += earliestResponseTime[2];
					} else {
						finalResponses[0]++;
					}
				}
			}
		}
		input.close();
	}

	double finalDecisionProbabilities[3] = {0.0, 0.0, 0.0};
	double finalResponseProbabilities[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < 3; i++) {
		finalDecisionProbabilities[i] = static_cast<double>(finalDecisions[i])/finishedExperiments*100;
		finalResponseProbabilities[i] = static_cast<double>(finalResponses[i])/finishedExperiments*100;
	}

	double earliestDecisionTimesteps = static_cast<double>(earliestDecisions)/(finalDecisions[1] + finalDecisions[2]);
	double earliestResponseTimesteps = static_cast<double>(earliestResponses)/(finalResponses[1] + finalResponses[2]);

	if(finishedExperiments == argc - 1) {
		cout.setf(std::ios::fixed);
		cout.precision(2);
		
		cout << finalDecisionProbabilities[1] << "%\t" << finalDecisionProbabilities[2] << "%\t" << finalDecisionProbabilities[0] << "%" << endl;
		cout << finalResponseProbabilities[1] << "%\t" << finalResponseProbabilities[2] << "%\t" << finalResponseProbabilities[0] << "%" << endl;

		// cout << earliestDecisionTimesteps << endl;
		// cout << earliestResponseTimesteps << endl;
	}
	return 0;
}