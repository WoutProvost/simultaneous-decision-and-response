#include "FootBotController.h"
#include "enums/RABIndex.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/entities/light_entity.h>

FootBotController::FootBotController() :
	// Initialize attributes and set default values
	color(CColor::BLACK),
	turnMode(TurnMode::NONE),
	behaviourState(BehaviourState::ROAMING),
	coloredBlobOmnidirectionalCameraSensorEnabled(false) {
}

void FootBotController::Init(TConfigurationNode &configurationNode) {
	// Get actuators and sensors
	differentialSteeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	ledsActuator = GetActuator<CCI_LEDsActuator>("leds");
	rangeAndBearingActuator = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
	footBotProximitySensor = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
	rangeAndBearingSensor = GetSensor<CCI_RangeAndBearingSensor>("range_and_bearing");
	coloredBlobOmnidirectionalCameraSensor = GetSensor<CCI_ColoredBlobOmnidirectionalCameraSensor>("colored_blob_omnidirectional_camera");
	footBotLightSensor = GetSensor<CCI_FootBotLightSensor>("footbot_light");

	// Parse the configuration file for params
	try {
		appearanceParams.setParams(GetNode(configurationNode, "appearance"));
	} catch(CARGoSException &ex) {
	}
	try {
		movementParams.setParams(GetNode(configurationNode, "movement"));
	} catch(CARGoSException &ex) {
	}
	try {
		collisionAvoidanceParams.setParams(GetNode(configurationNode, "collision_avoidance"));
	} catch(CARGoSException &ex) {
	}

	// Lit up all the LEDs in the ring with the same color and intensity
	color.Set(appearanceParams.getLedsColor());
	ledsActuator->SetAllColors(color);

	// Add this LED color to the colored blobs that should be ignored when reading from the colored blob omnidirectional camera sensor
	ignoredColoredBlobs[color] = true;

	// If the robot is configured to show it's exit preference using the LEDs, also add a slightly altered exit color to this list for each exit
	// This makes sure that the robot's LEDs won't be detected as the exit itself
	if(appearanceParams.getDebugShowPreference()) {
		string prefix("exit_light_");
		CSpace::TMapPerType &lightEntities = CSimulator::GetInstance().GetSpace().GetEntitiesByType("light");
		for(CSpace::TMapPerType::iterator it = lightEntities.begin(), end = lightEntities.end(); it != end; it++) {
			CLightEntity &lightEntity = *any_cast<CLightEntity*>(it->second);
			if(lightEntity.GetId().compare(0, prefix.length(), prefix) == 0) {
				ignoredColoredBlobs[getExitLightColorForRobotsToUse(lightEntity.GetColor())] = true;
			}
		}
	}
}

void FootBotController::ControlStep() {
	// Execute correct behaviour
	switch(behaviourState) {
		case BehaviourState::IDLE: {
			break;
		}
		case BehaviourState::ROAMING: {
			roam();
			break;
		}
	}
}

void FootBotController::Reset() {
	// Reset all the LEDs in the ring to their initial state
	ledsActuator->SetAllColors(color);

	// Clear all data that is still in the buffer
	rangeAndBearingActuator->ClearData();

	// Reset the turn mode to its initial state
	turnMode = TurnMode::NONE;

	// Reset the behaviour state to its initial state
	behaviourState = BehaviourState::ROAMING;

	// Disable the colored blob omnidirectional camera sensor
	coloredBlobOmnidirectionalCameraSensor->Disable();
	coloredBlobOmnidirectionalCameraSensorEnabled = false;
}

CColor FootBotController::getExitLightColorForRobotsToUse(const CColor &color) {
	// Slightly alter the color so that it won't be detected as an exit
	CColor exitLedsColor = color;
	if(exitLedsColor.GetRed() < 128) {
		exitLedsColor.SetRed(exitLedsColor.GetRed() + 1);
	} else {
		exitLedsColor.SetRed(exitLedsColor.GetRed() - 1);
	}
	if(exitLedsColor.GetGreen() < 128) {
		exitLedsColor.SetGreen(exitLedsColor.GetGreen() + 1);
	} else {
		exitLedsColor.SetGreen(exitLedsColor.GetGreen() - 1);
	}
	if(exitLedsColor.GetBlue() < 128) {
		exitLedsColor.SetBlue(exitLedsColor.GetBlue() + 1);
	} else {
		exitLedsColor.SetBlue(exitLedsColor.GetBlue() - 1);
	}
	return exitLedsColor;
}

void FootBotController::roam() {
	// Get the vector that points directly away from a potential obstacle to perform collision avoidance
	CVector2 heading = getCollisionAvoidanceVector();

	// Set the velocities of both the left and the right wheels according to the maximum velocity and to where the robot should go
	setWheelVelocitiesFromVector(movementParams.getMaxVelocity() * heading);
}

CVector2 FootBotController::getVectorToLight() {
	// Get readings from the light sensor
	const CCI_FootBotLightSensor::TReadings &readings = footBotLightSensor->GetReadings();

	// Get a new vector that points directly to the closest light using vector addition
	CVector2 vectorToClosestLight;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		vectorToClosestLight += CVector2(readings[reading].Value, readings[reading].Angle);
	}

	// Return the zero vector if no light was perceived
	if(vectorToClosestLight.Length() == 0.0) {
		return CVector2::ZERO;
	}
	// Otherwise return a unit vector to the light using vector normalization
	else {
		return vectorToClosestLight.Normalize();
	}
}

CVector2 FootBotController::getCollisionAvoidanceVector() {
	// Get readings from the proximity sensor
	const CCI_FootBotProximitySensor::TReadings &readings = footBotProximitySensor->GetReadings();
	
	// Get a new vector that points directly to the closest obstacle using vector addition
	CVector2 vectorToClosestObstacle;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		vectorToClosestObstacle += CVector2(readings[reading].Value, readings[reading].Angle);
	}

	// Ignore the obstacle and go straight if the angle to it is small enough and if it is far enough away
	// The sensors return a value between 0 (nothing within range) and 1 (obstacle touching sensor), which is why we need to use < instead of > when checking for the proximity of the obstacle
	CDegrees angle = ToDegrees(vectorToClosestObstacle.Angle());
	if(angle >= -collisionAvoidanceParams.getMaxAngleBetweenHeadingAndObstacle() && angle <= collisionAvoidanceParams.getMaxAngleBetweenHeadingAndObstacle()
	&& vectorToClosestObstacle.Length() < collisionAvoidanceParams.getMaxObstacleProximity()) {
		return CVector2::X;
	}
	// Otherwise return a unit vector that points directly away from the closest obstacle using vector normalization and vector negation
	else {
		return -vectorToClosestObstacle.Normalize();
	}
}

void FootBotController::setWheelVelocitiesFromVector(const CVector2 &heading) {
	// Get the angle of the heading as a value in the range [-180:180]
	CDegrees angle = ToDegrees(heading.Angle().SignedNormalize());

	// Limit the velocity to the maximum velocity
	Real velocity = heading.Length();
	if(velocity > movementParams.getMaxVelocity()) {
		velocity = movementParams.getMaxVelocity();
	}

	// Determine which turn mode to use according to where the robot should go
	if(Abs(angle) >= movementParams.getMinHeadingAngleForHardTurn()) {
		turnMode = TurnMode::HARD;
	} else if(Abs(angle) <= movementParams.getMaxHeadingAngleForNoTurn()) {
		turnMode = TurnMode::NONE;
	} else {
		turnMode = TurnMode::SOFT;
	}

	// Set the wheel velocities according to the turn mode
	Real v1, v2;
	switch(turnMode) {
		// Wheels turn in the same direction with the same velocities (go straight)
		case TurnMode::NONE: {
			v1 = velocity;
			v2 = velocity;
			break;
		}
		// Wheels turn in the same direction with different velocities
		case TurnMode::SOFT: {
			Real factor = (movementParams.getMinHeadingAngleForHardTurn() - Abs(angle)) / movementParams.getMinHeadingAngleForHardTurn();
			v1 = velocity - velocity * (1.0 - factor);
			v2 = velocity + velocity * (1.0 - factor);
			break;
		}
		// Wheels turn in opposite directions with the same velocities (turn on the spot)
		case TurnMode::HARD: {
			v1 = -movementParams.getMaxVelocity();
			v2 = movementParams.getMaxVelocity();
			break;
		}
	}

	// Apply the calculated velocities to the appropriate wheels depending on the sign of the angle
	if(angle.GetValue() > 0.0) {
		// Turn left
		differentialSteeringActuator->SetLinearVelocity(v1, v2);
	} else {
		// Turn right
		differentialSteeringActuator->SetLinearVelocity(v2, v1);
	}
}

// Static variables and constants initialization
map<uint32_t,bool> FootBotController::ignoredColoredBlobs = map<uint32_t,bool>();

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotController, "footbot")