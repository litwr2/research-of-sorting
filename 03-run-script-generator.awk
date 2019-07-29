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
    ss["radix8_msb"] = 1
    ss["radix11_msb"] = 1
    ss["radix16_msb"] = 1
    ss["shell_10/3_oms7"] = 1
    ss["radix8_oms7"] = 1
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

	ft["RANDOM"] = 1
	ft["ASCENDED"] = 1
	ft["DESCENDED"] = 1
	ft["ASCENDED_RANDOM"] = 1
    ft["DESCENDED_RANDOM"] = 1
	ft["LOW_VARIATION1"] = 1
	ft["LOW_VARIATION2"] = 1
	ft["LOW_VARIATION100"] = 1
	ft["SLOW_QSORT_HOARE"] = 1

	for (SS = 100*1000*1000; SS <= 100*1000*1000; SS *= 10) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
               for (i2 in ft) {
                   excl = ""
                   delete zoo
                   for (i3 in ss) {
                       if (ss[i3] == 0 || t[i1] == 0 || ft[i2] == 0) zoo[i3] = 1
                       lim = 100*1000
                       if (i3 == "radix8" && SS >= lim && index(i1, "_LONG") && i2 == "RANDOM")
                           zoo[i3] = 1

                       lim = 1000*1000
                       if (i3 == "bubble" && SS >= lim && i2 != "ASCENDED" && (i2 != "ASCENDED_RANDOM" || index(i1, "STRINGS")) && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "selection" || i3 == "insertion") && SS >= lim)
                           zoo[i3] = 1
                       if (i3 == "array*1" && SS >= lim && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && (i2 == "LOW_VARIATION2" || (index(i2, "SCENDED_RANDOM") || index(i2,  "DESCENDED") || i2 == "LOW_VARIATION100") && index(i1, "STRINGS")))
                           zoo[i3] = 1
                       if (i3 == "hashbt" && SS >= lim && (index(i2, "SCENDED_RANDOM")))
                           zoo[i3] = 1
                       if ((i3 == "qsort_hoare" || i3 == "qsort_hoare2") && SS >= lim && i2 == "SLOW_QSORT_HOARE")
                           zoo[i3] = 1
                       if (i3 == "qsort_no_pivot" && SS >= lim && (i2 == "ASCENDED" || i2 == "DESCENDED" || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || i2 == "SLOW_QSORT_HOARE" && index(i1, "STRINGS")))
                           zoo[i3] = 1
                       if (i3 == "qsort_lomuto" && SS >= lim && (index(i2, "SCENDED") || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || i2 == "SLOW_QSORT_HOARE" && index(i1, "STRINGS")))
                           zoo[i3] = 1
                       if (i3 == "hash" && SS >= lim && index(i1, "STRINGS") && (i2 == "ASCENDED_RANDOM" || i2 == "LOW_VARIATION100" || i2 == "LOW_VARIATION2"))
                           zoo[i3] = 1
                       if (i3 == "radix8_msb" && SS >= lim && index(i1, "_LONG") && i2 == "RANDOM")
                           zoo[i3] = 1

                       lim = 10*1000*1000
                       if (i3 == "bubble" && SS >= lim && i2 != "ASCENDED" && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && (index(i1, "STRING")  && i2 != "LOW_VARIATION1" && !(index(i1, "SHORT") && i2 == "RANDOM") && !((i1 == "STRINGS" || i1 == "CSTRINGS") && i2 == "RANDOM") || index(i2, "SCENDED_RANDOM")))
                           zoo[i3] = 1
                       if (i3 == "hash" && SS >= lim && (index(i1, "STRING") && i2 != "LOW_VARIATION1" && !(index(i1, "SHORT") && i2 == "RANDOM") && !((i1 == "STRINGS" || i1 == "CSTRINGS") && i2 == "RANDOM") || i2 == "LOW_VARIATION2" || i2 == "LOW_VARIATION100"))
                           zoo[i3] = 1
                       if ((i3 == "qsort_no_pivot" || i3 == "qsort_lomuto") && SS >= lim && (i2 == "LOW_VARIATION100" && index(i1, "STRINGS") || i2 == "SLOW_QSORT_HOARE"))
                           zoo[i3] = 1
                       if (SS >= lim && index(i1, "LONG"))
                           zoo[i3] = 1  # 8 MB RAM is not enough

                       lim = 100*1000*1000
                       if (SS >= lim && i1 == "STRINGS")
                           zoo[i3] = 1  # 8 MB RAM is not enough
                       if ((i3 == "qsort_no_pivot" || i3 == "qsort_lomuto") && SS >= lim && i2 == "LOW_VARIATION100")
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && i2 == "LOW_VARIATION100")
                           zoo[i3] = 1
                       if (SS >= lim && index(i3, "hashbt"))
                           zoo[i3] = 1  # 8 MB RAM is not enough
                       if (SS >= lim && index(i1, "STRING") && !index(i1, "SHORT"))
                           zoo[i3] = 1  # 8 MB RAM is not enough
                   }
                   if (length(zoo) == length(ss)) continue
                   printf "\n# %s %s %s ", nSS, i1, i2; for(x in ss) dbg_ssc[x] = 1;for(x in zoo)delete dbg_ssc[x];delete dbg_sss;n=1;for(x in dbg_ssc)dbg_sss[n++]=x;asort(dbg_sss);for(x = 1; x < n; ++x) printf "%s ", dbg_sss[x]; printf "\n"
                   for (x in zoo)
                       excl = excl "echo '\"" x "\"';"
                   if (excl != "")
                       excl = "(" excl ")|grep -vFf -"
                   else
                       excl = "cat"
                   excl = excl " nsort.cpp >nsort2.cpp;"
                   passes = 1
                   if (SS <= 1000) passes = 10
                   else if (SS <= 10000) passes = 4
                   else if (SS <= 100000) passes = 2
                   print excl "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DPASSES=" passes "\" FNP=nsort2 make && nsort2 >>results/" nSS "-" i1 "-" i2 " || echo ERROR!!!!!"
               }
        }
        print "echo ok"
}

