#include "FireEvacuationUserFunctions.h"
#include "../loop_functions/FireEvacuationLoopFunctions.h"

FireEvacuationUserFunctions::FireEvacuationUserFunctions() :
	// Initialize attributes and set default values
	nestSize(&dynamic_cast<FireEvacuationLoopFunctions&>(CSimulator::GetInstance().GetLoopFunctions()).getNestParams().getSize()) {
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
		DrawRay(CRay3(CVector3(-nestSize->GetX()/2, 0.0, 0.0001), CVector3(nestSize->GetX()/2, 0.0, 0.0001)), CColor::RED);
	}

	// Draw the vertical divider that visually cuts the arena in half
	if(dividerParams.getEnableVertical()) {
		DrawRay(CRay3(CVector3(0.0, -nestSize->GetY()/2, 0.0001), CVector3(0.0, nestSize->GetY()/2, 0.0001)), CColor::RED);
	}
}

// Macro that binds this class to an XML tag
REGISTER_QTOPENGL_USER_FUNCTIONS(FireEvacuationUserFunctions, "fire_evacuation_user_functions")