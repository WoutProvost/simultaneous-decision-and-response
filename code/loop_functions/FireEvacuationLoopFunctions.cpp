#include "FireEvacuationLoopFunctions.h"

// All possible colors between 2 colors of a gradient (both included) sit in the range [0:510]
#define MAX_POSSIBLE_TEMPERATURE		510

FireEvacuationLoopFunctions::FireEvacuationLoopFunctions() :
	// Initialize attributes and set default values
	tilesPerMeter(10),
	maxTemperature(MAX_POSSIBLE_TEMPERATURE),
	debugMode("none"),
	showTemperature(false),
	space(&GetSpace()),
	arenaSize(&space->GetArenaSize()),
	// floorEntity(&space->GetFloorEntity()),
	heatMap(vector<vector<int>>(arenaSize->GetX()*tilesPerMeter, vector<int>(arenaSize->GetY()*tilesPerMeter, -1))) {
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

	// Set the size of the heatmap depending on the size of the arena and the resolution depending on the tiles per meter and initialize the heatmap to -1
	int resolutionX = arenaSize->GetX()*tilesPerMeter;
	int resolutionY = arenaSize->GetY()*tilesPerMeter;
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY, -1));

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
		Real spacing = maxTemperature / (arenaSize->GetX()*tilesPerMeter);
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = spacing * x;
			}
		}
	}

	// When the heatmap gets updated, this should be called
	// floorEntity->SetChanged();
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
		for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
			heatMap[x][y] = -1;
		}
	}
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// Get the heatmap indices and temperature that belong to this floor position
	int indexX = (positionOnFloor.GetX() + arenaSize->GetX()/2) * tilesPerMeter;
	int indexY = (positionOnFloor.GetY() + arenaSize->GetY()/2) * tilesPerMeter;
	int temperature = MAX_POSSIBLE_TEMPERATURE / maxTemperature * heatMap[indexX][indexY];

	// If the temperature shouldn't be shown or is unknown, return the default floor color
	if(!showTemperature || heatMap[indexX][indexY] < 0) {
		return CColor(209, 209, 209, 255);
	}
	// Otherwise, return a color depending on the temperature
	else {
		// Calculate the red and green components of the color
		int red = 0;
		int green = 0;
		if(temperature < 256) {
			green = 255;
			red = temperature;
		} else {
			red = 255;
			green = 255 - (temperature - 255);
		}
		
		return CColor(red, green, 0, 255);
	}
}

// Macro that binds this class to an XML tag
REGISTER_LOOP_FUNCTIONS(FireEvacuationLoopFunctions, "fire_evacuation_loop_functions")