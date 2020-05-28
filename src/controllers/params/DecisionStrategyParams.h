#ifndef DECISION_STRATEGY_PARAMS_H
#define DECISION_STRATEGY_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class DecisionStrategyParams {

	private:
		// Params
		string mode;
		bool checkForFireCriticality;

	public:
		// Constructors
		DecisionStrategyParams();

		// Getters
		const string& getMode() const;
		bool getCheckForFireCriticality() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif