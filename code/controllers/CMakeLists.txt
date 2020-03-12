# Add these libraries to be built
# SHARED = linked dynamically into other targets and loaded at runtime
# MODULE = not linked into other targets and loaded dynamically at runtime
add_library(footbot_base SHARED FootBotBaseController.h FootBotBaseController.cpp)
add_library(footbot_gate_gripping MODULE FootBotGateGrippingController.h FootBotGateGrippingController.cpp)
add_library(footbot_temperature_sensing MODULE FootBotTemperatureSensingController.h FootBotTemperatureSensingController.cpp)
add_library(collision_avoidance SHARED CollisionAvoidanceParams.h CollisionAvoidanceParams.cpp)

# Define which other libraries these libraries depend on
target_link_libraries(footbot_base
	argos3core_simulator
	argos3plugin_simulator_footbot
	argos3plugin_simulator_genericrobot
	collision_avoidance)
target_link_libraries(footbot_gate_gripping
	footbot_base)
target_link_libraries(footbot_temperature_sensing
	footbot_base)