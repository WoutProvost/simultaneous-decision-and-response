# Tuesday 9-06-2020
- 

# Monday 1-06-2020
- Time to convergence: needs to reach that threshold and remain above that (allow difference of 5%)
- Don't group all non-symmetric cases together because some are more difficult than others
- Non-symmetric baseline only show correct bar for time to convergence
- Additional experiments: reaction percentage with different random walk
- Group charts more so they are more easily comparable
- Remove chart titles
- Add related work chapter

# Tuesday 26-05-2020
- Use timesteps in thesis, not seconds. Mention the amount of timesteps per second.
- First the most critical fire is selected. Second the furthest exit is used from the selected fire. Both phases can be combined implicitely.
- For a single fire source, criticality isn't taken into account, since we know as a designer that we only have a single fire.
- Whatever you study in the analysis for sensor robots, do this for gripper robots as well.
- Analysis focus: accuracy (exit probability), speed of decision (how long it takes the robots to decide on an exit).
- Plots: exit probabilities, correct response to decision, how long it takes the grippers to react.
- Use a grouped bar plot for single fire and multiple fire.

# Tuesday 19-05-2020
- The individual mode should be tested with 30 seeds as well
- Try at least 3 values for each reaction strategy parameter (see which values are the most interesting)
- Try at least 3 population ratios, while keeping the total population size the same (see which values are the most interesting)
- When there's still some time left, try to change the random walk parameter
- When there's still some time left, try to change the random walk parameter, try to change the total population to 400
- The two distances from different sources to the same exit combined have a smaller difference than the two distances from different sources to the other exit combined
- Set of points A = fires, set of points B = exits. Determine which point in B is furthest/closest from the combination of points in A

# Tuesday 12-05-2020
- The new decision strategy is more dependent on sensor noise
- Don't use a quality comparison after the voting model
- When testing, use fixed fire positions from easy to difficult for the swarm to solve
- The random_turn_ticks param has less priority then the others

# Tuesday 5-05-2020
- Add a new movement mode: turn in a random direction every x timesteps to break up the grouping and mix the system better
- Determine the exit probability: how many times you exit with correct solution
- Test with 6 tiles per meter to position a fire exactly on the divider line
- Test with changing values of the gripper parameters
- Test with a runtime of 10 minutes
- Test with more than 1 fire source

# Tuesday 28-04-2020
- Add random voting model that just takes the opinion of a random neighbor
- Read additional article for the weighted voter model
- Use two parameters for the gripper reaction mechanism: percentage and timesteps
- The gripper starts acting when a percentage x holds for y amount of time

# Tuesday 21-04-2020
- No meeting

# Tuesday 14-04-2020
- No meeting

# Tuesday 7-04-2020
- Determine when to start the collective response so that it is most efficient
- Majority rule: the grippers use the data received from their sensing neighbors
- When working with data from neighbors, use a quorum to determine what to do
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