# Done
- Individual for baseline (always logarithmic, except for 0.0 which flattens out around 50%)
- Gripper reaction percentage largely ineffective due to most standoffs being fully for one color
- Problem with trying to analyse the influence of the amount of gripper robots while keeping the amount of sensor robots the same, is that this different amount of gripper robots influences the result of the sensor robots as well due to the increase/decrease in collision avoidance.
=> One possible solution to this is to keep the amount of grippers the same, but disable the logging of the ones you don't want to test. However this has its own problem since the choice of which grippers to enable can influence the result as well.
=> Similar for when the total population remains the same, but the ratio is changed.
=> Similar for the random walk parameter or the total amount of robots.
=> Conclusion: all 1620 tests have to be run again.

# Experiments
- Try at least 3 values for each reaction strategy parameter (see which values are the most interesting)
- Try at least 3 population ratios, while keeping the total population size the same (see which values are the most interesting)
- When there's still some time left, try to change the random walk parameter
- When there's still some time left, try to change the random walk parameter, try to change the total population to 400

# Multiple sources
- position1="-7,-1.2" position2="0,1.2"
- The two distances from different sources to the same exit combined have a smaller difference than the two distances from different sources to the other exit combined
- Set of points A = fires, set of points B = exits. Determine which point in B is furthest/closest from the combination of points in A