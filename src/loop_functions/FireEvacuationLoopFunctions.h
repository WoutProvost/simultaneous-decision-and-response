#ifndef FIRE_EVACUATION_LOOP_FUNCTIONS_H
#define FIRE_EVACUATION_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include "params/NestParams.h"
#include "params/HeatMapParams.h"
#include "params/FireParams.h"
#include "params/LogParams.h"
#include <argos3/core/simulator/entity/floor_entity.h>

using namespace argos;
using std::vector;
using std::map;
using std::ofstream;

class FireEvacuationLoopFunctions : public CLoopFunctions {

	private:
		// Params
		NestParams nestParams;
		HeatMapParams heatMapParams;
		FireParams fireParams;
		LogParams logParams;

		// General variables and constants
		CSpace *space;
		CRandom::CRNG *random;
		CFloorEntity *floorEntity;
		CPhysicsEngine *physicsEngine;
		vector<vector<int>> heatMap;
		int temperatureSensingFootBots;
		int gateGrippingFootBots;
		map<uint32_t,int> temperatureSensingPreferences;
		map<uint32_t,int> gateGrippingActions;
		map<uint32_t,CColor> exitColors;
		ofstream logFile;

		// Methods
		void initHeatMap();
		void initLogFile();

	public:
		// Constructors
		FireEvacuationLoopFunctions();

		// Getters
		const NestParams& getNestParams() const;
		const HeatMapParams& getHeatMapParams() const;

		// Simulator methods
		virtual void Init(TConfigurationNode &configurationNode);
		virtual void Reset();
		virtual void Destroy();
		virtual void PostStep();
		virtual CColor GetFloorColor(const CVector2 &positionOnFloor);

};

#endif