- Time to convergence: needs to reach that threshold and keep above that (allow difference of 5%) + document change in latex text
- Don't group all non-symmetric cases together because some are more difficult than others. More than 3 bars for each category. Generate difficult and non-diffucult charts and see if it is much different. + document change in latex text

- Remove plot titles
- Group charts more so they are more easily comparable

- Related work chapter (articles):
Introduce work on collective decision making, value sensitive decision making (options with different qualities), there you can motivate novelty of thesis and how this thesis is different because the quality changes (more challenging because it is challenging on the microscopic model, but doesn't change quality on macroscopic model), discuss voting model literature (same quality/symmetric as well), analyse macroscopic behavior using microscopically coded behavior, check works on collective response, work by Yara (Google scholary). (3 pages or so)

- Mail multiple fires
- Mail cohesion threshold



# Experiments:
for f in *.argos; do coldecseed -n 30 "$f"; done && rm -rf !(*_*_*).argos && ls | wc -l
wget -O - -q https://www.wall2.ilabt.iminds.be/enable-nat.sh | sudo bash
/groups/wall2-ilabt-iminds-be/cosy-swarm/wout_exp/install/install.sh
cp -r /groups/wall2-ilabt-iminds-be/cosy-swarm/wout_exp/simultaneous-decision-and-response ~