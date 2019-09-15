cd results-all
./00.sh
cd ..
awk -f 04-json-generator-all.awk results-all/0001 >../litwr2.github.io/ros/data-all.js
