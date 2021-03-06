#include "FireEvacuationLoopFunctions.h"
#include <argos3/plugins/simulator/entities/light_entity.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include "../controllers/TemperatureSensingFootBotController.h"
#include "../controllers/GateGrippingFootBotController.h"
#include <cmath>

using std::endl;
using std::isnan;
using std::hex;
using std::setw;
using std::setfill;
using std::dec;
using std::next;

FireEvacuationLoopFunctions::FireEvacuationLoopFunctions() :
	// Initialize attributes and set default values
	space(&GetSpace()),
	random(CRandom::CreateRNG("argos")),
	temperatureSensingFootBots(0),
	gateGrippingFootBots(0) {
}

const NestParams& FireEvacuationLoopFunctions::getNestParams() const {
	return nestParams;
}

const HeatMapParams& FireEvacuationLoopFunctions::getHeatMapParams() const {
	return heatMapParams;
}

void FireEvacuationLoopFunctions::Init(TConfigurationNode &configurationNode) {
	// Parse the configuration file for params
	try {
		nestParams.setParams(GetNode(configurationNode, "nest"));
	} catch(CARGoSException &ex) {
	}
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

	// Set the size of the heatmap depending on the size of the nest and the resolution depending on the tiles per meter
	Real resolutionX = nestParams.getSize().GetX() * heatMapParams.getTilesPerMeter();
	Real resolutionY = nestParams.getSize().GetY() * heatMapParams.getTilesPerMeter();
	heatMap = vector<vector<int>>(resolutionX, vector<int>(resolutionY));

	// Initialize the heatmap with temperatures
	initHeatMap();

	// Get the amount of temperature sensing robots and gate gripping robots
	CSpace::TMapPerType &footBotEntities = space->GetEntitiesByType("foot-bot");
	for(auto it = footBotEntities.begin(), end = footBotEntities.end(); it != end; it++) {
		CFootBotEntity &footBotEntity = *any_cast<CFootBotEntity*>(it->second);
		CCI_Controller *controller = &footBotEntity.GetControllableEntity().GetController();
		TemperatureSensingFootBotController *temperatureSensingFootBotController = dynamic_cast<TemperatureSensingFootBotController*>(controller);
		if(temperatureSensingFootBotController != nullptr) {
			temperatureSensingFootBots++;
		}
		GateGrippingFootBotController *gateGrippingFootBotController = dynamic_cast<GateGrippingFootBotController*>(controller);
		if(gateGrippingFootBotController != nullptr) {
			gateGrippingFootBots++;
		}
	}

	// Get the colors of the lights at the exits
	string prefix("exit_light_");
	CSpace::TMapPerType &lightEntities = space->GetEntitiesByType("light");
	for(auto it = lightEntities.begin(), end = lightEntities.end(); it != end; it++) {
		CLightEntity &lightEntity = *any_cast<CLightEntity*>(it->second);
		if(lightEntity.GetId().compare(0, prefix.length(), prefix) == 0) {
			CColor color = lightEntity.GetColor();
			temperatureSensingPreferences[color] = 0;
			gateGrippingActions[color] = 0;
			exitColors[color] = color;
		}
	}

	// Add one extra color for an undecided preference
	temperatureSensingPreferences[CColor::BLACK] = 0;
	gateGrippingActions[CColor::BLACK] = 0;
	exitColors[CColor::BLACK] = CColor::BLACK;

	// Log some of these settings to a file
	if(!logParams.getDisable()) {
		logFile.open(logParams.getFile());
		if(logFile.is_open()) {
			initLogFile();
		} else {
			LOGERR << "Unable to open file '" << logParams.getFile() << "'." << endl;
		}
	}
}

void FireEvacuationLoopFunctions::Reset() {
	// Reset the heatmap to its initial state
	initHeatMap();

	// Reset the preference data to its initial state
	for(auto it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		it->second = 0;
	}
	for(auto it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
		it->second = 0;
	}

	// Close and reopen the logfile to erase everything and start from scratch
	if(!logParams.getDisable()) {
		if(logFile.is_open()) {
			logFile.close();
		}
		logFile.open(logParams.getFile());
		if(logFile.is_open()) {
			initLogFile();
		}
	}
}

void FireEvacuationLoopFunctions::Destroy() {
	// Close the log file
	if(!logParams.getDisable()) {
		if(logFile.is_open()) {
			logFile.close();
		}
	}
}

void FireEvacuationLoopFunctions::PostStep() {
	// Gather the preference data
	CSpace::TMapPerType &footBotEntities = space->GetEntitiesByType("foot-bot");
	for(auto it = footBotEntities.begin(), end = footBotEntities.end(); it != end; it++) {
		CFootBotEntity &footBotEntity = *any_cast<CFootBotEntity*>(it->second);
		CCI_Controller *controller = &footBotEntity.GetControllableEntity().GetController();
		TemperatureSensingFootBotController *temperatureSensingFootBotController = dynamic_cast<TemperatureSensingFootBotController*>(controller);
		if(temperatureSensingFootBotController != nullptr) {
			CColor color = temperatureSensingFootBotController->getPreferredExitLightColor();
			temperatureSensingPreferences[color]++;
		}
		GateGrippingFootBotController *gateGrippingFootBotController = dynamic_cast<GateGrippingFootBotController*>(controller);
		if(gateGrippingFootBotController != nullptr) {
			CColor color = gateGrippingFootBotController->getActingExitLightColor();
			gateGrippingActions[color]++;
		}
	}

	// Log this data to a file
	if(!logParams.getDisable()) {
		if(logFile.is_open()) {
			logFile << space->GetSimulationClock()*1000*physicsEngine->GetSimulationClockTick();
			for(auto it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
				logFile << "," << static_cast<Real>(it->second)/temperatureSensingFootBots;
			}
			for(auto it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
				logFile << "," << static_cast<Real>(it->second)/gateGrippingFootBots;
			}
			logFile << endl;
		}
	}

	// Clear the data for the next step
	for(auto it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		it->second = 0;
	}
	for(auto it = gateGrippingActions.begin(), end = gateGrippingActions.end(); it != end; it++) {
		it->second = 0;
	}
}

CColor FireEvacuationLoopFunctions::GetFloorColor(const CVector2 &positionOnFloor) {
	// If the floor position coordinates are within the nest
	Real nestBoundX = nestParams.getSize().GetX()/2;
	Real nestBoundY = nestParams.getSize().GetY()/2;
	if(positionOnFloor.GetX() >= -nestBoundX && positionOnFloor.GetX() < nestBoundX && positionOnFloor.GetY() >= -nestBoundY && positionOnFloor.GetY() < nestBoundY) {
		// Get the heatmap indices and temperature that belong to this floor position
		// For a nest size of 15 meters along one axis, the positionOnFloor sits in the range [-7.5:7.49] instead of [-7.5:7.5], so we won't have an off-by-one error in the array
		Real indexX = (positionOnFloor.GetX() + nestParams.getSize().GetX()/2) * heatMapParams.getTilesPerMeter();
		Real indexY = (positionOnFloor.GetY() + nestParams.getSize().GetY()/2) * heatMapParams.getTilesPerMeter();
		int temperature = static_cast<Real>(MAX_POSSIBLE_TEMPERATURE) / heatMapParams.getMaxTemperature() * heatMap[indexX][indexY];

		// While debugging, calculate the red, green and blue components of the color
		if(heatMapParams.getDebugUseColors()) {
			int red = 0;
			int green = 0;
			int blue = 0;
			if(heatMapParams.getDebugMode() == "none" && temperature == 0) {
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
	// Otherwise return a gray color
	else {
		return CColor(209, 209, 209);
	}
}

void FireEvacuationLoopFunctions::initHeatMap() {
	// While debugging, initialize the heatmap with predetermined temperatures
	if(heatMapParams.getDebugMode() != "none") {
		// Initialize the heatmap to debug the resolution
		if(heatMapParams.getDebugMode() == "resolution") {
			for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
				for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
					heatMap[x][y] = heatMapParams.getMaxTemperature() * ((x+y)%2);
				}
			}
		}
		// Initialize the heatmap to debug the gradient
		else if(heatMapParams.getDebugMode() == "gradient") {
			Real spacing = heatMapParams.getMaxTemperature() / (nestParams.getSize().GetX()*heatMapParams.getTilesPerMeter() - 1);
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
	// Otherwise create a fire according to the fire parameters
	else {
		// Initialize the heatmap to have no temperature
		for(size_t x = 0, sizeX = heatMap.size(); x < sizeX; x++) {
			for(size_t y = 0, sizeY = heatMap[x].size(); y < sizeY; y++) {
				heatMap[x][y] = 0;
			}
		}

		// Create a circular fire at a random position
		const vector<CVector2> &positions = fireParams.getPositions();
		for(int source = 0; source < fireParams.getSources(); source++) {
			Real resolutionX = nestParams.getSize().GetX() * heatMapParams.getTilesPerMeter();
			Real resolutionY = nestParams.getSize().GetY() * heatMapParams.getTilesPerMeter();
			int centerX = random->Uniform(CRange<UInt32>(0, resolutionX)); // Interval is [min,max) i.e. right-open
			int centerY = random->Uniform(CRange<UInt32>(0, resolutionY)); // Interval is [min,max) i.e. right-open

			// Use a fixed source position if it is provided and is not outside the range of the heatmap array
			// For a nest size of 15 meters along one axis with 5 tiles per meter, the coordinate range [-7.5:7.49] maps to the index range [0:74]
			// So the coordinate value 7.5 will result in an off-by-one error in the array
			const CVector2 &position = positions[source];
			if(!isnan(position.GetX()) && !isnan(position.GetY())) {
				int indexX = (position.GetX() + nestParams.getSize().GetX()/2) * heatMapParams.getTilesPerMeter();
				int indexY = (position.GetY() + nestParams.getSize().GetY()/2) * heatMapParams.getTilesPerMeter();
				if(indexX >= 0 && indexX < heatMap.size() && indexY >= 0 && indexY < heatMap[0].size()) {
					centerX = indexX;
					centerY = indexY;
				}
			}

			// Copy the heatmap, since the radius and angle loops can access an array element multiple times and thus increase the temperature too much
			vector<vector<int>> oldHeatMap = heatMap;
			
			// Create a fire circle in which the temperature increases from the outside to the center using a linear gradient
			Real radius = fireParams.getCircleRadius() * heatMapParams.getTilesPerMeter();
			Real spacing = heatMapParams.getMaxTemperature() / radius;
			for(Real r = radius; r >= 0.0; r -= 0.1) {
				for(Real angle = 0.0; angle < 360.0; angle += 0.1) {
					Real x = centerX + r * cos(angle);
					Real y = centerY + r * sin(angle);
					if(x >= 0 && x < heatMap.size() && y >= 0 && y < heatMap[x].size()) {
						if(heatMap[x][y] != heatMapParams.getMaxTemperature()) {
							int temperatureIncrease = round(heatMapParams.getMaxTemperature() - spacing * r);
							if(oldHeatMap[x][y] + temperatureIncrease < heatMapParams.getMaxTemperature()) {
								heatMap[x][y] = oldHeatMap[x][y] + temperatureIncrease;
							} else {
								heatMap[x][y] = heatMapParams.getMaxTemperature();
							}
						}
					}
				}
			}
		}
	}
}

void FireEvacuationLoopFunctions::initLogFile() {
	logFile << "# available-options,graph-colors-in-hex" << endl;
	logFile << "! " << temperatureSensingPreferences.size();
	for(auto it = temperatureSensingPreferences.begin(), end = temperatureSensingPreferences.end(); it != end; it++) {
		// CColors converted to uint32_t and then printed out in hex will not reflect the actual color, so don't print it->first here, but extract the RGB components manually!
		logFile << ",#" << hex << setfill('0') << setw(2) << exitColors[it->first].GetRed() << setw(2) << exitColors[it->first].GetGreen() << setw(2) << exitColors[it->first].GetBlue() << dec;
	}
	logFile << endl;
	logFile << "# milliseconds,data-percentages" << endl;
	logFile << 0;
	logFile << "," << 1;
	for(auto it = next(temperatureSensingPreferences.begin(),1), end = temperatureSensingPreferences.end(); it != end; it++) { // Start the iterator 1 element further
		logFile << "," << 0;
	}
	logFile << "," << 1;
	for(auto it = next(gateGrippingActions.begin(),1), end = gateGrippingActions.end(); it != end; it++) { // Start the iterator 1 element further
		logFile << "," << 0;
	}
	logFile << endl;
}

// Macro that binds this class to an XML tag
REGISTER_LOOP_FUNCTIONS(FireEvacuationLoopFunctions, "fire_evacuation_loop_functions")