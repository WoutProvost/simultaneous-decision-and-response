# Questions and ideas
- Do sensors need noise and the RaB sensor packet drop?
- Show a (live) graphical view of the collective decision and collective response (example: linux system monitor). Log the data from this graph.

# Settings
## Important settings
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
- CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
- CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
- CCI_RangeAndBearingSensor: https://www.argos-sim.info/api/a02900.php

# Performance notes
- For larger swarms, turning the light sensor of when you don't need it.
- For less than 100 robots, thread management is not beneficial.
- For swarms larger than 50 robots and/or large arenas, multiple physics engines should be used.
- Use the same number of threads as there are physics engines and take into account the amount of CPU cores.

footbot_flocking
footbot_foraging
footbot_synchronization
footbot_manualcontrol
footbot_nn

The color of the light is perceived by cameras.
The intensity of the light is perceived by light sensors.
Vuur maar doen opkomen na een tijd? Niet echt nodig door de random seed. By dynamisch natuurlijk wel nodig.
Verander kleur van light met de temperatuur?

# Subklassen
- Temperatuursensors: vuur detecteren
- Grippers: objecten vastnemen

# Actuators
- Distance scanner: set angle and speed of rotating scanner. Higher range than proximity sensor.

# Sensors
- Footbot distance scanner: read data of the scanner.
- Footbot base ground sensor: useful for detecting holes.
- Footbot motor ground sensor: useful for detecting changes in color on the ground.
- Footbot light sensor: detect lights.
- Differential steering: detect current position and orientation.
- Positioning: detect current position and orientation.
- Light sensor: detect lights.
- Cameras: detect different objects.
- Colored blob omnidirectional camera: detect led of other robots.
- Colored blob perspective camera: detect led of other robots.
- Ground: detect ground.

# TODO
- Andere example controllers en loop functions bekijken
- Movable gates enkel movable door grippers (niet pushen dus, want anders zouden de andere bots dit ook kunnen bewegen, of niet?)
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Heatmap + ground sensors (bottom sensors with gradient)
- Decisions might be influenced by random positioning of the robots, due to the random seed
- Based on what data does each individual robot decide?
- RAB heeft routing wss

# TODO 2
- Communicate with LEDs or radios?
- Do the gripping bots know the location of the gates or is this discovered by the swarm?
- Represent fire with light source, or with a changing floor texture depending on the temperature (sensed by the bots)?
- Distribute fire using random seed?
- The fire should spread?
- Once the bots have exited the gate, should they go to a predetermined location or just as far away from the fire as possible? As fare away as possible.
- Draw A and B choice textures/labels
- Arena size should pack 500 and use 100.
- Verwijder eventueel overbodige attributen en default values in .argos, nadat je ze wel hebt gedocumenteerd dan

# Useful
- Communication by transmitting and detecting LEDs: synchronization.argos
- Custom trajectory drawing, loop and user functions: trajectory.argos
- Custom labels drawing with user function: id.argos
- Bottom sensors, floor textures, complete experiment, loop functions with params, user functions: foraging.argos