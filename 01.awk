BEGIN {
	passes = 2
	t["PLAININT"] = 0
        t["INT1P4"] = 1
	t["INT64"] = 0
	t["INT128"] = 0
	t["FLOAT"] = 0
	t["STRINGS"] = 0
	t["CSTRINGS"] = 0
	#COUNTERS
        #ALL_VARIANTS  //SS must be less than 14 (14 means a many hours calculation)
	ft["RANDOM_ORDER"] = 1
	ft["ASCENDED_ORDER"] = 0
	ft["ASCENDED_RANDOM_ORDER"] = 0
	ft["DESCENDED_ORDER"] = 0
	ft["LOW_VARIATION_ORDER"] = 0
	LOW_VARIATION_CONST = 100
	ft["SLOW_QSORT1_ORDER"] = 0
        SS = 100000000
	for (i = 0; i < 1; ++i) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
              #if (t[i1])
                 for (i2 in ft)
                    if (ft[i2]) 
                       print "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DPASSES=" passes "\" make && nsort >results/" nSS "-" i1 "-" i2 " || echo ERROR!!!!!"
           SS *= 10
        }
        print "echo ok" 
}

