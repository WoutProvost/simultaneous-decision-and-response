#include "DividerParams.h"

DividerParams::DividerParams() :
	// Initialize attributes and set default values
	enableHorizontal(true),
	enableVertical(false) {
}

bool DividerParams::getEnableHorizontal() const {
	return enableHorizontal;
}

bool DividerParams::getEnableVertical() const {
	return enableVertical;
}

void DividerParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "enable_horizontal", enableHorizontal, enableHorizontal);
	GetNodeAttributeOrDefault(configurationNode, "enable_vertical", enableVertical, enableVertical);
}