#include "FireParams.h"

FireParams::FireParams() :
	// Initialize attributes and set default values
	mode("circle"),
	isDynamic(false),
	dynamicIntervalTicks(50),
	dynamicTemperatureIncrease(20),
	circleRadiusInmeters(3.0) {
}

void FireParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
    GetNodeAttributeOrDefault(configurationNode, "mode", mode, mode);
    GetNodeAttributeOrDefault(configurationNode, "is_dynamic", isDynamic, isDynamic);
    GetNodeAttributeOrDefault(configurationNode, "dynamic_interval_ticks", dynamicIntervalTicks, dynamicIntervalTicks);
    GetNodeAttributeOrDefault(configurationNode, "dynamic_temperature_increase", dynamicTemperatureIncrease, dynamicTemperatureIncrease);
    GetNodeAttributeOrDefault(configurationNode, "circle_radius_in_meters", circleRadiusInmeters, circleRadiusInmeters);
}