#include "FireEvacuationLoopFunctions.h"
#include <argos3/plugins/simulator/entities/light_entity.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include "../controllers/FootBotTemperatureSensingController.h"
#include "../controllers/FootBotGateGrippingController.h"

using std::endl;
using std::hex;
using std::dec;
using std::next;

FireEvacuationLoopFunctions::FireEvacuationLoopFunctions() :
	// Initialize attributes and set default values
	space(&GetSpace()),
	arenaSize(&space->GetArenaSize()),
	random(CRandom::CreateRNG("argos")),
	temperatureSensingFootBots(0),
	gateGrippingFootBots(0) {
}

const HeatMapParams& FireEvacuationLoopFunctions::getHeatMapParams() const {
	return heatMapParams;
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
	try {
		logParams.setParams(GetNode(configurationNode, "log"));
	} catch(CARGoSException &ex) {
	}

	// Initialize the floor entity
	floorEntity = &space->GetFloorEntity();

	// Initialize the physics engine
	physicsEngine = CSimulator::GetInstance().GetPhysicsEngines()[0];

	// Set the size of the heatmap depending on the size of the arena and the resolution depending on the tiles per meter
	Real resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
	Real resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY));

	// Initialize the heatmap with temperatures
	initHeatMap();

	// Get the amount of temperature sensing robots and gate gripping robots
	CSpace::TMapPerType &footBotEntities = space->GetEntitiesByType("foot-bot");
	for(CSpace::TMapPerType::iterator it = footBotEntities.begin(), end = footBotEntities.end(); it != end; it++) {
		CFootBotEntity &footBotEntity = *any_cast<CFootBotEntity*>(it->second);
		if(dynamic_cast<FootBotTemperatureSensingController*>(&footBotEntity.GetControllableEntity().GetController()) != nullptr) {
			temperatureSensingFootBots++;
		} else {
			gateGrippingFootBots++;
		}
	}

	// Get the colors of the lights at the exits
	string prefix("exit_light_");
	CSpace::TMapPerType &lightEntities = space->GetEntitiesByType("light");
	for(CSpace::TMapPerType::iterator it = lightEntities.begin(), end = lightEntities.end(); it != end; it++) {
		CLightEntity &lightEntity = *any_cast<CLightEntity*>(it->second);
		if(lightEntity.GetId().compare(0, prefix.length(), prefix) == 0) {
			CColor color = lightEntity.GetColor();
			temperatureSensingPreferences[color] = 0;
			gateGrippingActions[color] = 0;
		}
	}

	// Add one extra color for an undecided preference
	temperatureSensingPreferences[CColor::BLACK] = 0;
	gateGrippingActions[CColor::BLACK] = 0;

	// Log some of these settings to a file
	if(!logParams.disable) {
		logFile.open(logParams.file);
		if(logFile.is_open()) {
			initLogFile();
		} else {
			LOGERR << "Unable to open file '" << logParams.file << "'." << endl;
		}
	}
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	initHeatMap();

	// Reset the preference data to its initial state
	for(map<uint32_t,int>::iterator it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		it->second = 0;
	}
	for(map<uint32_t,int>::iterator it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
		it->second = 0;
	}

	// Close and reopen the logfile to erase everything and start from scratch
	if(!logParams.disable) {
		if(logFile.is_open()) {
			logFile.close();
		}
		logFile.open(logParams.file);
		if(logFile.is_open()) {
			initLogFile();
		}
	}
}

void FireEvacuationLoopFunctions::Destroy() {
	// Close the log file
	if(!logParams.disable) {
		if(logFile.is_open()) {
			logFile.close();
		}
	}
}

void FireEvacuationLoopFunctions::PreStep() {
	// Increase the temperature of the fire
	// Redrawing the floor is very resource intensive so this shouldn't happen too often
	// Even though this function is called PRE-step, the simulation clock is already incremented, so there's no problem with the modulo operator leading to an immediate redraw after initialization
	if(fireParams.isDynamic && space->GetSimulationClock() % fireParams.dynamicIntervalTicks == 0) {
		bool anyTileChanged = false;

		// for(int source = 0; source < fireParams.sources; source++) {
		// }

		// Redraw the floor texture if necessary
		if(anyTileChanged) {
			floorEntity->SetChanged();
		}
	}

	// // dynamic_spread_direction?
	// // Max fire size?

	// static Real radius = 0;
	// if(radius != fireParams.circleRadius * heatMapParams.tilesPerMeter + 1) {	
	// 	radius++;
	// }

	// // Copy the heatmap, since the radius and angle loops can access an array element multiple times and thus increase the temperature too much
	// vector<vector<int>> oldHeatMap = heatMap;

	// for(Real r = radius; r >= 0.0; r -= 0.1) {
	// 	for(Real angle = 0.0; angle < 360.0; angle += 0.1) {
	// 		Real x = centerX + r * cos(angle);
	// 		Real y = centerY + r * sin(angle);

	// 		// Spread the fire and increase the temperature
	// 		if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
	// 			if(heatMap[x][y] != heatMapParams.maxTemperature) {
	// 				if(oldHeatMap[x][y] + fireParams.dynamicTemperatureIncrease < heatMapParams.maxTemperature) {
	// 					heatMap[x][y] = oldHeatMap[x][y] + fireParams.dynamicTemperatureIncrease;
	// 				} else {
	// 					heatMap[x][y] = heatMapParams.maxTemperature;
	// 				}
	// 				anyTileChanged = true;
	// 			}
	// 		}
	// 	}
	// }



	// 	Real resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
	// 	Real resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
	// 	int centerX = random->Uniform(CRange<int>(0, resolutionX-1));
	// 	int centerY = random->Uniform(CRange<int>(0, resolutionY-1));
	
	// Real radius = fireParams.circleRadius * heatMapParams.tilesPerMeter;
	// Real spacing = heatMapParams.maxTemperature / radius;
}

void FireEvacuationLoopFunctions::PostStep() {
	// Gather the preference data
	CSpace::TMapPerType &footBotEntities = space->GetEntitiesByType("foot-bot");
	for(CSpace::TMapPerType::iterator it = footBotEntities.begin(), end = footBotEntities.end(); it != end; it++) {
		CFootBotEntity &footBotEntity = *any_cast<CFootBotEntity*>(it->second);
		CCI_Controller *controller = &footBotEntity.GetControllableEntity().GetController();
		FootBotTemperatureSensingController *footBotTemperatureSensingController = dynamic_cast<FootBotTemperatureSensingController*>(controller);
		if(footBotTemperatureSensingController != nullptr) {
			CColor color = footBotTemperatureSensingController->getPreferredExitLightColor();
			temperatureSensingPreferences[color]++;
		}
		FootBotGateGrippingController *footBotGateGrippingController = dynamic_cast<FootBotGateGrippingController*>(controller);
		if(footBotGateGrippingController != nullptr) {
			CColor color = footBotGateGrippingController->getActingExitLightColor();
			gateGrippingActions[color]++;
		}
	}

	// Log this data to a file
	if(!logParams.disable) {
		if(logFile.is_open()) {
			logFile << space->GetSimulationClock()*1000*physicsEngine->GetSimulationClockTick();
			for(map<uint32_t,int>::iterator it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
				logFile << "," << static_cast<Real>(it->second)/temperatureSensingFootBots;
			}
			for(map<uint32_t,int>::iterator it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
				logFile << "," << static_cast<Real>(it->second)/gateGrippingFootBots;
			}
			logFile << endl;
		}
	}

	// Clear the data for the next step
	for(map<uint32_t,int>::iterator it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		it->second = 0;
	}
	for(map<uint32_t,int>::iterator it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
		it->second = 0;
	}
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// Get the heatmap indices and temperature that belong to this floor position
	// For an arenaSize of 15 meters along one axis, the positionOnFloor sits in the range [-7.5:7.49] instead of [-7.5:7.5], so we won't have an off-by-one error in the array
	Real indexX = (positionOnFloor.GetX() + arenaSize->GetX()/2) * heatMapParams.tilesPerMeter;
	Real indexY = (positionOnFloor.GetY() + arenaSize->GetY()/2) * heatMapParams.tilesPerMeter;
	int temperature = MAX_POSSIBLE_TEMPERATURE / heatMapParams.maxTemperature * heatMap[indexX][indexY];

	// While debugging, calculate the red, green and blue components of the color
	if(heatMapParams.debugUseColors) {
		int red = 0;
		int green = 0;
		int blue = 0;
		if(heatMapParams.debugMode == "none" && temperature == 0) {
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
		temperature = MAX_POSSIBLE_TEMPERATURE - temperature;
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
					heatMap[x][y] = round(spacing * x);
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
	// Otherwise create a fire according to the fire parameters and according to whether it is dynamic
	else {
		// Initialize the heatmap to have no temperature
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = 0;
			}
		}

		// Create a circular fire at a random position
		for(int source = 0; source < fireParams.sources; source++) {
			Real resolutionX = arenaSize->GetX() * heatMapParams.tilesPerMeter;
			Real resolutionY = arenaSize->GetY() * heatMapParams.tilesPerMeter;
			int centerX = random->Uniform(CRange<int>(0, resolutionX-1));
			int centerY = random->Uniform(CRange<int>(0, resolutionY-1));

			// Create a linear gradient when the fire is static
			if(!fireParams.isDynamic) {
				// Copy the heatmap, since the radius and angle loops can access an array element multiple times and thus increase the temperature too much
				vector<vector<int>> oldHeatMap = heatMap;
				
				Real radius = fireParams.circleRadius * heatMapParams.tilesPerMeter;
				Real spacing = heatMapParams.maxTemperature / radius;
				for(Real r = radius; r >= 0.0; r -= 0.1) {
					for(Real angle = 0.0; angle < 360.0; angle += 0.1) {
						Real x = centerX + r * cos(angle);
						Real y = centerY + r * sin(angle);
						if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
							if(heatMap[x][y] != heatMapParams.maxTemperature) {
								int temperatureIncrease = round(heatMapParams.maxTemperature - spacing * r);
								if(oldHeatMap[x][y] + temperatureIncrease < heatMapParams.maxTemperature) {
									heatMap[x][y] = oldHeatMap[x][y] + temperatureIncrease;
								} else {
									heatMap[x][y] = heatMapParams.maxTemperature;
								}
							}
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

void FireEvacuationLoopFunctions::initLogFile() {
	logFile << "# available-options;graph-colors-in-hex" << endl;
	logFile << "! " << temperatureSensingPreferences.size();
	for(map<uint32_t,int>::iterator it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		logFile << ",#" << hex << it->first;
	}
	logFile << dec << endl;
	logFile << "# milliseconds;data-percentages" << endl;
	logFile << 0;
	logFile << "," << 1;
	for(map<uint32_t,int>::iterator it = next(temperatureSensingPreferences.begin(),1), end = temperatureSensingPreferences.end(); it != end; it++) { // Start the iterator 1 element further
		logFile << "," << 0;
	}
	logFile << "," << 1;
	for(map<uint32_t,int>::iterator it = next(gateGrippingActions.begin(),1), end = gateGrippingActions.end(); it != end; it++) { // Start the iterator 1 element further
		logFile << "," << 0;
	}
	logFile << endl;
}

// Macro that binds this class to an XML tag
REGISTER_LOOP_FUNCTIONS(FireEvacuationLoopFunctions, "fire_evacuation_loop_functions")