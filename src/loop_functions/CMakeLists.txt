# Add these libraries to be built
add_library(fire_evacuation_loop_functions SHARED FireEvacuationLoopFunctions.h FireEvacuationLoopFunctions.cpp)
add_library(heatmap SHARED params/HeatMapParams.h params/HeatMapParams.cpp)
add_library(fire SHARED params/FireParams.h params/FireParams.cpp)
add_library(plot SHARED params/PlotParams.h params/PlotParams.cpp)

# Define the dependencies of these libraries
target_link_libraries(fire_evacuation_loop_functions
	heatmap
	fire
	plot)