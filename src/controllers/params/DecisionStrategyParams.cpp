#include "DecisionStrategyParams.h"

DecisionStrategyParams::DecisionStrategyParams() :
	// Initialize attributes and set default values	
	mode("none") {
}

const string& DecisionStrategyParams::getMode() const {
	return mode;
}

void DecisionStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
}