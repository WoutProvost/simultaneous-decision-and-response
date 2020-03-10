# Add these libraries to be built
# SHARED = linked dynamically into other targets and loaded at runtime
# MODULE = not linked into other targets and loaded dynamically at runtime
add_library(footbot_base SHARED footbot_base.h footbot_base.cpp)
add_library(footbot_gate_gripping MODULE footbot_gate_gripping.h footbot_gate_gripping.cpp)
add_library(footbot_temperature_sensing MODULE footbot_temperature_sensing.h footbot_temperature_sensing.cpp)

# Define which other libraries these libraries depend on
target_link_libraries(footbot_base
	argos3core_simulator
	argos3plugin_simulator_footbot
	argos3plugin_simulator_genericrobot)
target_link_libraries(footbot_gate_gripping
	footbot_base)
target_link_libraries(footbot_temperature_sensing
	footbot_base)