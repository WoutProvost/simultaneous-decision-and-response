#include "ReactionStrategyParams.h"

ReactionStrategyParams::ReactionStrategyParams() :
	// Initialize attributes and set default values	
	minAgreementPercentage(0.8),
	minDurationTicks(300) {
}

Real ReactionStrategyParams::getMinAgreementPercentage() const {
	return minAgreementPercentage;
}

int ReactionStrategyParams::getMinDurationTicks() const {
	return minDurationTicks;
}

void ReactionStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "min_agreement_percentage", minAgreementPercentage, minAgreementPercentage);
	GetNodeAttributeOrDefault(configurationNode, "min_duration_ticks", minDurationTicks, minDurationTicks);
}