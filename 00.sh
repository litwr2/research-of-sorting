cd results
./00.sh
cd ..
awk -f 04-json-generator.awk results/0001 >article/data.js
