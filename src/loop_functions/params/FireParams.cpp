#include "FireParams.h"
#include <limits>

using std::numeric_limits;
using std::to_string;

FireParams::FireParams() :
	// Initialize attributes and set default values
	sources(1),
	positions(0),
	circleRadius(3.0) {
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

void FireParams::setParams(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	GetNodeAttributeOrDefault(configurationNode, "sources", sources, sources);
	GetNodeAttributeOrDefault(configurationNode, "circle_radius", circleRadius, circleRadius);

	// Get the positions of the sources
	positions = vector<CVector2>(sources, CVector2(numeric_limits<Real>::quiet_NaN(), numeric_limits<Real>::quiet_NaN()));
	for(int source = 0; source < sources; source++) {
		GetNodeAttributeOrDefault(configurationNode, "position" + to_string(source+1), positions[source], positions[source]);
	}
}