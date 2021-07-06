BEGIN {
    ss["shell_a3n"] = 0
    ss["shell_10/3"] = 0
    ss["shell_prime_e"] = 0
    ss["shell_a102549"] = 0
    ss["shell_prime_2"] = 0
    ss["shell_prime_10/3"] = 0
    ss["shell_a102549m"] = 1
    ss["shell_2.25"] = 0
    ss["radix8"] = 0
    ss["radix11"] = 0
    ss["radix16"] = 0
    ss["radix8_msd"] = 0
    ss["radix11_msd"] = 0
    ss["radix16_msd"] = 0
    ss["radix_msd_sa"] = 0
    ss["radix_lsd_sa"] = 0
    ss["radix8_trie"] = 0
    ss["shell_10/3_oms7"] = 0
    ss["radix8_oms7"] = 0
    ss["radix8_msd_oms7"] = 0
    ss["heapsort_stl"] = 0
    ss["radix_bsd"] = 0
    ss["sradix_bsd"] = 0
    ss["clib_qsort"] = 0
    ss["heapsort_bsd"] = 0
    ss["heapsort_sa"] = 0
    ss["mergesort_bsd"] = 0
    ss["mergesort_sa"] = 0
    ss["mergesort_iter_sa"] = 0
    ss["mergesort_ip_sa"] = 0
    ss["mergesort_sip_sa"] = 0
    ss["catamergesort_sa"] = 0
    ss["catamergesort_stb_sa"] = 0
    ss["qsort_hoare"] = 0
    ss["qsort_hoare_tco"] = 0
    ss["qsort_no_pivot"] = 0
    ss["qsort_hoare2"] = 0
    ss["qsort_ll_sa"] = 0
    ss["qsort_lr_sa"] = 0
    ss["qsort_3ll_sa"] = 0
    ss["qsort_3lr_sa"] = 0
    ss["qsort_2p_sa"] = 0
    ss["introsort_sa"] = 0
    ss["introsort2_sa"] = 0
    ss["introsort2_stb_sa"] = 0
    ss["septenaryquick_sa"] = 0
    ss["septenaryquick_stb_sa"] = 0
    ss["qsort_safe"] = 1
    ss["qsort_safe_nss"] = 1
    ss["qsort_lomuto"] = 0
    ss["qsort_dualpivot"] = 0
    ss["stlsort"] = 0
    ss["stlstable"] = 0
    ss["timsort"] = 0
    ss["spread"] = 0
    ss["pdq"] = 0
    ss["spin"] = 0
    ss["flat_stable"] = 0
    ss["bubble"] = 0
    ss["combo"] = 1
    ss["selection"] = 0
    ss["tree_stl"] = 0
    ss["tree_boost"] = 0
    ss["array*1"] = 0
    ss["array*2"] = 0
    ss["array*3"] = 0
    ss["array*5"] = 0
    ss["array*7"] = 0
    ss["hash"] = 0
    ss["hashbt_std"] = 0
    ss["hashbt"] = 0
    ss["hashbt_boost"] = 0
    ss["insertion"] = 0
    ss["gnome_sa"] = 0
    ss["oddeven_sa"] = 0
    ss["cocktailshaker_sa"] = 0
    ss["bininsertionsort_sa"] = 0
    ss["bogosort_sa"] = 0
    ss["bozosort_sa"] = 0
    ss["bitonic_sa"] = 0
    ss["bitonic_nw_sa"] = 0
    ss["batcher_nw_sa"] = 0
    ss["smooth_sa"] = 0
    ss["stooge_sa"] = 0
    ss["slowsort_sa"] = 0
    ss["cyclesort_sa"] = 0  #doesn't work
    ss["splay_sa"] = 0
    ss["splayshake_sa"] = 0
    ss["splaymerge_sa"] = 0

    t["INT32"] = 1
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
    ft["ORDERED"] = 1
    ft["REVERSED"] = 1
    ft["PARTIALLY_ORDERED"] = 1
    ft["PARTIALLY_REVERSED"] = 1
    ft["LOW_VARIATION1"] = 1
    ft["LOW_VARIATION2"] = 1
    ft["LOW_VARIATION100"] = 1
    ft["SLOW_QSORT_HOARE"] = 1
    ft["SLOW_QSORT_HOARE_L"] = 1

    for (SS = 1*1*1000; SS <= 1*1*1000; SS *= 10) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
               for (i2 in ft) {
                   excl = ""
                   delete zoo
                   for (i3 in ss) {
                       if (ss[i3] == 0 || t[i1] == 0 || ft[i2] == 0) zoo[i3] = 1
                       if (SS > 20 && (index(i3, "bogo") || index(i3, "bozo")))
                           zoo[i3] = 1
                       if (SS > 1000 && (index(i3, "slowsort")))
                           zoo[i3] = 1
                       if (SS > 10000 && (index(i3, "stooge") || index(i3, "cycle") || index(i3, "oddeven")))
                           zoo[i3] = 1
                       lim = 100*1000
                       if (i3 == "radix8" && SS >= lim && index(i1, "_LONG") && i2 == "RANDOM")
                           zoo[i3] = 1

                       lim = 1000*1000
                       if ((i3 == "bubble" || index(i3, "cocktailshaker") || index(i3, "gnome")) && SS >= lim && i2 != "ORDERED" && (i2 != "PARTIALLY_ORDERED" || index(i1, "STRINGS")) && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "selection" || i3 == "insertion") && SS >= lim)
                           zoo[i3] = 1
                       if (i3 == "array*1" && SS >= lim && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && (i2 == "LOW_VARIATION2" || (index(i2, "PARTIALLY") || index(i2,  "REVERSED") || i2 == "LOW_VARIATION100") && index(i1, "STRING")))
                           zoo[i3] = 1
                       if (i3 == "hashbt" && SS >= lim && index(i2, "PARTIALLY"))
                           zoo[i3] = 1
                       if (index(i3, "hoare") && SS >= lim*10 && index(i2, "SLOW_QSORT_HOARE"))
                           zoo[i3] = 1
                       if (i3 == "qsort_no_pivot" && SS >= lim && (i2 == "ORDERED" || i2 == "REVERSED" || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || index(i2, "SLOW_QSORT_HOARE") && index(i1, "STRING")))
                           zoo[i3] = 1
                       if (i3 == "qsort_lomuto" && SS >= lim && (index(i2, "PARTIALLY") || i2 == "LOW_VARIATION1" || i2 == "LOW_VARIATION2" || index(i2, "SLOW_QSORT_HOARE") && index(i1, "STRING")))
                           zoo[i3] = 1
                       if (i3 == "hash" && SS >= lim && index(i1, "STRING") && (i2 == "PARTIALLY_ORDERED" || i2 == "LOW_VARIATION100" || i2 == "LOW_VARIATION2"))
                           zoo[i3] = 1
                       if (i3 == "radix8_msd" && SS >= lim && index(i1, "_LONG") && i2 == "RANDOM")
                           zoo[i3] = 1

                       lim = 10*1000*1000
                       if (i3 == "bubble" && SS >= lim && i2 != "ORDERED" && i2 != "LOW_VARIATION1")
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && (index(i1, "STRING") && i2 != "LOW_VARIATION1" && !(index(i1, "SHORT") && i2 == "RANDOM") && !(!index(i1, "LONG") && i2 == "RANDOM") || index(i2, "PARTIALLY")))
                           zoo[i3] = 1
                       if (i3 == "hash" && SS >= lim && (index(i1, "STRING") && i2 != "LOW_VARIATION1" && !(index(i1, "SHORT") && i2 == "RANDOM") && !((i1 == "STRINGS" || i1 == "CSTRINGS") && i2 == "RANDOM") || i2 == "LOW_VARIATION2" || i2 == "LOW_VARIATION100"))
                           zoo[i3] = 1
                       if ((i3 == "qsort_no_pivot" || i3 == "qsort_lomuto") && SS >= lim && (i2 == "LOW_VARIATION100" && index(i1, "STRING") || index(i2, "SLOW_QSORT_HOARE")))
                           zoo[i3] = 1
                       if (SS >= lim && index(i1, "LONG"))
                           zoo[i3] = 1  # 8 GB RAM is not enough?

                       lim = 100*1000*1000
                       if (SS >= lim && i1 == "STRINGS")
                           zoo[i3] = 1  # 8 GB RAM is not enough?
                       if ((i3 == "qsort_no_pivot" || i3 == "qsort_lomuto") && SS >= lim && (i2 == "LOW_VARIATION100" || index(i1, "STRING")))
                           zoo[i3] = 1
                       if ((i3 == "array*2" || i3 == "array*3" || i3 == "array*5" || i3 == "array*7") && SS >= lim && i2 == "LOW_VARIATION100")
                           zoo[i3] = 1
                       if (SS >= lim && index(i3, "hashbt"))
                           zoo[i3] = 1  # 8 GB RAM is not enough
                       if (SS >= lim && index(i1, "STRING") && !index(i1, "SHORT"))
                           zoo[i3] = 1  # 8 GB RAM is not enough?
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
                   print excl "touch always.cpp;EXTRA=\"-D" i1 " -D" i2 " -DSS=" SS " -DPASSES=" passes "\" FNP=nsort2 make && nsort2 >>results/" nSS "-" i1 "-" i2 " || echo $? ERROR!!!!!"
               }
        }
        print "echo ok"
}

