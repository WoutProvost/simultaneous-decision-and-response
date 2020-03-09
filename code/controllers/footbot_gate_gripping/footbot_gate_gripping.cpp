#include "footbot_gate_gripping.h"

CFootBotGateGripping::CFootBotGateGripping() {}

void CFootBotGateGripping::Init(TConfigurationNode& t_node) {
    // Call base class method
    CFootBotBase::Init(t_node);
}

void CFootBotGateGripping::ControlStep() {
    // Call base class method
    CFootBotBase::ControlStep();
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(CFootBotGateGripping, "footbot_gate_gripping_controller")