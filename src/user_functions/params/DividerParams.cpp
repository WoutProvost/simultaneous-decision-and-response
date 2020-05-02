#include "DividerParams.h"

DividerParams::DividerParams() :
	// Initialize attributes and set default values
	enable(true) {
}

bool DividerParams::getEnable() const {
	return enable;
}

void DividerParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "enable", enable, enable);
}