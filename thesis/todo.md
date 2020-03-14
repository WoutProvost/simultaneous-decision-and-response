- Heatmap params?
- Extra debug model: vuurcirkel met eventuele wijzigbare radius of gebaseerd op echt vuur van een heatmap afbeelding
heatmap init


footbot_foraging.cpp: CalculateVectorToLight & SetWheelSpeedsFromVector
- Use state machine.
- Update diffusion en wheel code met die van in foraging.
- Op basis van de intensiteit dat een temperatuur sensor bot op een bepaalde plaats ondervindt, kan je die vloertegel zo instellen op de heatmap.
- Intensiteit licht vergroot met tijd?
- Probleem met een licht, is dat je geen andere blobs meer kan gebruiken voor andere doelen. Mss zelf een entiteit en sensor ontwikkelen?
- Alternatief is om af te gaan van de heatmap, en zo ground sensors te gebruiken als temperatuursensors.
- Aan de hand van de ground sensoren (2 vanvoor en 2 vanachter) kan je bepalen naar waar een robot verder kan rijden. Niet naar een warmere tegel. En als alle 4 op dezelfde tegel, neem dan random richting en kijk of er naar een plek die kouder is kan gegaan worden. Zijn er geen andere tegels die kouder zijn (bv bij begin als een robot op een rode tegel spawnt, maar kan vermeden worden door met een loop functie pas het vuur te starten op een plaats waar geen robot is) dan zit de robot vast.
- Als je argos random seed neemt, gebruikt die dan de seed van in de configuration file?
- Een fireDetected variabele moet in de Reset functie gereset worden!

- Grippers: objecten zoeken en vastnemen
- Sensors: uitgang zoeken
- Footbot motor ground sensor: useful for detecting changes in color on the ground.
- A and B choice can be differentiated by different colored lights

# TODO
- Zie dat de camera van de sensor bots, het vuur negeert.
- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because they manouvering of the bots doesn't have much to do with the thesis novelty
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Heatmap + ground sensors (bottom sensors with gradient)
- Based on what data does each individual robot decide, proximity to exit?
- Once the bots have exited the gate hey should go as fare away as possible from the fire
- Dynamic example: the fire should spread according to random seed in configuration file, wether to spread is toggleable by configuration file





















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
- **Velocity:** 5
- **Max angle between heading and obstacle:** 5
- **Max obstacle proximity:** 0.1
- **Leds color:** black
- **RaB range:** 3
- **RaB data size:** 10
- **Max force:** 15
- **Max torque:** 150
## Temperature sensing footbots:
- **Velocity:** 5
- **Max angle between heading and obstacle:** 5
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