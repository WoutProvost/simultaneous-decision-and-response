- Heatmap params?
- Extra debug model: vuurcirkel met eventuele wijzigbare radius of gebaseerd op echt vuur van een heatmap afbeelding
- heatmap init
- Check of de ground sensor ook met groen, geel en rood kan werken of enkel met wit, grijs en zwart.
- Kijk of all sensors (en documentatie hieronder en in .conf file) nog nodig zijn.

See footbot_foraging.cpp for CalculateVectorToLight and SetWheelSpeedsFromVector methods.
- Use a state machine.
- Update diffusion and wheel code with the one from the foraging example.
- Temperature should increase with time?
- Depending on the readings of the ground sensors of the temperature sensing robots (2 in front, 2 in back) you can determine to where the robot should move. It shouldn't move to a tile that's warmer. If the robot happens to have it's 4 sensors on the same tile, or all sensors return the same temperature, try to move in a random direction and see if eventually the robot ends up on a cooler tile. If there are no cooler tiles around the robot the robot is stuck. This last scenario could happen when in the beginning the robot spawns on a hot tile, but this can be circumvented with a loop function by spawning the fire after a certain amount of time and on a tile that is not occupied by a robot.
- Check if the random generator in a loop function, with the 'argos' setting, uses the seed set in the configuration file.
- Don't forget to reset any variables in the appropriate Reset functions.

- Gripper robots: search for gates and grip them
- Sensor robots: search for an exit
- A and B choice can be differentiated by different colored lights to navigate to.

# TODO
- Movable gates enkel movable door grippers, nu kunnen de andere bots de gates ook pushen (force/torque/friction van sensors verlagen, of mass van objects verhogen en enkel de gripper genoeg force/torque geven) (wat met de proximity sensors van de grippers, diffusion uitzetten, of logica met als de afstand tot het licht boven de gate gelijk is aan de max proximitysensor rijkwijdte, dan niet uitwijken, op voorwaarde dat die gate werd beslist in de swarm)
- Gates vervangen door gound blobs die alleen door de grippers opgepakt kunnen worden?
- Solid gates disappear when gripped, because they manouvering of the bots doesn't have much to do with the thesis novelty
- Custom ending with loop function (all robots or large enough percentage are safe), or use predetermined time length?
- Based on what data does each individual robot decide, proximity to exit?
- Once the bots have exited the gate they should go as fare away as possible from the fire
- Dynamic example: the fire should spread according to random seed in configuration file, wether to spread is toggleable by configuration file





















# Questions and ideas
- Do sensors need noise and the RaB sensor packet drop?
- Show a (live) graphical view of the collective decision and collective response (example: linux system monitor). Log the data from this graph.

# Important configuration settings
- Robot velocity
- Robot RaB range
- RaB medium check occlusions
- Heatmap tiles per meter
- Heatmpa max temperature

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