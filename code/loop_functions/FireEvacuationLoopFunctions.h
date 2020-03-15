#ifndef FIRE_EVACUATION_LOOP_FUNCTIONS_H
#define FIRE_EVACUATION_LOOP_FUNCTIONS_H

#include "HeatMapParams.h"
#include "FireParams.h"
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>

using namespace argos;
using std::vector;

class FireEvacuationLoopFunctions : public CLoopFunctions {

	private:
		// Params
		HeatMapParams heatMapParams;
		FireParams fireParams;
		
		// General variables and constants
		CSpace *space;
		const CVector3 *arenaSize;
		CRandom::CRNG *random;
		CFloorEntity *floorEntity;
		vector<vector<int>> heatMap;

		// Methods
		void initHeatMap();

	public:
		FireEvacuationLoopFunctions();

		virtual void Init(TConfigurationNode &configurationNode);
		virtual void Reset();
		virtual void PreStep();
		virtual CColor GetFloorColor(const CVector2 &positionOnFloor);

};

#endif