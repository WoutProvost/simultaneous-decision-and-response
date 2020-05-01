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

int FireParams::getSources() const {
	return sources;
}

Real FireParams::getCircleRadius() const {
	return circleRadius;
}

bool FireParams::getIsDynamic() const {
	return isDynamic;
}

int FireParams::getDynamicIntervalTicks() const {
	return dynamicIntervalTicks;
}

int FireParams::getDynamicTemperatureIncrease() const {
	return dynamicTemperatureIncrease;
}

const CDegrees& FireParams::getDynamicSpreadDirection() const {
	return dynamicSpreadDirection;
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