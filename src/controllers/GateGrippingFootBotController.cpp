#include "GateGrippingFootBotController.h"
#include "enums/RABIndex.h"
#include <algorithm>

using std::max_element;
using std::pair;

GateGrippingFootBotController::GateGrippingFootBotController() :
	// Call base class method and initialize attributes and set default values
	FootBotController::FootBotController(),
	actingExitLightColor(CColor::BLACK),
	candidateExitLightColor(CColor::BLACK),
	candidateExitTicks(0) {
}

const CColor& GateGrippingFootBotController::getActingExitLightColor() const {
	return actingExitLightColor;
}

void GateGrippingFootBotController::Init(TConfigurationNode &configurationNode) {
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

void GateGrippingFootBotController::ControlStep() {
	// Call base class method
	FootBotController::ControlStep();

	// Receive opinions from temperature sensing robots in this robot's neighborhood
	listenToDecisions();

	// Act upon the acting exit
	executeResponse();

	// If the robot is not undecided, lit up all the LEDs in the ring except the beacon with a color that represents the robot's exit acted upon
	// The color is slightly different from the exit color so that it won't be detected as an exit
	if(appearanceParams.getDebugShowPreference() && actingExitLightColor != CColor::BLACK) {
		ledsActuator->SetAllColors(getExitLightColorForRobotsToUse(actingExitLightColor));
		ledsActuator->SetSingleColor(12, color);
	}
}

void GateGrippingFootBotController::Reset() {
	// Call base class method
	FootBotController::Reset();

	// Reset the exit acted upon to its initial state
	actingExitLightColor = CColor::BLACK;

	// Reset the candidate exit that might be acted upon in the future to its initial state
	candidateExitLightColor = CColor::BLACK;

	// Reset the ticks since the candidate exit was last updated to its initial state
	candidateExitTicks = 0;
}

void GateGrippingFootBotController::listenToDecisions() {
	// Get readings from the range and bearing sensor
	const CCI_RangeAndBearingSensor::TReadings &readings = rangeAndBearingSensor->GetReadings();

	// Receive decisions from temperature sensing robots in this robot's neighborhood
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
			UInt8 distanceIntegralPart = readings[reading].Data[RABIndex::EXIT_DISTANCE_PART_INTEGRAL];
			UInt8 distanceFractionalPart = readings[reading].Data[RABIndex::EXIT_DISTANCE_PART_FRACTIONAL];
			Real distance = distanceIntegralPart + static_cast<Real>(distanceFractionalPart)/100;

			totalVotes++;
			exitVotes[exitColor]++;
			exitColors[exitColor] = exitColor;
		}
	}

	// If there are any neighboring temperature sensing robots in the neighborhood and if these robots have actually made decisions
	// Use the combined data to determine which exit to act upon based upon the used parameters
	if(exitVotes.size() != 0) {
		// Combination of plurality and majority models in case a low minimum agreement percentage is given (i.e. less than 0.5)
		auto winningVote = max_element(exitVotes.begin(), exitVotes.end(), [](const pair<uint32_t,int> &a, const pair<uint32_t,int> &b)->bool{return a.second < b.second;});
		Real winningPercentage = static_cast<Real>(winningVote->second)/totalVotes;

		// If the percentage threshold has been reached
		if(exitVotes.size() == 1 || (winningPercentage > 1.0/exitVotes.size() && winningPercentage >= reactionStrategyParams.getMinAgreementPercentage())) {
			// If the exit preferred by the neighbors changes, update the candidate exit and reset the ticks since the candidate exit was last updated
			if(candidateExitLightColor != exitColors[winningVote->first]) {
				candidateExitLightColor = exitColors[winningVote->first];
				candidateExitTicks = 0;
			}
			// If the exit preferred by the neighbors has remained the same since the last control step, increase the ticks since the candidate exit was last updated if the time threshold wasn't reached already
			else {
				if(candidateExitTicks < reactionStrategyParams.getMinDurationTicks()) {
					candidateExitTicks++;
				}
			}
		}
		// If the percentage threshold wasn't reached, reset the ticks since the candidate exit was last updated if it wasn't reset already
		else {
			if(candidateExitTicks != 0) {
				candidateExitTicks = 0;
			}
		}
	}

	// If an exit is preferred by at least the given percentage of neighboring temperature sensing robots for the given time duration, start acting upon that exit
	// The ticks since the candidate exit was last updated is incremented one last time to prevent this block being executed each control step
	if(candidateExitTicks == reactionStrategyParams.getMinDurationTicks()) {
		actingExitLightColor = candidateExitLightColor;
		candidateExitTicks++;
	}
}

void GateGrippingFootBotController::executeResponse() {
	// // If the robot is not undecided, act upon the acting exit
	// if(actingExitLightColor != CColor::BLACK) {
	// 	// Enable the resource-intensive colored blob omnidirectional camera sensor when a measurement has to be made and the sensor is not yet enabled
	// 	if(actingExitLightPosition == CVector2::ZERO && !coloredBlobOmnidirectionalCameraSensorEnabled) {
	// 		coloredBlobOmnidirectionalCameraSensor->Enable();
	// 		coloredBlobOmnidirectionalCameraSensorEnabled = true;
	// 	}
	// 	// Disable the resource-intensive colored blob omnidirectional camera sensor when no measurement has to be made and the sensor is not yet disabled
	// 	else if(actingExitLightPosition != CVector2::ZERO && coloredBlobOmnidirectionalCameraSensorEnabled) {
	// 		coloredBlobOmnidirectionalCameraSensor->Disable();
	// 		coloredBlobOmnidirectionalCameraSensorEnabled = false;
	// 	}

	// 	// Get readings from the positioning sensor
	// 	const CCI_PositioningSensor::SReading &reading = positioningSensor->GetReading();

	// 	// Determine the robot orientation
	// 	CRadians z; CRadians y; CRadians x;
	// 	reading.Orientation.ToEulerAngles(z, y, x);

	// 	// Determine the absolute position of the acting exit
	// 	// The same delay from the temperature sensors applies here as well
	// 	if(coloredBlobOmnidirectionalCameraSensorEnabled) {
	// 		// Get the relative position of the acting exit to the robot
	// 		actingExitLightPosition = getVectorToExitLight(actingExitLightColor);

	// 		// If a succesful measurement was made, adjust this relative position to the absolute position in the nest
	// 		if(actingExitLightPosition != CVector2::ZERO) {
	// 			// TODO width params voor elke exit, dus zoals met positionX voor sources
	// 			// TODO exit orientation, don't just assume you need to change the X value

	// 			// Take into account the current orientation and position of the robot
	// 			actingExitLightPosition.Rotate(z);
	// 			actingExitLightPosition += CVector2(reading.Position.GetX(), reading.Position.GetY());

	// 			// Pick a random position along the exit width
	// 			Real exitWidth = 3.0;
	// 			actingExitLightPosition.SetX(random->Uniform(CRange<Real>(actingExitLightPosition.GetX() - (exitWidth/2 - 0.1), actingExitLightPosition.GetX() + (exitWidth/2 - 0.1)))); // Interval is [min,max) i.e. right-open
	// 		}
	// 	}

	// 	// If the position of the acting exit is known
	// 	if(actingExitLightPosition != CVector2::ZERO) {
	// 		// Get the vector that points directly away from a potential obstacle to perform collision avoidance
	// 		CVector2 heading = getCollisionAvoidanceVector();

	// 		// If the robot isn't currently performing obstacle avoidance, or is very close to the exit
	// 		bool ignoreNoTurn = false;
	// 		if(heading == CVector2::X || (actingExitLightPosition.GetX() - reading.Position.GetX() <= 0.2 && actingExitLightPosition.GetY() - reading.Position.GetY() <= 0.2)) {
	// 			// // If the robot is beyond the exit, continue straight ahead
	// 			// if(actingExitLightPosition.GetX() - reading.Position.GetX() < 0.0 || actingExitLightPosition.GetY() - reading.Position.GetY() < 0.0) {
	// 			// 	heading = CVector2::X;

	// 			// 	// TODO this condition depends on the orientation of the exit
	// 			// 	// TODO test for negative values
	// 			// 	// TODO test if the condition outside this one is still valid (maybe use abs)
	// 			// }
	// 			// // Otherwise, go to the exit
	// 			// else {
	// 				// Get the vector between the robot and the exit
	// 				CVector2 vectorBetweenRobotAndExit(actingExitLightPosition.GetX() - reading.Position.GetX(), actingExitLightPosition.GetY() - reading.Position.GetY());

	// 				// Change the heading to go to the exit
	// 				heading = CVector2(heading.Length(), vectorBetweenRobotAndExit.Angle() - z);
	// 			// }

	// 			// Make sure to use this new direction angle exactly
	// 			ignoreNoTurn = true;
	// 		}

	// 		// Set the velocities of both the left and the right wheels according to the maximum velocity and to where the robot should go
	// 		setWheelVelocitiesFromVector(movementParams.getMaxVelocity() * heading, ignoreNoTurn);
	// 	}
	// }
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(GateGrippingFootBotController, "gate_gripping_footbot")