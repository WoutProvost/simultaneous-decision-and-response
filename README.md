# swarm-robotics-thesis
Master's thesis on swarm robotics and collective decision making.

Read-only link to the LaTeX project: https://www.overleaf.com/read/sncpkxbhbqts

## ARGoS installation:
```bash
git clone https://github.ugent.be/wprovost/swarm-robotics-thesis
cd swarm-robotics-thesis
sudo dpkg -i download/argos3_simulator-*.deb
sudo apt --fix-broken install
sudo chmod o+w /usr/local/share/applications/argos3.desktop
echo "Icon=gnome-robots.png" >> /usr/local/share/applications/argos3.desktop
sudo chmod o-w /usr/local/share/applications/argos3.desktop
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

## Plot application installation
```bash
sudo cp src/plot/coldecplot /usr/local/bin
sudo cp ../src/plot/autocomplete.sh /etc/bash_completion.d/coldecplot
sudo cp ../src/plot/coldecplot.desktop /usr/local/share/applications
sudo cp ../src/plot/coldecplot.1 /usr/local/share/man/man1
sudo gzip -f /usr/local/share/man/man1/coldecplot.1
```

## Seed application installation
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

## Configuration:
Controller **general** params:
* `leds_color`:
  * The gate gripping footbot defaults to `black`.
  * The temperature sensing footbot defaults to `white`.

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
* `circle_radius`: Defaults to `3.0`.
* `is_dynamic`: Defaults to `false`.
* `dynamic_interval_ticks`: Defaults to `50`.
* `dynamic_temperature_increase`: Defaults to `5`.
* `dynamic_spread_direction`: Defaults to `0.0`.

Loop functions **log** params:
* `file`: Defaults to `../logs/log.csv`.
* `disable`: Defaults to `false`.

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