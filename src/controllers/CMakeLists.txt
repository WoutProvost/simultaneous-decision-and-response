# Add these libraries to be built
add_library(footbot SHARED FootBotController.h FootBotController.cpp)
add_library(footbot_gate_gripping MODULE FootBotGateGrippingController.h FootBotGateGrippingController.cpp)
add_library(footbot_temperature_sensing MODULE FootBotTemperatureSensingController.h FootBotTemperatureSensingController.cpp)
add_library(movement SHARED params/MovementParams.h params/MovementParams.cpp)
add_library(collision_avoidance SHARED params/CollisionAvoidanceParams.h params/CollisionAvoidanceParams.cpp)
add_library(voting_strategy SHARED params/VotingStrategyParams.h params/VotingStrategyParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(footbot
	movement
	collision_avoidance)
target_link_libraries(footbot_gate_gripping
	footbot)
target_link_libraries(footbot_temperature_sensing
	footbot
	voting_strategy
	fire_evacuation_loop_functions)