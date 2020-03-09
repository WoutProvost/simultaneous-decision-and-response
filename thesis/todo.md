- argos -q prototype

- Custom ending with loop function (all robots safe), or use predetermined time length?
- Use random seed for same results or let the time be used?
- Simulation step => CCI_Controller::Step()
- Params => CCI_Controller::Init()
- Controller en loop/user functions macros
- Sensors, actuators en params in <my_controller>
- Velocity based control with differential_steering actuator (foot-bot & e-puck), set max force and max torque in <dynamics2d> of <foot-bot> of <arena>.
- Pas /path/to/blabla aan in example.argos
- Configure media
- Configure loop functions
- Configure user functions
- Andere example controllers en loop functions bekijken
- Verwijder eventueel overbodige attributen in .argos
- Movable gates enkel movable door grippers (niet pushen dus, want anders zouden de andere bots dit ook kunnen bewegen, of niet?)
- It is possible to add any number of colored LEDs to the box. In this way,
the box is visible with a robot camera. The position and color of the
LEDs is specified with the following syntax: argos3 -q box
- Heatmap + ground sensors (bottom sensors with gradient)
- Sensors need noise?

# Useful
- Communication by transmitting and detecting LEDs: synchronization.argos
- Gripper bots and movable objects using a simple time-based logic: gripping.argos
- Custom trajectory drawing, loop and user functions: trajectory.argos
- Custom labels drawing with user function: id.argos
- Bottom sensors, floor textures, complete experiment, loop functions with params, user functions: foraging.argos
- Bots botsen niet tegen elkaar, maar ontwijken elkaar en obstakels: epuck_obstacleavoidance.argos

# TODO
- Gripping bots should have proximity sensors as well.
- Gripping bots should have a speed variable as well.
- Communicate with LEDs?
- Do the gripping bots know the location of the gates or is this discovered by the swarm?
- Represent fire with light source, or with a changing floor texture depending on the temperature (sensed by the bots)?
- Distribute fire using random seed?
- The fire should spread?
- Once the bots have exited the gate, should they go to a predetermined location or just as far away from the fire as possible? As fare away as possible.
- Draw A and B choice textures/labels
- Arena size should pack 500 and use 100.