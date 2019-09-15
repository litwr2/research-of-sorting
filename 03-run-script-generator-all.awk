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
    ss["radix8_trie"] = 0
    ss["shell_10/3_oms7"] = 0
    ss["radix8_oms7"] = 0
    ss["radix8_msd_oms7"] = 0
    ss["heapsort_stl"] = 0
    ss["radix_bsd"] = 0
    ss["sradix_bsd"] = 0
    ss["clib_qsort"] = 0
    ss["heapsort_bsd"] = 0
    ss["mergesort_bsd"] = 0
    ss["qsort_hoare"] = 0
    ss["qsort_hoare_tco"] = 0
    ss["qsort_hoare2"] = 0
    ss["qsort_no_pivot"] = 0
    ss["qsort_lomuto"] = 0
    ss["qsort_dualpivot"] = 1
    ss["stlsort"] = 0
    ss["stlstable"] = 0
    ss["timsort"] = 0
    ss["spread"] = 0
    ss["pdq"] = 0
    ss["spin"] = 0
    ss["flat_stable"] = 0
    ss["bubble"] = 0
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

    t["INT32"] = 0
    t["INT1P4"] = 0
    t["INT64"] = 0
    t["INT128"] = 0
    t["FLOAT"] = 0
    t["STRINGS"] = 0
    t["CSTRINGS"] = 0
    t["STRINGS_SHORT"] = 1
    t["CSTRINGS_SHORT"] = 1
    t["STRINGS_LONG"] = 0
    t["CSTRINGS_LONG"] = 0

    for (SS = 8; SS <= 12; ++SS)  # 7 .. 12
       for (i1 in t) {
           excl = ""
           delete zoo
           for (i3 in ss) {
               if (ss[i3] == 0 || t[i1] == 0) zoo[i3] = 1
               #if (SS > 7 && i3 == "radix16") zoo[i3] = 1
               #if (SS > 8 && i3 == "radix11") zoo[i3] = 1
               #if (SS > 8 && i3 == "flat_stable") zoo[i3] = 1
               #if (SS > 9 && i3 == "radix8") zoo[i3] = 1
               #if (SS > 9 && i3 == "radix8_oms7") zoo[i3] = 1
           }
           for (x in zoo)
               excl = excl "echo '\"" x "\"';"
           if (length(zoo) == length(ss)) continue
           if (excl != "")
               excl = "(" excl ")|grep -vwFf -"
           else
               excl = "cat"
           excl = excl " nsort-all.cpp >nsort-all2.cpp;"
           passes = 1
           #if (SS <= 9) passes = 3
           #else if (SS <= 10) passes = 2
           #else if (SS <= 11) passes = 2
           #else if (SS <= 12) passes = 2
           repeats = 2
           print excl "touch always.cpp;EXTRA=\"-DREPEATS=" repeats " -D" i1 " -DSS=" SS " -DPASSES=" passes "\" FNP=nsort-all2 make && nsort-all2 >>results-all/" SS "-" i1 " || echo $? ERROR!!!!!"
           }
        print "echo ok"
}

