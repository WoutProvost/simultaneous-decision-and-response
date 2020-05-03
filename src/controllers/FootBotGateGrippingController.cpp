#include "FootBotGateGrippingController.h"
#include "enums/RABIndex.h"
#include <algorithm>

using std::max_element;

FootBotGateGrippingController::FootBotGateGrippingController() :
	// Call base class method and initialize attributes and set default values
	FootBotController::FootBotController(),
	actingExitLightColor(CColor::BLACK),
	candidateExitLightColor(CColor::BLACK),
	candidateExitTicks(0) {
}

const CColor& FootBotGateGrippingController::getActingExitLightColor() const {
	return actingExitLightColor;
}

void FootBotGateGrippingController::Init(TConfigurationNode &configurationNode) {
	// Call base class method
	FootBotController::Init(configurationNode);

	// Get actuators and sensors
	footBotGripperActuator = GetActuator<CCI_FootBotGripperActuator>("footbot_gripper");
	
	// Parse the configuration file for params
	try {
		reactionStrategyParams.setParams(GetNode(configurationNode, "reaction_strategy"));
	} catch(CARGoSException &ex) {
	}
}

void FootBotGateGrippingController::ControlStep() {
	// Call base class method
	FootBotController::ControlStep();

	// Receive opinions from temperature sensing robots in this robot's neighbourhood
	listenToDecisions();

	// If the robot is not undecided, lit up all the LEDs in the ring except the beacon with a color that represents the robot's exit acted upon
	// The color is slightly different from the exit color so that it won't be detected as an exit
	if(appearanceParams.getDebugShowPreference() && actingExitLightColor != CColor::BLACK) {
		ledsActuator->SetAllColors(getExitLightColorForRobotsToUse(actingExitLightColor));
		ledsActuator->SetSingleColor(12, color);
	}
}

void FootBotGateGrippingController::Reset() {
	// Call base class method
	FootBotController::Reset();

	// Reset the exit acted upon to its initial state
	actingExitLightColor = CColor::BLACK;

	// Reset the candidate exit that might be acted upon in the future to its initial state
	candidateExitLightColor = CColor::BLACK;

	// Reset the ticks since the candidate exit was last updated to its initial state
	candidateExitTicks = 0;
}

void FootBotGateGrippingController::listenToDecisions() {
	// Get readings from the range and bearing sensor
	const CCI_RangeAndBearingSensor::TReadings &readings = rangeAndBearingSensor->GetReadings();

	// Receive decisions from temperature sensing robots in this robot's neighbourhood
	int totalVotes = 0;
	map<uint32_t,int> exitVotes;
	map<uint32_t,CColor> exitColors;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		UInt8 temperature = readings[reading].Data[RABIndex::TEMPERATURE];
		if(temperature != 0) {
			UInt8 red = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_RED];
			UInt8 green = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_GREEN];
			UInt8 blue = readings[reading].Data[RABIndex::EXIT_COLOR_CHANNEL_BLUE];
			CColor exitColor = CColor(red, green, blue);
			UInt8 distance = readings[reading].Data[RABIndex::EXIT_DISTANCE];

			totalVotes++;
			exitVotes[exitColor]++;
			exitColors[exitColor] = exitColor;
		}
	}

	// If the neighbouring temperature sensing robots actually have made decisions
	// Use the combined data to determine which exit to act upon based upon the used parameters
	if(exitVotes.size() != 0) {
		// Combination of plurality and majority models
		// Only use a strict winning vote, i.e. don't do anything when there's an ex aequo for the winning vote
		map<uint32_t,int>::iterator winningVote = max_element(exitVotes.begin(), exitVotes.end());
		map<uint32_t,int>::iterator it = exitVotes.begin();
		while(it != exitVotes.end() && (it->second != winningVote->second || it->first == winningVote->first)) {
			it++;
		}
		if(it == exitVotes.end() && static_cast<Real>(winningVote->second)/totalVotes >= reactionStrategyParams.getMinAgreementPercentage()) {
			if(candidateExitLightColor != exitColors[winningVote->first]) {
				candidateExitLightColor = exitColors[winningVote->first];
				candidateExitTicks = 0;
			} else {
				if(candidateExitTicks < reactionStrategyParams.getMinDurationTicks()) {
					candidateExitTicks++;
				}
			}
		} else {
			candidateExitTicks = 0;
		}
	}

	// If an exit is preferred by at least the given percentage of neighbouring temperature sensing robots for the given time duration, start acting upon that exit
	if(candidateExitTicks == reactionStrategyParams.getMinDurationTicks()) {
		actingExitLightColor = candidateExitLightColor;
		candidateExitTicks++;
	}
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotGateGrippingController, "footbot_gate_gripping")