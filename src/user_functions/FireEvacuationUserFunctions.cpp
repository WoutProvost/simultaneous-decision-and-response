#include "FireEvacuationUserFunctions.h"
#include <argos3/core/simulator/space/space.h>

void FireEvacuationUserFunctions::Init(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	try {
		dividerParams.setParams(GetNode(configurationNode, "divider"));
	} catch(CARGoSException &ex) {
	}
}

void FireEvacuationUserFunctions::DrawInWorld() {
	// Draw the horizontal divider that visually cuts the arena in half
	if(dividerParams.getEnable()) {
		Real sizeX = CSimulator::GetInstance().GetSpace().GetArenaSize().GetX();
		DrawRay(CRay3(CVector3(-sizeX/2, 0.0, 0.5), CVector3(sizeX/2, 0.0, 0.5)), CColor::RED);
	}
}

// Macro that binds this class to an XML tag
REGISTER_QTOPENGL_USER_FUNCTIONS(FireEvacuationUserFunctions, "fire_evacuation_user_functions")