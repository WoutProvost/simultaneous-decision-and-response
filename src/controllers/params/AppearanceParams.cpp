#include "AppearanceParams.h"

AppearanceParams::AppearanceParams() :
	// Initialize attributes and set default values	
	ledsColor("black"),
	debugShowPreference(false) {
}

const string& AppearanceParams::getLedsColor() const {
	return ledsColor;
}

bool AppearanceParams::getDebugShowPreference() const {
	return debugShowPreference;
}

void AppearanceParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "leds_color", ledsColor, ledsColor);
	GetNodeAttributeOrDefault(configurationNode, "debug_show_preference", debugShowPreference, debugShowPreference);
}