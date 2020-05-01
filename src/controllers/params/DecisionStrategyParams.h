#ifndef DECISION_STRATEGY_PARAMS_H
#define DECISION_STRATEGY_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class DecisionStrategyParams {

	public:
		// Params
		string mode;

		// Constructors
		DecisionStrategyParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif