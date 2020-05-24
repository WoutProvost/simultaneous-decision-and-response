#include "DecisionStrategyParams.h"

DecisionStrategyParams::DecisionStrategyParams() :
	// Initialize attributes and set default values	
	mode("none"),
	multipleFireSourcesSupportVersion(1) {
}

const string& DecisionStrategyParams::getMode() const {
	return mode;
}

int DecisionStrategyParams::getMultipleFireSourcesSupportVersion() const {
	return multipleFireSourcesSupportVersion;
}

void DecisionStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
	GetNodeAttributeOrDefault(configurationNode, "multiple_fire_sources_support_version", multipleFireSourcesSupportVersion, multipleFireSourcesSupportVersion);
}