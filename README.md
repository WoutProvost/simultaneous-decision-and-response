# simultaneous-decision-and-response
Simultaneous decision and response in a collective system using swarm robotics and collective decision making in a fire evacuation scenario.

## Dependencies:
```bash
sudo apt install cmake libfreeimage-dev libfreeimageplus-dev \
qt5-default freeglut3-dev libxi-dev libxmu-dev liblua5.3-dev \
lua5.3
```

## ARGoS installation:
Download the appropriate ARGoS package for your system [here](https://www.argos-sim.info/core.php) and follow the installation instructions. Afterwards continue with these steps. You can optionally execute the following 3 commands, to give the simulator GUI a proper desktop desktop icon:
```bash
sudo chmod o+w /usr/local/share/applications/argos3.desktop
echo "Icon=gnome-robots.png" >> /usr/local/share/applications/argos3.desktop
sudo chmod o-w /usr/local/share/applications/argos3.desktop
```

## Clone repository:
```bash
git clone https://github.com/WoutProvost/simultaneous-decision-and-response
cd simultaneous-decision-and-response
```

## Compilation:
```bash
mkdir frames logs build
cd build
cmake ..
make
```

## Plot application installation:
```bash
sudo cp src/plot/coldecplot /usr/local/bin
sudo cp ../src/plot/autocomplete.sh /etc/bash_completion.d/coldecplot
sudo cp ../src/plot/coldecplot.desktop /usr/local/share/applications
sudo cp ../src/plot/coldecplot.1 /usr/local/share/man/man1
sudo gzip -f /usr/local/share/man/man1/coldecplot.1
```

## Seed application installation:
```bash
sudo cp src/seed/coldecseed /usr/local/bin
sudo cp ../src/seed/autocomplete.sh /etc/bash_completion.d/coldecseed
sudo cp ../src/seed/coldecseed.1 /usr/local/share/man/man1
sudo gzip -f /usr/local/share/man/man1/coldecseed.1
```

## Execution:
```bash
argos3 -c ../experiments/fire_evacuation.argos
man coldecplot
man coldecseed
```

## Run experiments in bulk:
```bash
cd ../experiments
for f in *.argos; do coldecseed -n 30 "$f"; done
nohup parallel --delay 0.5 argos3 -c {1} ::: *.argos &
```

## Show results in bulk:
```bash
cd ../logs
for f in *.csv; do coldecplot "$f"; done
```

## Configuration:
Controller **appearance** params:
* `leds_color`: Defaults to `black`.
* `debug_show_preference`: Defaults to `false`.

Controller **movement** params:
* `max_velocity`: Defaults to `10.0`.
* `max_heading_angle_for_no_turn`: Defaults to `10.0`.
* `min_heading_angle_for_hard_turn`: Defaults to `90.0`.
* `random_turn_ticks`:
  * A value of `0` disables turning to a random direction after a configured amount of ticks.
  * Defaults to `100`.

Controller **collision_avoidance** params:
* `max_angle_between_heading_and_obstacle`: Defaults to `5.0`.
* `max_obstacle_proximity`: Defaults to `0.1`.

Temperature sensing controller **decision_strategy** params:
* `mode`:
  * Mode `plurality` uses the exit with the most votes as long as there is no ex aequo.
  * Mode `majority` uses the exit with more than 50% of the votes.
  * Mode `quality` uses the exit with the best average quality as long as there is no ex aequo.
  * Mode `random` uses the exit of a random neighbor.
  * Defaults to `none`.
* `check_for_fire_criticality`:
  * Doesn't support multiple fires when disabled.
  * Defaults to `true`.

Gate gripping controller **reaction_strategy** params:
* `min_agreement_percentage`: Defaults to `0.8`.
* `min_duration_ticks`: Defaults to `300`.

Loop functions **nest** params:
* `size`:
  * The value is a list of 2 widths, one for each dimension, separated by a comma.
  * Defaults to `15,15`.

Loop functions **heatmap** params:
* `tiles_per_meter`: Defaults to `6`.
* `max_temperature`:
  * Maximum of `255`, since the grayscale color range and UInt8 range is [0, 255].
  * Defaults to `255`.
* `debug_mode`:
  * Mode `gradient` is useful to show the whole temperature range in terms of steps.
  * Mode `resolution` is useful to show how large the tiles are compared to the robots.
  * Defaults to `none`.
* `debug_use_colors`:
  * The simulation only works with grayscale, so make sure to disable color after debugging.
  * Defaults to `false`.

Loop functions **fire** params:
* `sources`: Defaults to `1`.
* `positionX`:
  * The `X` can be a number from `1` to the amount of `sources`.
  * Each source can be controlled independently by its own attribute.
  * The value is a list of 2 nest coordinates separated by a comma.
  * If the value provided is outside the nest, the source falls back to a random position in the nest.
  * For a nest size of e.g. 15 meters along one axis, the valid range is `[-7.5:7.49]` and not `[-7.5:7.5]`.
  * Defaults to a random position in the nest.
* `circle_radius`: Defaults to `3.0`.

Loop functions **log** params:
* `file`: Defaults to `../logs/log.csv`.
* `disable`: Defaults to `false`.

User functions **divider** params:
* `enable_horizontal`: Defaults to `true`.
* `enable_vertical`: Defaults to `false`.

## Plot application uninstallation:
```bash
sudo rm -rf /usr/local/bin/coldecplot
sudo rm -rf /etc/bash_completion.d/coldecplot
sudo rm -rf /usr/local/share/applications/coldecplot.desktop
sudo rm -rf /usr/local/share/man/man1/coldecplot.1
```

## Seed application uninstallation:
```bash
sudo rm -rf /usr/local/bin/coldecseed
sudo rm -rf /etc/bash_completion.d/coldecseed
sudo rm -rf /usr/local/share/man/man1/coldecseed.1
```
