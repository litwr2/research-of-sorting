BEGIN {
    ss["shell_a3n"] = 1
    ss["shell_10/3"] = 1
    ss["shell_prime_e"] = 1
    ss["shell_a102549"] = 1
    ss["shell_exp_tab"] = 1
    ss["shell_prime_10/3"] = 1
    ss["radix8"] = 2
    ss["radix11"] = 2
    ss["radix16"] = 2
    ss["shell_10/3_oms7"] = 1
    ss["radix8_oms7"] = 1
    ss["msd8_oms7"] = 1
    ss["heapsort_stl"] = 1
    ss["radix_bsd"] = 1
    ss["sradix_bsd"] = 1
    ss["clib_qsort"] = 1
    ss["heapsort_bsd"] = 1
    ss["mergesort_bsd"] = 1
    ss["qsort_hoare"] = 1
    #ss["qsort_hoare_tco"] = 0
    ss["qsort_no_pivot"] = 1
    ss["qsort_hoare2"] = 1
    ss["qsort_lomuto"] = 1
    ss["stlsort"] = 1
    ss["stlstable"] = 1
    ss["timsort"] = 1
    ss["spread"] = 1
    ss["pdq"] = 1
    ss["spin"] = 1
    ss["flat_stable"] = 1
    ss["bubble"] = 0
    ss["selection"] = 0
    ss["tree_stl"] = 1
    ss["tree_boost"] = 1
    ss["array*1"] = 0
    ss["array*2"] = 1
    ss["array*3"] = 1
    ss["array*5"] = 1
    ss["array*7"] = 1
    ss["hash"] = 1
    ss["hashbt_std"] = 1
    ss["hashbt"] = 1
    ss["hashbt_boost"] = 1

	t["PLAININT"] = 1
        t["INT1P4"] = 1
	t["INT64"] = 1
	t["INT128"] = 1
	t["FLOAT"] = 0
	t["STRINGS"] = 0
	t["CSTRINGS"] = 0
	t["STRINGS_SHORT"] = 0
	t["CSTRINGS_SHORT"] = 0
	t["STRINGS_LONG"] = 0
	t["CSTRINGS_LONG"] = 0

	ft["RANDOM"] = 1
	ft["ASCENDED"] = 0
	ft["DESCENDED"] = 0
	ft["ASCENDED_RANDOM"] = 0
        ft["DESCENDED_RANDOM"] = 0
	ft["LOW_VARIATION1"] = 0
	ft["LOW_VARIATION2"] = 0
	ft["LOW_VARIATION100"] = 0
	ft["SLOW_QSORT_HOARE"] = 0

	passes = 5
        SS = 100*1000

        excl = "("
        for (i in ss)
            if (ss[i] != 2) excl = excl "echo " i ";"
        excl = excl ")|grep -vFf - nsort.cpp >nsort2.cpp;"

	for (i = 0; i < 1; ++i) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
              if (t[i1])
                 for (i2 in ft)
                    if (ft[i2])
                       print excl "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DPASSES=" passes "\" make && nsort2 >results/" nSS "-" i1 "-" i2 "-z || echo ERROR!!!!!"
           SS *= 10
        }
        print "echo ok"
}

