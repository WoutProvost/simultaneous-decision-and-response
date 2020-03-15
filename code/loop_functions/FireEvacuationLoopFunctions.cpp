#include "FireEvacuationLoopFunctions.h"

// All possible colors of a grayscale gradient sit in the range [0:255]
#define MAX_POSSIBLE_TEMPERATURE		255

FireEvacuationLoopFunctions::FireEvacuationLoopFunctions() :
	// Initialize attributes and set default values
	tilesPerMeter(10),
	maxTemperature(MAX_POSSIBLE_TEMPERATURE),
	debugMode("none"),
	showTemperature(false),
	space(&GetSpace()),
	arenaSize(&space->GetArenaSize()),
	// floorEntity(&space->GetFloorEntity()),
	heatMap(vector<vector<int>>(arenaSize->GetX()*tilesPerMeter, vector<int>(arenaSize->GetY()*tilesPerMeter))) {
}

void FireEvacuationLoopFunctions::Init(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	try {
		TConfigurationNode &heatMapNode = GetNode(configurationNode, "heatmap");
		GetNodeAttributeOrDefault(heatMapNode, "tiles_per_meter", tilesPerMeter, tilesPerMeter);
		GetNodeAttributeOrDefault(heatMapNode, "max_temperature", maxTemperature, maxTemperature);
		GetNodeAttributeOrDefault(heatMapNode, "debug_mode", debugMode, debugMode);
		GetNodeAttributeOrDefault(heatMapNode, "show_temperature", showTemperature, showTemperature);
	} catch(CARGoSException &ex) {
	}

	// The max temperature can't exceed the max possible temperature
	if(maxTemperature > MAX_POSSIBLE_TEMPERATURE) {
		maxTemperature = MAX_POSSIBLE_TEMPERATURE;
	}

	// Set the size of the heatmap depending on the size of the arena and the resolution depending on the tiles per meter
	int resolutionX = arenaSize->GetX()*tilesPerMeter;
	int resolutionY = arenaSize->GetY()*tilesPerMeter;
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY));

	// Initialize the heatmap with predetermined temperatures
	initHeatMap();

	// When the heatmap gets updated, this should be called
	// floorEntity->SetChanged();
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	initHeatMap();
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// Get the heatmap indices and temperature that belong to this floor position
	int indexX = (positionOnFloor.GetX() + arenaSize->GetX()/2) * tilesPerMeter;
	int indexY = (positionOnFloor.GetY() + arenaSize->GetY()/2) * tilesPerMeter;
	int temperature = MAX_POSSIBLE_TEMPERATURE / maxTemperature * heatMap[indexX][indexY];

	// If the temperature shouldn't be shown return white, otherwise return a grayscale color depending on the temperature		
	if(!showTemperature) {
		temperature = 255;
	}
	
	return CColor(temperature, temperature, temperature, 255);
}

void FireEvacuationLoopFunctions::initHeatMap() {
	// Initialize the heatmap to debug the resolution
	if(debugMode == "resolution") {
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = maxTemperature * ((x+y)%2);
			}
		}
	}
	// Initialize the heatmap to debug the gradient
	else if(debugMode == "gradient") {
		Real spacing = maxTemperature / (arenaSize->GetX()*tilesPerMeter - 1);
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = spacing * x;
			}
		}
	}
	// Initialize the heatmap to have no temperature
	else {
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = 0;
			}
		}
	}
}

// Macro that binds this class to an XML tag
REGISTER_LOOP_FUNCTIONS(FireEvacuationLoopFunctions, "fire_evacuation_loop_functions")