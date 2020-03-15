#include "HeatMapParams.h"

HeatMapParams::HeatMapParams() :
	// Initialize attributes and set default values
	tilesPerMeter(10),
	maxTemperature(MAX_POSSIBLE_TEMPERATURE),
	debugMode("none"),
	showTemperature(false) {
}

void HeatMapParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
    GetNodeAttributeOrDefault(configurationNode, "tiles_per_meter", tilesPerMeter, tilesPerMeter);
    GetNodeAttributeOrDefault(configurationNode, "max_temperature", maxTemperature, maxTemperature);
    GetNodeAttributeOrDefault(configurationNode, "debug_mode", debugMode, debugMode);
    GetNodeAttributeOrDefault(configurationNode, "show_temperature", showTemperature, showTemperature);
}