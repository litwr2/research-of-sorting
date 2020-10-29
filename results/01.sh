awk -f 01.awk 0001 | sqlite | awk '{if($3!=n){n=$3;print "\n" n;}print $1,$2}'
