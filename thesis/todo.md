- Depending on the readings of the ground sensors of the temperature sensing robots (2 in front, 2 in back) you can determine to where the robot should move. It shouldn't move to a tile that's warmer. If the robot happens to have it's 4 sensors on the same tile, or all sensors return the same temperature, try to move in a random direction and see if eventually the robot ends up on a cooler tile. If there are no cooler tiles around the robot the robot is stuck. This last scenario could happen when in the beginning the robot spawns on a hot tile, but this can be circumvented with a loop function by spawning the fire after a certain amount of time and on a tile that is not occupied by a robot. Or maybe the sensing robot should be allowed to drive over 'hot' spots, since it is only doing some sensing.

- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because the manouvering of the bots doesn't have much to do with the thesis novelty

- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Once the bots have exited the gate they should go as fare away as possible from the fire
- If we implement addition fire modes, each fire mode should have its own configuration node, so it's easier to have its own attributes


















# Done
- Movable gates
- 100 gripper robots (black leds) & 100 sensor robots (white leds)
- Base class controller with collision avoidance and roaming movement (mostly taken from foraging example)
- 2 subclasses for the 2 types of robots
- Fire not implemented as light, because this would conflict with lights used for navigation, heatmap with ground sensors used instead
- Sensor robots can only sense grayscale, but the colord heatmap works for debugging purposes
- Heatmap tiles_per_meter, max_temperature, gradient and resolution debug modes (show pictures or demonstrate)
- Static fire circle mode with circle_radius (show pictures or demonstrate)
- Plot using https://www.qt.io/ and https://www.qcustomplot.com/

# TODO
- Dynamic fire circle: dynamic_interval_ticks, dynamic_temperature_increase
- Gates: only removable by the gripper robots
- Gripper robots: search for gates and remove the gates and exit the arena
- Sensor robots: search for an exit and exit the arena
- Plot: show live data of the collective decision and collective response, also log the data from this graph in a file

# Questions and ideas
- Redrawing the floor is very resource intensive so only do this after a few ticks
- Additional fire modes: single spreading fire according to real life model or random seed, multiple spreading fires popping up at random time intervals
- Based on what data does each individual robot make its individual decision. Proximity to one of the exits? Is this proximity even possible to implement?
- A and B choice can be differentiated in the analysis by different colored lights to navigate to or by the direction of the vector to the light
- Do sensors need noise and the RaB sensor packet drop?

# Important configuration settings
- Robot velocity
- Robot RaB range & data size
- RaB medium check occlusions
- Heatmap tiles per meter & max temperature
- Fire interval ticks & temperature increase & circle radius

# Documentation
- CDynamics2DFootBotModel: https://www.argos-sim.info/api/a00521_source.php
- CCI_Controller: https://www.argos-sim.info/api/a02036.php
- CCI_DifferentialSteeringActuator: https://www.argos-sim.info/api/a02816.php
- CCI_LEDsActuator: https://www.argos-sim.info/api/a02840.php
- CCI_RangeAndBearingActuator: https://www.argos-sim.info/api/a02896.php
- CCI_FootBotGripperActuator: https://www.argos-sim.info/api/a02636.php
- CCI_FootBotProximitySensor: https://www.argos-sim.info/api/a02656.php
- CCI_RangeAndBearingSensor: https://www.argos-sim.info/api/a02900.php
- CCI_ColoredBlobOmnidirectionalCameraSensor: https://www.argos-sim.info/api/a02792.php
- CCI_FootBotLightSensor: https://www.argos-sim.info/api/a02640.php
- CCI_FootBotMotorGroundSensor: https://www.argos-sim.info/api/a02648.php

# Performance notes
- For larger swarms, turning the light sensor of when you don't need it.
- For larger swarms, turning the camera sensor of when you don't need it.
- For less than 100 robots, thread management is not beneficial.
- For swarms larger than 50 robots and/or large arenas, multiple physics engines should be used.
- Use the same number of threads as there are physics engines and take into account the amount of CPU cores.