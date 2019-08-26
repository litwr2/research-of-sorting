FN=0001
rm -f $FN
for i in [7891]*;do awk -f 00.awk $i >>$FN;done
