#include "HeatMapParams.h"

HeatMapParams::HeatMapParams() :
	// Initialize attributes and set default values
	tilesPerMeter(6),
	maxTemperature(MAX_POSSIBLE_TEMPERATURE),
	debugMode("none"),
	debugUseColors(false) {
}

int HeatMapParams::getTilesPerMeter() const {
	return tilesPerMeter;
}

int HeatMapParams::getMaxTemperature() const {
	return maxTemperature;
}

const string& HeatMapParams::getDebugMode() const {
	return debugMode;
}

bool HeatMapParams::getDebugUseColors() const {
	return debugUseColors;
}

void HeatMapParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "tiles_per_meter", tilesPerMeter, tilesPerMeter);
	GetNodeAttributeOrDefault(configurationNode, "max_temperature", maxTemperature, maxTemperature);
	GetNodeAttributeOrDefault(configurationNode, "debug_mode", debugMode, debugMode);
	GetNodeAttributeOrDefault(configurationNode, "debug_use_colors", debugUseColors, debugUseColors);

	// The max temperature can't exceed the max possible temperature
	if(maxTemperature > MAX_POSSIBLE_TEMPERATURE) {
		maxTemperature = MAX_POSSIBLE_TEMPERATURE;
	}
}