cd results-all
./00.sh
cd ..
awk -f 04-json-generator-all.awk results-all/0001 >article/data-all.js
