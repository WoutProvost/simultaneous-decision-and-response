#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define THRESHOLD			0.8		// Use 0.7 for multiple fires
#define CONVERGENCE_MARGIN	0.05

int main(int argc, char *argv[]) {
	int finishedExperiments = 0;
	int decisionOutcomes[3] = {0, 0, 0};
	int responseOutcomes[3] = {0, 0, 0};
	int decisionConvergenceTimeOutcome = 0;
	int responseConvergenceTimeOutcome = 0;

	for(int arg = 1; arg < argc; arg++) {
		double finalDecisionData[3] = {0.0, 0.0, 0.0};
		double finalResponseData[3] = {0.0, 0.0, 0.0};

		// Exit probability
		{
			ifstream input(argv[arg]);
			if(!input.is_open()) {
				cerr << "Error opening file '" << argv[arg] << "'." << endl;
				exit(EXIT_FAILURE);
			}

			string line;
			while(getline(input, line)) {
				if(!line.empty() && line.rfind("#", 0) != 0 && line.rfind("!", 0) != 0 && line.rfind("0", 0) != 0) {
					size_t pos = line.find_first_of(',');
					string prefix = line.substr(0, pos);

					if(prefix == "3.6e+06") {
						line = line.erase(0, pos);
						stringstream data(line);
						char c;
						finishedExperiments++;

						// Decision
						data >> c >> finalDecisionData[0] >> c >> finalDecisionData[1] >> c >> finalDecisionData[2];
						if(finalDecisionData[1] >= THRESHOLD) {
							decisionOutcomes[1]++;
						} else if(finalDecisionData[2] >= THRESHOLD) {
							decisionOutcomes[2]++;
						} else {
							decisionOutcomes[0]++;
						}

						// Response
						data >> c >> finalResponseData[0] >> c >> finalResponseData[1] >> c >> finalResponseData[2];
						if(finalResponseData[1] >= THRESHOLD) {
							responseOutcomes[1]++;
						} else if(finalResponseData[2] >= THRESHOLD) {
							responseOutcomes[2]++;
						} else {
							responseOutcomes[0]++;
						}
					}
				}
			}

			input.close();
		}

		// Time to convergence
		if(finalDecisionData[1] >= THRESHOLD || finalDecisionData[2] >= THRESHOLD || finalResponseData[1] >= THRESHOLD || finalResponseData[2] >= THRESHOLD) {
			ifstream input(argv[arg]);
			if(!input.is_open()) {
				cerr << "Error opening file '" << argv[arg] << "'." << endl;
				exit(EXIT_FAILURE);
			}

			int lineCount = 0;
			int decisionConvergenceTime = 0;
			int responseConvergenceTime = 0;

			string line;
			while(getline(input, line)) {
				if(!line.empty() && line.rfind("#", 0) != 0 && line.rfind("!", 0) != 0 && line.rfind("0", 0) != 0) {
					size_t pos = line.find_first_of(',');
					string prefix = line.substr(0, pos);
					line = line.erase(0, pos);
					stringstream data(line);
					char c;
					lineCount++;

					// Decision
					double decisionData[3];
					data >> c >> decisionData[0] >> c >> decisionData[1] >> c >> decisionData[2];
					double decisionDataToCompare = 0.0;
					double finalDecisionDataToCompare = 0.0;
					if(finalDecisionData[1] >= THRESHOLD) {
						decisionDataToCompare = decisionData[1];
						finalDecisionDataToCompare = finalDecisionData[1];
					} else if(finalDecisionData[2] >= THRESHOLD) {
						decisionDataToCompare = decisionData[2];
						finalDecisionDataToCompare = finalDecisionData[2];
					}
					if(decisionDataToCompare >= finalDecisionDataToCompare - CONVERGENCE_MARGIN && decisionDataToCompare <= finalDecisionDataToCompare + CONVERGENCE_MARGIN) {
						if(decisionConvergenceTime == 0) {
							decisionConvergenceTime = lineCount;							
						}
					} else {
						if(decisionConvergenceTime != 0) {
							decisionConvergenceTime = 0;
						}
					}

					// Response
					double responseData[3];
					data >> c >> responseData[0] >> c >> responseData[1] >> c >> responseData[2];
					double responseDataToCompare = 0.0;
					double finalResponseDataToCompare = 0.0;
					if(finalResponseData[1] >= THRESHOLD) {
						responseDataToCompare = responseData[1];
						finalResponseDataToCompare = finalResponseData[1];
					} else if(finalResponseData[2] >= THRESHOLD) {
						responseDataToCompare = responseData[2];
						finalResponseDataToCompare = finalResponseData[2];
					}
					if(responseDataToCompare >= finalResponseDataToCompare - CONVERGENCE_MARGIN && responseDataToCompare <= finalResponseDataToCompare + CONVERGENCE_MARGIN) {
						if(responseConvergenceTime == 0) {
							responseConvergenceTime = lineCount;
						}
					} else {						
						if(responseConvergenceTime != 0) {
							responseConvergenceTime = 0;
						}
					}
				}
			}

			if(finalDecisionData[1] >= THRESHOLD || finalDecisionData[2] >= THRESHOLD) {
				decisionConvergenceTimeOutcome += decisionConvergenceTime;
			}

			if(finalResponseData[1] >= THRESHOLD || finalResponseData[2] >= THRESHOLD) {
				responseConvergenceTimeOutcome += responseConvergenceTime;
			}

			input.close();
		}
	}

	double decisionExitProbabilities[3] = {0.0, 0.0, 0.0};
	double responseExitProbabilities[3] = {0.0, 0.0, 0.0};
	for(int i = 0; i < 3; i++) {
		decisionExitProbabilities[i] = static_cast<double>(decisionOutcomes[i])/finishedExperiments*100;
		responseExitProbabilities[i] = static_cast<double>(responseOutcomes[i])/finishedExperiments*100;
	}

	double averageDecisionConvergenceTime = static_cast<double>(decisionConvergenceTimeOutcome)/(decisionOutcomes[1] + decisionOutcomes[2]);
	double averageResponseConvergenceTime = static_cast<double>(responseConvergenceTimeOutcome)/(responseOutcomes[1] + responseOutcomes[2]);

	if(finishedExperiments == argc - 1) {
		cout.setf(std::ios::fixed);
		cout.precision(2);
		
		// Exit probability conclusive results
		// cout << (decisionExitProbabilities[1] + decisionExitProbabilities[2]) << "%" << endl;
		// cout << (responseExitProbabilities[1] + responseExitProbabilities[2]) << "%" << endl;

		// Time to convergence conclusive results
		cout << averageDecisionConvergenceTime << endl;
		cout << averageResponseConvergenceTime << endl;
	}
	return 0;
}