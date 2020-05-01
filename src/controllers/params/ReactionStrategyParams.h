#ifndef REACTION_STRATEGY_PARAMS_H
#define REACTION_STRATEGY_PARAMS_H

#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class ReactionStrategyParams {

	private:
		// Params
		Real minAgreementPercentage;
		int minDurationTicks;

	public:
		// Constructors
		ReactionStrategyParams();

		// Getters
		Real getMinAgreementPercentage() const;
		int getMinDurationTicks() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif