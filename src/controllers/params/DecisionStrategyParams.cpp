#include "DecisionStrategyParams.h"

DecisionStrategyParams::DecisionStrategyParams() :
	// Initialize attributes and set default values	
	mode("none"),
	checkForFireCriticality(true) {
}

const string& DecisionStrategyParams::getMode() const {
	return mode;
}

bool DecisionStrategyParams::getCheckForFireCriticality() const {
	return checkForFireCriticality;
}

void DecisionStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
	GetNodeAttributeOrDefault(configurationNode, "check_for_fire_criticality", checkForFireCriticality, checkForFireCriticality);
}