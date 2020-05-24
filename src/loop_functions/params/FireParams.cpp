#include "FireParams.h"
#include <limits>

using std::numeric_limits;
using std::to_string;

FireParams::FireParams() :
	// Initialize attributes and set default values
	sources(1),
	positions(0),
	circleRadius(3.0),
	isDynamic(false),
	dynamicIntervalTicks(50),
	dynamicTemperatureIncrease(5),
	dynamicSpreadDirection(0.0) {
}

int FireParams::getSources() const {
	return sources;
}

const vector<CVector2>& FireParams::getPositions() const {
	return positions;
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

	// Get the positions of the sources
	positions = vector<CVector2>(sources, CVector2(numeric_limits<Real>::quiet_NaN(), numeric_limits<Real>::quiet_NaN()));
	for(int source = 0; source < sources; source++) {
		GetNodeAttributeOrDefault(configurationNode, "position" + to_string(source+1), positions[source], positions[source]);
	}
}