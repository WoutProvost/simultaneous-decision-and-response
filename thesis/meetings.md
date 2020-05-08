# Tuesday 12-05-2020
- 

# Tuesday 5-05-2020
- Add a new movement mode: turn in a random direction every x timesteps to break up the grouping and mix the system better
- Determine the exit probability: how many times you exit with correct solution
- Test with 6 tiles per meter to position a fire exactly on the divider line
- Test with changing values of the gripper parameters
- Test with a runtime of 10 minutes
- Test with more than 1 fire source

# Tuesday 28-04-2020
- Add random voting model that just takes the opinion of a random neighbour
- Read additional article for the weighted voter model
- Use two parameters for the gripper reaction mechanism: percentage and timesteps
- The gripper starts acting when a percentage x holds for y amount of time

# Tuesday 21-04-2020
- No meeting

# Tuesday 14-04-2020
- No meeting

# Tuesday 7-04-2020
- Determine when to start the collective response so that it is most efficient
- Majority rule: the grippers use the data received from their sensing neighbours
- When working with data from neighbours, use a quorum to determine what to do
- Weighted balance between distance and temperature, since a fire that's not very hot but very close to one exit, might or might not be that bad
- Sensor move randomly to detect fires and aggregate
- Maybe use fire edge detection
- Start building edge, but abandon when not enough robots participate (use probabilities)
- Grippers also move to detect the edges being formed

# Tuesday 31-03-2020
- Distance method: measure the distance of the fire to the exits
- Fire spreading method: measure how fast the fire could reach the exits
- Determine which exit is closer to the center of mass of the swarm (only useful when the swarm is not uniformly divided)

# Tuesday 24-03-2020
- Migrate git repository from GitHub to UGent GitHub Enterprise
- Get access to the UGent cluster, email PHD student for credentials
- Implement mode with multiple fires before mode with dynamic fire
- Use RaB range of 1 meter
- Use 1 tile per robot width (= 5 tiles per meter)
- Try implementing the individual decision, changing decision and individual reaction mechanisms
- Try implementing some voting strategies

# Tuesday 17-03-2020
- No meeting

# Thursday 12-03-2020
- No meeting

# Thursday 5-03-2020
- No meeting

# Thursday 27-02-2020
- Implement the static scenario (see picture from whiteboard)
- Heatmap + ground sensors (bottom sensors with gradient)

# Thursday 13-02-2020
- No meeting

# Thursday 20-02-2020
- No meeting

# Friday 7-02-2020
- Think of a scenario to implement
- Experiment with ARGoS
- Search for additional articles