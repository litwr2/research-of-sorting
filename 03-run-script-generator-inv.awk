BEGIN {
    ss["shell_a3n"] = 0
    ss["shell_10/3"] = 0
    ss["shell_prime_e"] = 0
    ss["shell_a102549"] = 0
    ss["shell_prime_2"] = 0
    ss["shell_prime_10/3"] = 0
    ss["shell_a102549m"] = 0
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
    ss["qsort_safe"] = 0
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
    ss["combo"] = 0
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
    ss["cyclesort_sa"] = 0
    ss["splay_sa"] = 0
    ss["splayshake_sa"] = 0
    ss["splaymerge_sa"] = 0
    #for (i in ss) ss[i] = 1

    t["INT32"] = 0
    t["INT1P4"] = 0
    t["INT64"] = 0
    t["INT128"] = 0
    t["FLOAT"] = 0
    t["STRINGS"] = 0
    t["CSTRINGS"] = 0
    t["STRINGS_SHORT"] = 0
    t["CSTRINGS_SHORT"] = 1
    t["STRINGS_LONG"] = 0
    t["CSTRINGS_LONG"] = 0

    ft["RANDOM"] = 1
    ft["ORDERED"] = 0
    ft["REVERSED"] = 0
    ft["PARTIALLY_ORDERED"] = 0
    ft["PARTIALLY_REVERSED"] = 0
    ft["LOW_VARIATION1"] = 0
    ft["LOW_VARIATION2"] = 0
    ft["LOW_VARIATION100"] = 0
    ft["SLOW_QSORT_HOARE"] = 0

    for (SS = 100*1000*1000; SS <= 100*1000*1000; SS *= 10) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
               for (i2 in ft) {
                   excl = ""
                   delete zoo
                   for (i3 in ss) {
                       if (ss[i3] == 0 || t[i1] == 0 || ft[i2] == 0) zoo[i3] = 1
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
