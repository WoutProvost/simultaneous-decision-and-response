#ifndef REACTION_STRATEGY_PARAMS_H
#define REACTION_STRATEGY_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class ReactionStrategyParams {

	public:
		// Params
		Real minAgreementPercentage;
		int minDurationTicks;

		// Constructors
		ReactionStrategyParams();

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif