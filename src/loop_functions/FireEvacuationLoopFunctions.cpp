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

	// Initialize the floor entity
	floorEntity = &space->GetFloorEntity();

	// Set the size of the heatmap depending on the size of the arena and the resolution depending on the tiles per meter
	Real resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
	Real resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY));

	// Initialize the heatmap with temperatures
	initHeatMap();
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	initHeatMap();
}

void FireEvacuationLoopFunctions::PreStep() {
	// // Increase the temperature of the fire
	// if(fireParams.isDynamic && fireParams.mode == "circle") {
	// 	bool redraw = false;
	// 	static int ticks = 0;
	// 	static Real radius = 0;
	// 	int centerX = 4;
	// 	int centerY = 64;
	// 	ticks++;

	// 	// Redrawing the floor is very resource intensive so this shouldn't happen too often
	// 	if(ticks == fireParams.dynamicIntervalTicks) {
	// 		ticks = 0;

	// 		if(radius != fireParams.circleRadius * heatMapParams.tilesPerMeter + 1) {	
	// 			radius++;
	// 		}

	// 		for(Real r = 0; r <= radius; r += 0.1) {
	// 			for(Real angle = 0; angle < 360; angle += 0.1) {
	// 				Real x = centerX + r * cos(angle);
	// 				Real y = centerY + r * sin(angle);

	// 				// Spread the fire and increase the temperature
	// 				if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
	// 					if(heatMap[x][y] != heatMapParams.maxTemperature) {
	// 						if(heatMap[x][y] + fireParams.dynamicTemperatureIncrease < heatMapParams.maxTemperature) {
	// 							heatMap[x][y] += fireParams.dynamicTemperatureIncrease;
	// 						} else {
	// 							heatMap[x][y] = heatMapParams.maxTemperature;
	// 						}
	// 						redraw = true;
	// 					}
	// 				}
	// 			}
	// 		}

	// 		// Redraw the floor texture
	// 		if(heatMapParams.showTemperature && redraw) {
	// 			floorEntity->SetChanged();
	// 		}
	// 	}
	// }
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// Get the heatmap indices and temperature that belong to this floor position
	Real indexX = (positionOnFloor.GetX() + arenaSize->GetX()/2) * heatMapParams.tilesPerMeter;
	Real indexY = (positionOnFloor.GetY() + arenaSize->GetY()/2) * heatMapParams.tilesPerMeter;
	int temperature = MAX_POSSIBLE_TEMPERATURE / heatMapParams.maxTemperature * heatMap[indexX][indexY];

	// While debugging, calculate the red, green and blue components of the color
	if(heatMapParams.debugUseColors) {
		int red = 0;
		int green = 0;
		int blue = 0;
		if(!heatMapParams.showTemperature || (heatMapParams.debugMode == "none" && temperature == 0)) {
			red = 209;
			green = 209;
			blue = 209;
		} else {
			if(temperature < 128) {
				green = 255;
				red = temperature*2;
			} else {
				red = 255;
				green = 255 - (temperature*2 - 255);
			}
		}
		return CColor(red, green, blue);
	}
	// Otherwise invert the temperature to make white = no temperature and black = max temperature and return a grayscale color depending on the temperature
	else {
		if(!heatMapParams.showTemperature) {
			temperature = 209;
		} else {
			temperature = MAX_POSSIBLE_TEMPERATURE - temperature;
		}
		return CColor(temperature, temperature, temperature);
	}
}

void FireEvacuationLoopFunctions::initHeatMap() {
	// While debugging, initialize the heatmap with predetermined temperatures
	if(heatMapParams.debugMode != "none") {
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
	// Otherwise create a fire according to the fire mode and according to wether it is dynamic
	else {
		// Create a circular fire at a random position
		if(fireParams.mode == "circle") {
			Real resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
			Real resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
			int centerX = random->Uniform(CRange<int>(-resolutionX/2, resolutionX/2));
			int centerY = random->Uniform(CRange<int>(-resolutionY/2, resolutionY/2));

			// Create a linear gradient when the fire is static
			if(!fireParams.isDynamic) {
				Real radius = fireParams.circleRadius * heatMapParams.tilesPerMeter;
				Real spacing = heatMapParams.maxTemperature / radius;
				for(Real r = 0; r <= radius; r += 0.1) {
					for(Real angle = 0; angle < 360; angle += 0.1) {
						Real x = centerX + r * cos(angle);
						Real y = centerY + r * sin(angle);
						if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
							heatMap[x][y] = heatMapParams.maxTemperature - spacing * r;
						}
					}
				}
			}
			// Otherwise create a single tile where the fire should start to spread from
			else {
				heatMap[centerX][centerY] = heatMapParams.maxTemperature;
			}
		}
	}
}

// Macro that binds this class to an XML tag
REGISTER_LOOP_FUNCTIONS(FireEvacuationLoopFunctions, "fire_evacuation_loop_functions")