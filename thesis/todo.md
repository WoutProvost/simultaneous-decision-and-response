# Questions and ideas
- Do sensors need noise and/or packet drop?
- Use default range and bearing settings?
- Show a (live) graphical view of the collective decision and collective response (example: linux system monitor). Log the data from this graph.

# Actuators and sensors
CDynamics2DFootBotModel: https://www.argos-sim.info/api/a00521_source.php
CCI_Controller: https://www.argos-sim.info/api/a02036.php
CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
CCI_LEDsActuator: https://www.argos-sim.info/api/a02840.php
CCI_RangeAndBearingActuator: https://www.argos-sim.info/api/a02896.php
CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
CCI_RangeAndBearingSensor: https://www.argos-sim.info/api/a02900.php

footbot_flocking
footbot_foraging
footbot_synchronization
footbot_manualcontrol
footbot_nn

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