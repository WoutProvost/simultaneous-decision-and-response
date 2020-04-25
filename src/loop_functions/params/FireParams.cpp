#include "FireParams.h"

FireParams::FireParams() :
	// Initialize attributes and set default values
	sources(1),
	circleRadius(3.0),
	isDynamic(false),
	dynamicIntervalTicks(50),
	dynamicTemperatureIncrease(5),
	dynamicSpreadDirection(0.0) {
}

void FireParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "sources", sources, sources);
	GetNodeAttributeOrDefault(configurationNode, "circle_radius", circleRadius, circleRadius);
	GetNodeAttributeOrDefault(configurationNode, "is_dynamic", isDynamic, isDynamic);
	GetNodeAttributeOrDefault(configurationNode, "dynamic_interval_ticks", dynamicIntervalTicks, dynamicIntervalTicks);
	GetNodeAttributeOrDefault(configurationNode, "dynamic_temperature_increase", dynamicTemperatureIncrease, dynamicTemperatureIncrease);
	GetNodeAttributeOrDefault(configurationNode, "dynamic_spread_direction", dynamicSpreadDirection, dynamicSpreadDirection);
}