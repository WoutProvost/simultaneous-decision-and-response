#include "LogParams.h"

LogParams::LogParams() :
	// Initialize attributes and set default values
	file("../logs/log.csv"),
	disable(false) {
}

void LogParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "file", file, file);
	GetNodeAttributeOrDefault(configurationNode, "disable", disable, disable);
}