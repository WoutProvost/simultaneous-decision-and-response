#ifndef FIRE_EVACUATION_LOOP_FUNCTIONS_H
#define FIRE_EVACUATION_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include "params/HeatMapParams.h"
#include "params/FireParams.h"
#include <argos3/core/simulator/entity/floor_entity.h>

using namespace argos;
using std::vector;
using std::map;
using std::ofstream;

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
		int temperatureSensingFootBots;
		int gateGrippingFootBots;
		map<uint32_t,int> exitLightColors;
		string fileName;
		ofstream logFile;

		// Methods
		void initHeatMap();

	public:		
		// Constructors
		FireEvacuationLoopFunctions();

		// Getters
		const HeatMapParams& getHeatMapParams() const;
		const FireParams& getFireParams() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void Reset();
		virtual void Destroy();
		virtual void PreStep();
		virtual void PostStep();
		virtual CColor GetFloorColor(const CVector2 &positionOnFloor);

};

#endif