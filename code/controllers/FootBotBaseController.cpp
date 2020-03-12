#include "FootBotBaseController.h"

FootBotBaseController::FootBotBaseController() :
	differentialSteeringActuator(NULL),
	ledsActuator(NULL),
	rangeAndBearingActuator(NULL),
	footBotProximitySensor(NULL),
	rangeAndBearingSensor(NULL),
    coloredBlobOmnidirectionalCameraSensor(NULL),
	velocity(2.5f),
	maxAngleBetweenHeadingAndObstacle(10.0f),
	maxObstacleProximity(0.5f),
	ledsColorString("black"),
	doNotTurnAngleRange(-ToRadians(maxAngleBetweenHeadingAndObstacle), ToRadians(maxAngleBetweenHeadingAndObstacle)),
	ledsColor(0, 0, 0, 255) {
}

void FootBotBaseController::Init(TConfigurationNode &t_node) {
	// Get actuators and sensors
	differentialSteeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	ledsActuator = GetActuator<CCI_LEDsActuator>("leds");
	rangeAndBearingActuator = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
	footBotProximitySensor = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
	rangeAndBearingSensor = GetSensor<CCI_RangeAndBearingSensor>("range_and_bearing");
    coloredBlobOmnidirectionalCameraSensor = GetSensor<CCI_ColoredBlobOmnidirectionalCameraSensor>("colored_blob_omnidirectional_camera");

	// Parse the configuration file for params
	GetNodeAttributeOrDefault(t_node, "velocity", velocity, velocity);
	GetNodeAttributeOrDefault(t_node, "max_angle_between_heading_and_obstacle", maxAngleBetweenHeadingAndObstacle, maxAngleBetweenHeadingAndObstacle);
	GetNodeAttributeOrDefault(t_node, "max_obstacle_proximity", maxObstacleProximity, maxObstacleProximity);
	GetNodeAttributeOrDefault(t_node, "leds_color", ledsColorString, ledsColorString);

	// Adjust the angle range in which the robot won't turn, with the retrieved angle from the configuration file
	doNotTurnAngleRange.Set(-ToRadians(maxAngleBetweenHeadingAndObstacle), ToRadians(maxAngleBetweenHeadingAndObstacle));

	// Lit up all the LEDs in the ring with the same color and intensity
	ledsColor.Set(ledsColorString);
	ledsActuator->SetAllColors(ledsColor);
}

void FootBotBaseController::ControlStep() {
	// Get readings from the proximity sensor
	const CCI_FootBotProximitySensor::TReadings &readings = footBotProximitySensor->GetReadings();

	// Sum these readings together
	CVector2 accumulator;
	for(size_t reading = 0, size = readings.size(); reading < size; reading++) {
		accumulator += CVector2(readings[reading].Value, readings[reading].Angle);
	}
	accumulator /= readings.size();
	CRadians angle = accumulator.Angle();

	// If the angle is small enough and the closest obstacle is far enough
	if(doNotTurnAngleRange.WithinMinBoundIncludedMaxBoundIncluded(angle) && accumulator.Length() < maxObstacleProximity) {
		// Go straight (left and right wheel turn with the same velocity)
		differentialSteeringActuator->SetLinearVelocity(velocity, velocity);
	}
	// Otherwise, turn a little, depending on the sign of the angle
	else {
		if(angle.GetValue() > 0.0f) {
			// Turn right (only left wheel turns)
			differentialSteeringActuator->SetLinearVelocity(velocity, 0.0f);
		} else {
			// Turn left (only right wheel turns)
			differentialSteeringActuator->SetLinearVelocity(0.0f, velocity);
		}
	}
}

void FootBotBaseController::Reset() {
	// Reset all the LEDs in the ring with the same color and intensity from the initial state
	ledsActuator->SetAllColors(ledsColor);
}

// Macro that binds this class to an XML tag
REGISTER_CONTROLLER(FootBotBaseController, "footbot_base_controller")