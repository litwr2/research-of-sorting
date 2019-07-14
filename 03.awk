BEGIN {
    ss["shell_a3n"] = 1
    ss["shell_10/3"] = 1
    ss["shell_prime_e"] = 1
    ss["shell_a102549"] = 1
    ss["shell_exp_tab"] = 1
    ss["shell_prime_10/3"] = 1
    ss["shell_a102549m"] = 1
    ss["shell_2.25"] = 1
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
    ss["bubble"] = 1
    ss["selection"] = 1
    ss["tree_stl"] = 1
    ss["tree_boost"] = 1
    ss["array*1"] = 1
    ss["array*2"] = 1
    ss["array*3"] = 1
    ss["array*5"] = 1
    ss["array*7"] = 1
    ss["hash"] = 1
    ss["hashbt_std"] = 1
    ss["hashbt"] = 1
    ss["hashbt_boost"] = 1
    ss["qsort_dualpivot"] = 1

	t["PLAININT"] = 0
    t["INT1P4"] = 0
	t["INT64"] = 0
	t["INT128"] = 0
	t["FLOAT"] = 0
	t["STRINGS"] = 1
	t["CSTRINGS"] = 1
	t["STRINGS_SHORT"] = 1
	t["CSTRINGS_SHORT"] = 1
	t["STRINGS_LONG"] = 1
	t["CSTRINGS_LONG"] = 1

	ft["RANDOM"] = 1
	ft["ASCENDED"] = 0
	ft["DESCENDED"] = 0
	ft["ASCENDED_RANDOM"] = 0
    ft["DESCENDED_RANDOM"] = 0
	ft["LOW_VARIATION1"] = 0
	ft["LOW_VARIATION2"] = 0
	ft["LOW_VARIATION100"] = 0
	ft["SLOW_QSORT_HOARE"] = 0

	for (SS = 1000; SS <= 100*1000; SS *= 10) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
               for (i2 in ft) {
                   excl = ""
                   for (i3 in ss) {
                       lim = 1000*1000
                       if (i3 == "bubble" && SS >= lim && i2 != "ASCENDED" && i2 != "ASCENDED_RANDOM" && i2 != "LOW_VARIATION1")
                           excl = excl "echo " i3 ";"
                       if (i3 == "selection" && SS >= lim)
                           excl = excl "echo " i3 ";"
                       if (i3 == "array*1" && SS >= lim)
                           excl = excl "echo '" i3 "';"
                       if (i3 == "array*2" && SS >= lim && (i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || index(i2, "SCENDED_RANDOM") || i2 == "LOW_VARIATION100" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "array*3" && SS >= lim && (i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2"|| index(i2, "SCENDED_RANDOM") || i2 == "LOW_VARIATION100" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "array*5" && SS >= lim && (i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2"|| index(i2,  "SCENDED_RANDOM") || i2 == "LOW_VARIATION100" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "array*7" && SS >= lim && (i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2"|| index(i2,  "SCENDED_RANDOM") || i2 == "LOW_VARIATION100" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "hashbt" && SS >= lim && (i2 == "LOW_VARIATION1" || index(i2, "SCENDED_RANDOM")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "qsort_hoare" && SS >= lim && i2 == "SLOW_QSORT_HOARE")
                           excl = excl "echo '" i3 "';"
                       if (i3 == "qsort_hoare2" && SS >= lim && i2 == "SLOW_QSORT_HOARE")
                           excl = excl "echo '" i3 "';"
                       if (i3 == "qsort_no_pivot" && SS >= lim && (i2 == "ASCENDED" || i2 == "DESCENDED" || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || i2 == "SLOW_QSORT_HOARE" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "qsort_lomuto" && SS >= lim && (index(i2, "SCENDED") || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || i2 == "SLOW_QSORT_HOARE" && index(i1, "STRINGS")))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "shell_a3n" && SS >= lim && index(i1, "STRINGS") && (i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2"))
                           excl = excl "echo '" i3 "';"
                       if (i3 == "hash" && SS >= lim && index(i1, "STRINGS") && (i2 == "LOW_VARIATION100" || i2 == "LOW_VARIATION2"))
                           excl = excl "echo '" i3 "';"
                   }
                   if (excl != "")
                       excl = "(" excl ")|grep -vFf -"
                   else
                       excl = "cat"
                   excl = excl " nsort.cpp >nsort2.cpp;"
                   passes = 1
                   if (SS <= 1000) passes = 10
                   else if (SS <= 10000) passes = 4
                   else if (SS <= 100000) passes = 2
                   print excl "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DPASSES=" passes "\" make && nsort2 >>results/" nSS "-" i1 "-" i2 " || echo ERROR!!!!!"
               }
        }
        print "echo ok"
}

