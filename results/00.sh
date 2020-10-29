FN=0001
rm -f $FN
for i in 1e*;do awk -f 00.awk $i >>$FN;done
