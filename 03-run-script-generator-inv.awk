BEGIN {
    ss["shell_a3n"] = 0
    ss["shell_10/3"] = 1
    ss["shell_prime_e"] = 0
    ss["shell_a102549"] = 0
    ss["shell_exp_tab"] = 0
    ss["shell_prime_10/3"] = 0
    ss["shell_a102549m"] = 0
    ss["shell_2.25"] = 0
    ss["radix8"] = 0
    ss["radix11"] = 0
    ss["radix16"] = 0
    ss["radix8_msb"] = 0
    ss["radix11_msb"] = 0
    ss["radix16_msb"] = 0
    ss["shell_10/3_oms7"] = 0
    ss["radix8_oms7"] = 0
    ss["radix8_msb_oms7"] = 0
    ss["heapsort_stl"] = 0
    ss["radix_bsd"] = 0
    ss["sradix_bsd"] = 0
    ss["clib_qsort"] = 0
    ss["heapsort_bsd"] = 0
    ss["mergesort_bsd"] = 0
    ss["qsort_hoare"] = 0
    ss["qsort_hoare_tco"] = 0
    ss["qsort_no_pivot"] = 0
    ss["qsort_hoare2"] = 0
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
    ss["selection"] = 0
    ss["tree_stl"] = 0
    ss["tree_boost"] = 0
    ss["array*1"] = 1
    ss["array*2"] = 0
    ss["array*3"] = 0
    ss["array*5"] = 0
    ss["array*7"] = 0
    ss["hash"] = 0
    ss["hashbt_std"] = 0
    ss["hashbt"] = 0
    ss["hashbt_boost"] = 0
    ss["insertion"] = 0
    #for (i in ss) ss[i] = 1

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
    ft["ORDERED"] = 1
    ft["REVERSED"] = 1
    ft["PARTIALLY_ORDERED"] = 1
    ft["PARTIALLY_REVERSED"] = 1
    ft["LOW_VARIATION1"] = 1
    ft["LOW_VARIATION2"] = 1
    ft["LOW_VARIATION100"] = 1
    ft["SLOW_QSORT_HOARE"] = 1

    for (SS = 1000*1000; SS <= 1000*1000; SS *= 10) {
           nSS = "1e" int(log(SS)/log(10) + .5)
           for (i1 in t)
               for (i2 in ft) {
                   excl = ""
                   delete zoo
                   for (i3 in ss) {
                       if (ss[i3] == 0 || t[i1] == 0 || ft[i2] == 0) zoo[i3] = 1
                   }
                   if (length(zoo) == length(ss)) continue
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
