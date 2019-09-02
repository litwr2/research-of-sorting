BEGIN {
    mdata["shell"] = 0
    mdata["radix"] = "=TN"
    mdata["radix_msd"] = "=TN"
    mdata["radix_bsd"] = 0
    mdata["sradix_bsd"] = "=TN*"
    mdata["radix8_trie"] = "от =TN + 24L до =(T + 24L + 12)N"
    mdata["clib_qsort"] = "от =TN/2 до =TN*"
    mdata["heapsort"] = 0
    mdata["mergesort_bsd"] = "от =Tlog2N до TN*"
    mdata["quicksort"] = "от =16log2N до 16N"
    mdata["quicksort_tco"] = "от 0 до N"
    mdata["stlsort"] = "от 0 до до =Tlog2N*"
    mdata["stlstable"] = "от 0 до =TN/2*"
    mdata["timsort"] = "от 0 до =TN*"
    mdata["spread"] = "=0"
    mdata["pdq"] = "TlogN"
    mdata["spin"] = "TN/2"
    mdata["flat_stable"] = "=TN/256"
    mdata["bubble"] = 0
    mdata["selection"] = 0
    mdata["tree_stl"] = "(T + 32)N"
    mdata["tree_boost"] = "(T + 24)N"
    mdata["array*1"] = "(T + 1/8)N"
    mdata["array*k, k&gt;1"] = "(T + 4k)N"
    mdata["hash"] = "(T + 8 + 4A)N"
    mdata["hashbt_std"] = "(80 + T + 4A + M)N"
    mdata["hashbt"] = "(T + 12)N"
    mdata["hashbt_boost"] = "(56 + T + 4A + M)N"
    mdata["insertion"] = 0
    n = asorti(mdata, mdata_sorted)
    #text = "<style type=text/css>table,th,td{border-width:thin;border-style:solid;border-color:green;border-spacing:0px;}</style><table><tr><th>Метод<th>Зависимость"
    text = "<div align=center>\n<table>\n<tr><th>Метод<th>Зависимость"
    for (i = 1; i <= n; ++i) {
        s = mdata[mdata_sorted[i]]
        gsub("N", "<i>N</i>", s)
        gsub("*", "<sup>*</sup>", s)
        gsub("=", "\\&#x2248;", s);
        gsub("log2", "log<sub>2</sub>", s);
        text = text "<tr><td>" mdata_sorted[i] "<td align=center>" s "\n"
    }
    text = text "</table>\n</div>"
    print text
}

