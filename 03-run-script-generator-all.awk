BEGIN {
    ss["shell_a3n"] = 1
    ss["shell_10/3"] = 1
    ss["shell_prime_e"] = 1
    ss["shell_a102549"] = 1
    ss["shell_exp_tab"] = 1
    ss["shell_prime_10/3"] = 1
    ss["shell_a102549m"] = 1
    ss["shell_2.25"] = 1
    ss["radix8"] = 0
    ss["radix11"] = 0
    ss["radix16"] = 0
    ss["radix8_msb"] = 1
    ss["radix11_msb"] = 1
    ss["radix16_msb"] = 1
    ss["shell_10/3_oms7"] = 1
    ss["radix8_oms7"] = 0
    ss["radix8_msb_oms7"] = 1
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
    ss["qsort_dualpivot"] = 1
    ss["stlsort"] = 1
    ss["stlstable"] = 1
    ss["timsort"] = 1
    ss["spread"] = 1
    ss["pdq"] = 1
    ss["spin"] = 1
    ss["flat_stable"] = 0
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
    ss["insertion"] = 1

	t["PLAININT"] = 1
    t["INT1P4"] = 1
	t["INT64"] = 1
	t["INT128"] = 1
	t["FLOAT"] = 1
	t["STRINGS"] = 1
	t["CSTRINGS"] = 1
	t["STRINGS_SHORT"] = 1
	t["CSTRINGS_SHORT"] = 1
	t["STRINGS_LONG"] = 1
	t["CSTRINGS_LONG"] = 1

	for (SS = 7; SS <= 12; ++SS)
       for (i1 in t) {
           excl = ""
           delete zoo
           for (i3 in ss) {
               if (ss[i3] == 0 || t[i1] == 0) zoo[i3] = 1
           }
           for (x in zoo)
               excl = excl "echo " x ";"
           if (length(zoo) == length(ss)) continue
           if (excl != "")
               excl = "(" excl ")|grep -vwFf -"
           else
               excl = "cat"
           excl = excl " nsort-all.cpp >nsort-all2.cpp;"
           passes = 1
           if (SS <= 9) passes = 10
           else if (SS <= 10) passes = 5
           else if (SS <= 11) passes = 3
           else if (SS <= 12) passes = 2
           print excl "touch always.cpp;EXTRA=\"-D" i1 " -DSS=" SS " -DPASSES=" passes " FNP=nsort2-all make && nsort-all2 >>results/" SS "-" i1 " || echo ERROR!!!!!"
           }
        print "echo ok"
}
