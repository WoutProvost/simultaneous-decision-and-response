#include "FootBotController.h"
#include "enums/RABIndex.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/entities/light_entity.h>

FootBotController::FootBotController() :
	// Initialize attributes and set default values
	random(CRandom::CreateRNG("argos")),
	color(CColor::BLACK),
	turnMode(TurnMode::NONE),
	behaviorState(BehaviorState::ROAMING),
	randomTurnTicks(0),
	randomTurnVector(CVector2::ZERO),
	coloredBlobOmnidirectionalCameraSensorEnabled(false) {
}

void FootBotController::Init(TConfigurationNode &configurationNode) {
	// Get actuators and sensors
	differentialSteeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	ledsActuator = GetActuator<CCI_LEDsActuator>("leds");
	footBotProximitySensor = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
	rangeAndBearingSensor = GetSensor<CCI_RangeAndBearingSensor>("range_and_bearing");
	coloredBlobOmnidirectionalCameraSensor = GetSensor<CCI_ColoredBlobOmnidirectionalCameraSensor>("colored_blob_omnidirectional_camera");
	positioningSensor = GetSensor<CCI_PositioningSensor>("positioning");

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
		for(auto it = lightEntities.begin(), end = lightEntities.end(); it != end; it++) {
			CLightEntity &lightEntity = *any_cast<CLightEntity*>(it->second);
			if(lightEntity.GetId().compare(0, prefix.length(), prefix) == 0) {
				ignoredColoredBlobs[getExitLightColorForRobotsToUse(lightEntity.GetColor())] = true;
			}
		}
	}
}

void FootBotController::ControlStep() {
	// Execute correct behavior
	switch(behaviorState) {
		case BehaviorState::IDLE: {
			break;
		}
		case BehaviorState::ROAMING: {
			roam();
			break;
		}
	}
}

void FootBotController::Reset() {
	// Reset all the LEDs in the ring to their initial state
	ledsActuator->SetAllColors(color);

	// Reset the turn mode to its initial state
	turnMode = TurnMode::NONE;

	// Reset the behavior state to its initial state
	behaviorState = BehaviorState::ROAMING;

	// Reset the ticks since the robot last turned in a random direction to its initial state
	randomTurnTicks = 0;

	// Reset the random direction vector the robot last turned to to its initial state
	randomTurnVector = CVector2::ZERO;

	// Disable the colored blob omnidirectional camera sensor
	coloredBlobOmnidirectionalCameraSensor->Disable();
	coloredBlobOmnidirectionalCameraSensorEnabled = false;
}

CVector2 FootBotController::getRandomTurnDirectionVector() {
	// Return a unit vector with a random angle	
	return CVector2(1.0, ToRadians(CDegrees(random->Uniform(CRange<Real>(0.0, 360.0))))); // Interval is [min,max) i.e. right-open
}

bool FootBotController::adjustHeadingWithRandomTurnDirection(CVector2 &heading) {
	// If the robot isn't currently performing obstacle avoidance, turn in a random direction every configured amount of timesteps to break up the grouping and mix the system better
	bool ignoreNoTurn = false;
	if(heading == CVector2::X) {
		// Increase the amount of ticks since the robot last turned in a random direction
		// Only increase the amount of ticks when not performing collision avoidance, so that over time the robots stop turning all at once
		randomTurnTicks++;

		// Check if the robot should turn in a random direction
		if(randomTurnTicks == movementParams.getRandomTurnTicks()) {
			// Get a unit vector that uses a random direction
			randomTurnVector = getRandomTurnDirectionVector();

			// Reset the ticks since the robot last turned in a random direction
			randomTurnTicks = 0;
		}

		// If the random direction vector the robot last turned to isn't in its initial state
		if(randomTurnVector != CVector2::ZERO) {
			// Get readings from the positioning sensor
			const CCI_PositioningSensor::SReading &reading = positioningSensor->GetReading();

			// Determine the robot orientation
			CRadians z; CRadians y; CRadians x;
			reading.Orientation.ToEulerAngles(z, y, x);

			// Change the heading to use the random direction
			heading = CVector2(heading.Length(), randomTurnVector.Angle() - z);

			// Make sure to use this new direction angle exactly
			ignoreNoTurn = true;
		}
	} else {
		// Reset the random direction vector the robot last turned to to its initial state so that the robot doesn't continually bump into the obstacle after completing the collision avoidance
		randomTurnVector = CVector2::ZERO;
	}
	return ignoreNoTurn;
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

CVector2 FootBotController::getVectorToExitLight(CColor exitColor) {
	// Get readings from the colored blob omnidirectional camera sensor
	const CCI_ColoredBlobOmnidirectionalCameraSensor::SReadings &readings = coloredBlobOmnidirectionalCameraSensor->GetReadings();

	// Get a new vector that points directly to the exit light
	CVector2 vectorToExitLight;
	for(size_t blob = 0, size = readings.BlobList.size(); blob < size; blob++) {
		if(!ignoredColoredBlobs[readings.BlobList[blob]->Color] && exitColor == readings.BlobList[blob]->Color) {
			vectorToExitLight = CVector2(readings.BlobList[blob]->Distance/100, readings.BlobList[blob]->Angle);
		}
	}

	// Return the zero vector if no exit light of that color was found
	if(vectorToExitLight.Length() == 0.0) {
		return CVector2::ZERO;
	}
	// Otherwise return the vector to the light
	else {
		return vectorToExitLight;
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

void FootBotController::setWheelVelocitiesFromVector(const CVector2 &heading, bool ignoreNoTurn) {
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
	} else if(!ignoreNoTurn && Abs(angle) <= movementParams.getMaxHeadingAngleForNoTurn()) {
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

void FootBotController::roam() {
	// Get the vector that points directly away from a potential obstacle to perform collision avoidance
	CVector2 heading = getCollisionAvoidanceVector();

	// Adjust the heading vector with a random turn direction if necessary
	bool ignoreNoTurn = adjustHeadingWithRandomTurnDirection(heading);

	// Set the velocities of both the left and the right wheels according to the maximum velocity and to where the robot should go
	setWheelVelocitiesFromVector(movementParams.getMaxVelocity() * heading, ignoreNoTurn);
}

// Static variables and constants initialization
map<uint32_t,bool> FootBotController::ignoredColoredBlobs = map<uint32_t,bool>();

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotController, "footbot")