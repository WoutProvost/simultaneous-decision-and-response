#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define THRESHOLD	0.8

int main(int argc, char *argv[]) {
	int finishedExperiments = 0;
	int finalDecisions[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
	int finalResponses[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
	int earliestDecisions[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result
	int earliestResponses[3] = {0, 0, 0}; // Inconclusive, correct result, incorrect result

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

				// Decision (only use first occurence)
				data >> c >> decisionData[0] >> c >> decisionData[1] >> c >> decisionData[2];
				if(earliestDecisionTime[1] == 0 && decisionData[1] >= THRESHOLD) {
					earliestDecisionTime[1] = lineCount;
				}
				if(earliestDecisionTime[2] == 0 && decisionData[2] >= THRESHOLD) {
					earliestDecisionTime[2] = lineCount;
				}
				earliestDecisionTime[0] = 36000;

				// Response (only use first occurence)
				data >> c >> responseData[0] >> c >> responseData[1] >> c >> responseData[2];
				if(earliestResponseTime[1] == 0 && responseData[1] >= THRESHOLD) {
					earliestResponseTime[1] = lineCount;
				}
				if(earliestResponseTime[2] == 0 && responseData[2] >= THRESHOLD) {
					earliestResponseTime[2] = lineCount;
				}
				earliestResponseTime[0] = 36000;

				// Final result
				if(prefix == "3.6e+06") {
					finishedExperiments++;

					// Decision
					if(decisionData[1] >= THRESHOLD) {
						finalDecisions[1]++;
						earliestDecisions[1] += earliestDecisionTime[1];
					} else if(decisionData[2] >= THRESHOLD) {
						finalDecisions[2]++;
						earliestDecisions[2] += earliestDecisionTime[2];
					} else {
						finalDecisions[0]++;
						earliestDecisions[0] += earliestDecisionTime[0];
					}

					// Response
					if(responseData[1] >= THRESHOLD) {
						finalResponses[1]++;
						earliestResponses[1] += earliestResponseTime[1];
					} else if(responseData[2] >= THRESHOLD) {
						finalResponses[2]++;
						earliestResponses[2] += earliestResponseTime[2];
					} else {
						finalResponses[0]++;
						earliestResponses[0] += earliestResponseTime[0];
					}
				}
			}
		}
		input.close();
	}

	double finalDecisionProbabilities[3] = {0.0, 0.0, 0.0};
	double finalResponseProbabilities[3] = {0.0, 0.0, 0.0};
	double earliestDecisionTimesteps[3] = {0.0, 0.0, 0.0};
	double earliestResponseTimesteps[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < 3; i++) {
		finalDecisionProbabilities[i] = static_cast<double>(finalDecisions[i])/finishedExperiments*100;
		finalResponseProbabilities[i] = static_cast<double>(finalResponses[i])/finishedExperiments*100;
		earliestDecisionTimesteps[i] = static_cast<double>(earliestDecisions[i])/finalDecisions[i];
		earliestResponseTimesteps[i] = static_cast<double>(earliestResponses[i])/finalResponses[i];
	}

	if(finishedExperiments == argc - 1) {
		cout << finishedExperiments << " results aggregated (threshold=" << THRESHOLD*100 << "%): " << endl
		<< "- Decision: T=" << finalDecisionProbabilities[1] << "% (" << earliestDecisionTimesteps[1] << "t)"
		<< ", F=" << finalDecisionProbabilities[2] << "% (" << earliestDecisionTimesteps[2] << "t), I=" << finalDecisionProbabilities[0] << "% (" << earliestDecisionTimesteps[0] << "t)" << endl
		<< "- Response: T=" << finalResponseProbabilities[1] << "% (" << earliestResponseTimesteps[1] << "t)"
		<< ", F=" << finalResponseProbabilities[2] << "% (" << earliestResponseTimesteps[2] << "t), I=" << finalResponseProbabilities[0] << "% (" << earliestResponseTimesteps[0] << "t)" << endl;
	}
	return 0;
}