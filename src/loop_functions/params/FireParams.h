#ifndef FIRE_PARAMS_H
#define FIRE_PARAMS_H

#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/angles.h>
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;
using std::vector;

class FireParams {

	private:
		// Params
		int sources;
		vector<CVector2> positions;
		Real circleRadius;
		bool isDynamic;
		int dynamicIntervalTicks;
		int dynamicTemperatureIncrease;
		CDegrees dynamicSpreadDirection;

	public:
		// Constructors
		FireParams();

		// Getters
		int getSources() const;
		const vector<CVector2>& getPositions() const;
		Real getCircleRadius() const;
		bool getIsDynamic() const;
		int getDynamicIntervalTicks() const;
		int getDynamicTemperatureIncrease() const;
		const CDegrees& getDynamicSpreadDirection() const;

		// Simulator methods
		void setParams(TConfigurationNode &configurationNode);

};

#endif