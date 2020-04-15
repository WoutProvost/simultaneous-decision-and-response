#ifndef VOTING_STRATEGY_PARAMS_H
#define VOTING_STRATEGY_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::string;

class VotingStrategyParams {

	public:
		// Params
		string mode;

		// Constructors
		VotingStrategyParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif