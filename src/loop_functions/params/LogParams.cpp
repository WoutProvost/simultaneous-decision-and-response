#include "LogParams.h"

LogParams::LogParams() :
	// Initialize attributes and set default values
	file("../logs/log.csv"),
	disable(false) {
}

const string& LogParams::getFile() const {
	return file;
}

bool LogParams::getDisable() const {
	return disable;
}

void LogParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "file", file, file);
	GetNodeAttributeOrDefault(configurationNode, "disable", disable, disable);
}