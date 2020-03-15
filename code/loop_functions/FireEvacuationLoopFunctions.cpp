#include "FireEvacuationLoopFunctions.h"

FireEvacuationLoopFunctions::FireEvacuationLoopFunctions() :
	// Initialize attributes and set default values
	space(&GetSpace()),
	arenaSize(&space->GetArenaSize()),
	random(CRandom::CreateRNG("argos")) {
}

void FireEvacuationLoopFunctions::Init(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	try {
		heatMapParams.setParams(GetNode(configurationNode, "heatmap"));
	} catch(CARGoSException &ex) {
	}
	try {
		fireParams.setParams(GetNode(configurationNode, "fire"));
	} catch(CARGoSException &ex) {
	}

	// The max temperature can't exceed the max possible temperature
	if(heatMapParams.maxTemperature > MAX_POSSIBLE_TEMPERATURE) {
		heatMapParams.maxTemperature = MAX_POSSIBLE_TEMPERATURE;
	}

	// Initialize the floor entity
	floorEntity = &space->GetFloorEntity();

	// Set the size of the heatmap depending on the size of the arena and the resolution depending on the tiles per meter
	int resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
	int resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY));

	// While debugging, initialize the heatmap with predetermined temperatures
	if(heatMapParams.debugMode != "none") {
		initHeatMap();
	}
	// Otherwise create a fire at a random position
	else {
		// int centerX = random->Uniform(CRange<int>(-resolutionX/2, resolutionX/2));
		// int centerY = random->Uniform(CRange<int>(-resolutionY/2, resolutionY/2));

		// // Linear gradient
		// int radiusInmeters = 3;
		// int radius = radiusInmeters * heatMapParams.tilesPerMeter;
		// Real spacing = heatMapParams.maxTemperature / radius;
		// for(int r = 0; r <= radius; r++) {
		// 	for(int angle = 0; angle < 360; angle++) {
		// 		Real x = centerX + r * cos(angle);
		// 		Real y = centerY + r * sin(angle);
		// 		if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
		// 			heatMap[x][y] = heatMapParams.maxTemperature - spacing * r;
		// 		}
		// 	}
		// }
	}
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	initHeatMap();
}

void FireEvacuationLoopFunctions::PreStep() {
	// bool redraw = false;

	// // Increase the temperature of the fire
	// for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
	// 	for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
	// 		if(heatMap[x][y] != 0 && heatMap[x][y] != heatMapParams.maxTemperature) {
	// 			if(heatMap[x][y] + 5 < heatMapParams.maxTemperature) {
	// 				heatMap[x][y] += 5;
	// 			} else {
	// 				heatMap[x][y] = heatMapParams.maxTemperature;
	// 			}
	// 			redraw = true;
	// 		}
	// 	}
	// }

	// // Spread the fire
	// // TODO

	// // Redraw the floor texture
	// if(heatMapParams.showTemperature && redraw) {
	// 	floorEntity->SetChanged();
	// }
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// Get the heatmap indices and temperature that belong to this floor position
	int indexX = (positionOnFloor.GetX() + arenaSize->GetX()/2) * heatMapParams.tilesPerMeter;
	int indexY = (positionOnFloor.GetY() + arenaSize->GetY()/2) * heatMapParams.tilesPerMeter;
	int temperature = MAX_POSSIBLE_TEMPERATURE / heatMapParams.maxTemperature * heatMap[indexX][indexY];

	// If the temperature shouldn't be shown return no temperature, otherwise return a grayscale color depending on the temperature
	if(!heatMapParams.showTemperature) {
		temperature = 0;
	}

	// Invert the temperature to make white = no temperature and black = max temperature
	temperature = MAX_POSSIBLE_TEMPERATURE - temperature;
	
	return CColor(temperature, temperature, temperature);

	// Calculate the red, green and blue components of the color	
	// int red = 0;
	// int green = 0;
	// int blue = 0;
	// if(temperature == 0) {
	// 	red = 209;
	// 	green = 209;
	// 	blue = 209;
	// } else if(temperature < 128) {
	// 	green = 255;
	// 	red = temperature*2;
	// } else {
	// 	red = 255;
	// 	green = 255 - (temperature*2 - 255);
	// }
	// return CColor(red, green, blue);
}

void FireEvacuationLoopFunctions::initHeatMap() {
	// Initialize the heatmap to debug the resolution
	if(heatMapParams.debugMode == "resolution") {
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = heatMapParams.maxTemperature * ((x+y)%2);
			}
		}
	}
	// Initialize the heatmap to debug the gradient
	else if(heatMapParams.debugMode == "gradient") {
		Real spacing = heatMapParams.maxTemperature / (arenaSize->GetX()*heatMapParams.tilesPerMeter - 1);
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