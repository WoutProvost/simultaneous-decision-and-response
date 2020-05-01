#include "DecisionStrategyParams.h"

DecisionStrategyParams::DecisionStrategyParams() :
	// Initialize attributes and set default values	
	mode("none") {
}

void DecisionStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
}