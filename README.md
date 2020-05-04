# simultaneous-decision-and-response
Simultaneous decision and response in a collective system using swarm robotics and collective decision making in a fire evacuation scenario.

## ARGoS installation:
Download the appropriate ARGoS package for your system [here](https://www.argos-sim.info/core.php) and follow the installation instructions. Afterwards continue with these steps.
```bash
sudo apt --fix-broken install
sudo chmod o+w /usr/local/share/applications/argos3.desktop
echo "Icon=gnome-robots.png" >> /usr/local/share/applications/argos3.desktop
sudo chmod o-w /usr/local/share/applications/argos3.desktop
```

## Clone repository:
```bash
git clone https://github.ugent.be/wprovost/simultaneous-decision-and-response
cd simultaneous-decision-and-response
```

## Compilation:
```bash
mkdir frames
mkdir logs
mkdir build
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
coldecseed -n 30 fire_evacuation.argos
parallel --delay 0.5 argos3 -c fire_evacuation{1}.argos ::: `seq 1 30`
```

## Show results in bulk:
```bash
cd ../logs
ls fire_evacuation*.csv | while read -r file; do coldecplot "$file"; done
```

## Configuration:
Controller **appearance** params:
* `leds_color`: Defaults to `black`.
* `debug_show_preference`: Defaults to `false`.

Controller **movement** params:
* `max_velocity`: Defaults to `10.0`.
* `max_heading_angle_for_no_turn`: Defaults to `10.0`.
* `min_heading_angle_for_hard_turn`: Defaults to `90.0`.

Controller **collision avoidance** params:
* `max_angle_between_heading_and_obstacle`: Defaults to `5.0`.
* `max_obstacle_proximity`: Defaults to `0.1`.

Temperature sensing controller **decision strategy** params:
* `mode`:
  * Mode `plurality` uses the exit with the most votes as long as there is no ex aequo.
  * Mode `majority` uses the exit with more than 50% of the votes.
  * Mode `random` uses the exit of a random neighbour.
  * Defaults to `none`.

Gate gripping controller **reaction strategy** params:
* `min_agreement_percentage`: Defaults to `0.8`.
* `min_duration_ticks`: Defaults to `300`.

Loop functions **heatmap** params:
* `tiles_per_meter`: Defaults to `10`.
* `max_temperature`:
  * Maximum of `255`, since the grayscale color range is [0, 255];
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
  * The value is a list of 2 arena coordinates separated by a comma.
  * If the value provided is outside the arena, the source falls back to a random position in the arena.
  * For an arena size of e.g. 15 meters along one axis, the valid range is `[-7.5:7.49]` and not `[-7.5:7.5]`.
  * Defaults to a random position in the arena.
* `circle_radius`: Defaults to `3.0`.
* `is_dynamic`: Defaults to `false`.
* `dynamic_interval_ticks`: Defaults to `50`.
* `dynamic_temperature_increase`: Defaults to `5`.
* `dynamic_spread_direction`: Defaults to `0.0`.

Loop functions **log** params:
* `file`: Defaults to `../logs/log.csv`.
* `disable`: Defaults to `false`.

User functions **divider** params:
* `enable`: Defaults to `true`.

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