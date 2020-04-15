#include "VotingStrategyParams.h"

VotingStrategyParams::VotingStrategyParams() :
	// Initialize attributes and set default values	
	mode("none") {
}

void VotingStrategyParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
}