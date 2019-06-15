BEGIN {
    ss["shell_a3n"] = 1
    ss["shell_10/3"] = 1
    ss["shell_prime_e"] = 1
    ss["shell_a102549"] = 1
    ss["shell_exp_tab"] = 1
    ss["shell_prime_10/3"] = 1
    ss["radix8"] = 1
    ss["radix11"] = 1
    ss["radix16"] = 1
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
    ss["qsort_hoare_tco"] = 0
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
	t["FLOAT"] = 1
	t["STRINGS"] = 0
	t["CSTRINGS"] = 0

	ft["RANDOM_ORDER"] = 1
	ft["ASCENDED_ORDER"] = 0
	ft["ASCENDED_RANDOM_ORDER"] = 0
	ft["DESCENDED_ORDER"] = 0
	ft["LOW_VARIATION_ORDER"] = 0
	ft["SLOW_QSORT1_ORDER"] = 0

	passes = 2
        LOW_VARIATION_CONST = 100
        SS = 1000*1000*100

        excl = "("
        for (i in ss)
            if (!ss[i]) excl = excl "echo " i ";"
        excl = excl ")|grep -vFf - nsort.cpp >nsort2.cpp;"

	for (i = 0; i < 1; ++i) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
              if (t[i1])
                 for (i2 in ft)
                    if (ft[i2])
                       print excl "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DLOW_VARIATION_CONST=" LOW_VARIATION_CONST " -DPASSES=" passes "\" make && nsort2 >>results/" nSS "-" i1 "-" i2 "-z || echo ERROR!!!!!"
           SS *= 10
        }
        print "echo ok"
}

