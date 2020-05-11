#include "FireEvacuationUserFunctions.h"
#include <argos3/core/simulator/space/space.h>

FireEvacuationUserFunctions::FireEvacuationUserFunctions() :
	// Initialize attributes and set default values
	space(&CSimulator::GetInstance().GetSpace()),
	arenaSize(&space->GetArenaSize()) {
}

void FireEvacuationUserFunctions::Init(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	try {
		dividerParams.setParams(GetNode(configurationNode, "divider"));
	} catch(CARGoSException &ex) {
	}
}

void FireEvacuationUserFunctions::DrawInWorld() {
	// Draw the horizontal divider that visually cuts the arena in half
	if(dividerParams.getEnableHorizontal()) {
		Real sizeX = arenaSize->GetX();
		DrawRay(CRay3(CVector3(-sizeX/2, 0.0, 0.0001), CVector3(sizeX/2, 0.0, 0.0001)), CColor::RED);
	}

	// Draw the vertical divider that visually cuts the arena in half
	if(dividerParams.getEnableVertical()) {
		Real sizeY = arenaSize->GetY();
		DrawRay(CRay3(CVector3(0.0, -sizeY/2, 0.0001), CVector3(0.0, sizeY/2, 0.0001)), CColor::RED);
	}
}

// Macro that binds this class to an XML tag
REGISTER_QTOPENGL_USER_FUNCTIONS(FireEvacuationUserFunctions, "fire_evacuation_user_functions")