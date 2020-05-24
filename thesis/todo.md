# Done
- Individual for baseline (always logarithmic, except for 0.0 which flattens out around 50%)
- Gripper reaction percentage largely ineffective due to most standoffs being fully for one color (might need more testing)
- Problem with trying to analyse the influence of the amount of gripper robots while keeping the amount of sensor robots the same, is that this different amount of gripper robots influences the result of the sensor robots as well due to the increase/decrease in collision avoidance.
=> One possible solution to this is to keep the amount of grippers the same, but disable the logging of the ones you don't want to test. However this has its own problem since the choice of which grippers to enable can influence the result as well.
=> Similar for when the total population remains the same, but the ratio is changed.
=> Similar for the random walk parameter or the total amount of robots.
=> Conclusion: all 1620 tests have to be run again.

# Multiple fires
- Suggestion with minimal difference doesn't work: larger arena with the left fire much further left, then the two values won't be close together anymore.
- Found a better and much much simpler solution after some brainstorming.
- Remember what you mentioned: our brain applies some kind of heuristic to determine which fire should be prioritized.
- That heuristic is: which of the fire sources is CLOSEST to ANY of the exits?
==> Instead of basing the quality on the furthest distance to the exit, base it on the closest distance to the exit.
==> Instead of multiplying the temperature by the distance to get the quality, divide the temperature by the distance.
==> Old method:
	1) Red: 11.1m
	   Blue: 9.3m
	   Choose exit with distance furthest away from current position for quality comparison (Red)
	   Choose exit with distance furthest away from current position to update preferred exit (Red)
	2) Red: 6.2m
	   Blue: 8.6m
	   Choose exit with distance furthest away from current position for quality comparison (Blue)
	   Choose exit with distance furthest away from current position to update preferred exit (Blue)
	3) Fire 1 wins over fire 2, because it has higher multiplied quality
	   255° * 11.1m = 2830.5 > 255° * 8.6 = 2193
==> New method:
	1) Red: 11.1m
	   Blue: 9.3m
	   Choose exit with distance closest to current position for quality comparison (Blue)
	   Choose exit with distance furthest away from current position to update preferred exit (Red)
	2) Red: 6.2m
	   Blue: 8.6m
	   Choose exit with distance closest to current position for quality comparison (Red)
	   Choose exit with distance furthest away from current position to update preferred exit (Blue)
	3) Fire 2 wins over fire 1, because it has higher fractional quality
	   255° / 9.3m = 27.42 > 255° / 6.2 = 41.13
- Verified this method using 4 scenarios (see pictures): sources="2" position1="-7,-1.2" position2="0,1.2"
- Due to the change, results using the previous algorithm aren't perfectly up to date anymore, but the results are still valid for that old algorithm, which is described in the paper.
- New param multiple_fire_sources_support_version.
- Needs experiments to verify this algorithm (see logs).

# Experiments
- Try at least 3 values for each reaction strategy parameter (see which values are the most interesting)
- Try at least 3 population ratios, while keeping the total population size the same (see which values are the most interesting)
- When there's still some time left, try to change the random walk parameter
- When there's still some time left, try to change the total population to 400