{
    b[$1] += $2
    c[$1]++
}

END {
    split(FILENAME, a, "-")
    for (i in b) printf "%16s %12.0f %s %s %s\n", i, b[i]/c[i], a[1], a[2], a[3]
}

