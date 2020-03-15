#ifndef FIRE_EVACUATION_LOOP_FUNCTIONS_H
#define FIRE_EVACUATION_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>

using namespace argos;
using std::vector;
using std::string;

class FireEvacuationLoopFunctions : public CLoopFunctions {

	private:
		// Params
		int tilesPerMeter;
		int maxTemperature;
		string debugMode;
		bool showTemperature;
		
		// General variables and constants
		CSpace *space;
		const CVector3 *arenaSize;
		CFloorEntity *floorEntity;
		vector<vector<int>> heatMap;
		CRandom::CRNG *random;

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