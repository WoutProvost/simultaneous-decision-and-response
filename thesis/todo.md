footbot_foraging.cpp: CalculateVectorToLight & SetWheelSpeedsFromVector
footbot_flocking.cpp 153: enkel een bepaalde kleur detecteren, moet niet met light sensor of camera, maar met colored blob camera
Use state machine.
Update diffusion en wheel code met die van in foraging.
Verander kleur van light met de temperatuur? Intensiteit light vergroot met tijd?
Nu kunnen alle sensors vanop elke afstand het vuur detecteren.

- Grippers: objecten zoeken en vastnemen
- Sensors: uitgang zoeken
- Footbot motor ground sensor: useful for detecting changes in color on the ground.
- A and B choice can be differentiated by different colored lights

# TODO
- Example loop functions bekijken
- Zie dat de camera van de sensor bots, het vuur negeert.
- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because they manouvering of the bots doesn't have much to do with the thesis novelty
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Heatmap + ground sensors (bottom sensors with gradient)
- Based on what data does each individual robot decide, proximity to exit?
- Once the bots have exited the gate hey should go as fare away as possible from the fire
- Dynamic example: the fire should spread according to random seed in configuration file, wether to spread is toggleable by configuration file





















/*
// Degrees start from north heading and go counter-clockwise

// Verkrijg float uit configuration file en maak er graden van
CDegrees degrees = CDegrees(Real value);
// Converteer graden naar radialen
CRadians radians = ToRadians(degrees);
// Maak een range van de radialen
CRange<CRadians> range = doNotTurnAngleRange(-radians, radians);

// Verkrijg readings van de sensor
vector<SReading> readings = GetReadings();
// Elke reading bevat een length en een angle
SReading reading = SReading(Real value, CRadians angle);
CVector2 vector = CVector2(Real length, CRadians angle);



// Vector addition (magnitude, degrees)
(0.5, 7.5) + (0.8, 22.5) = (1.2895, 16.74)

// Vector division by scalar
(1.2895, 16.74) / 2 = (0.64475, 16.74)
*/



# Questions and ideas
- Do sensors need noise and the RaB sensor packet drop?
- Show a (live) graphical view of the collective decision and collective response (example: linux system monitor). Log the data from this graph.

# Settings
## Important settings
- Robot velocity
- Robot RaB range
- Fire light intensity
- RaB medium check occlusions
The rest of the settings are default.
## Random number generator
- **Seed:** 12345
## Arena
- **Size:** 15x15x1
## Gate gripping footbots:
- **Show proximity sensor rays:** true
- **Show range and bearing sensor rays:** true
- **Show colored blob omnidirectional camera sensor rays:** true
- **Velocity:** 5
- **Max angle between heading and obstacle:** 7.5
- **Max obstacle proximity:** 0.1
- **Leds color:** black
- **RaB range:** 3
- **RaB data size:** 10
- **Max force:** 15
- **Max torque:** 150
## Temperature sensing footbots:
- **Show proximity sensor rays:** true
- **Show range and bearing sensor rays:** true
- **Show light sensor rays:** true
- **Velocity:** 5
- **Max angle between heading and obstacle:** 7.5
- **Max obstacle proximity:** 0.1
- **Leds color:** white
- **RaB range:** 3
- **RaB data size:** 10
- **Max force:** 15
- **Max torque:** 150
## Movable gates:
- **Radius:** 0.1
- **Height:** 0.2
- **Mass:** 0.1
## Fire light
- **Color:** yellow
- **Intensity:** 1.0
## Physics engine
- **Box linear friction:** 1.49
- **Box angular friction:** 1.49
- **Cylinder linear friction:** 1.49
- **Cylinder angular friction:** 1.49
## RaB medium
- **Check occlusions:** true

# Documentation
- CDynamics2DFootBotModel: https://www.argos-sim.info/api/a00521_source.php
- CCI_Controller: https://www.argos-sim.info/api/a02036.php
- CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
- CCI_LEDsActuator: https://www.argos-sim.info/api/a02840.php
- CCI_RangeAndBearingActuator: https://www.argos-sim.info/api/a02896.php
- CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
- CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
- CCI_RangeAndBearingSensor: https://www.argos-sim.info/api/a02900.php
- CCI_FootBotLightSensor: https://www.argos-sim.info/api/a02640.php
- CCI_ColoredBlobOmnidirectionalCameraSensor: https://www.argos-sim.info/api/a02792.php

# Performance notes
- For larger swarms, turning the light sensor of when you don't need it.
- For larger swarms, turning the camera sensor of when you don't need it.
- For less than 100 robots, thread management is not beneficial.
- For swarms larger than 50 robots and/or large arenas, multiple physics engines should be used.
- Use the same number of threads as there are physics engines and take into account the amount of CPU cores.