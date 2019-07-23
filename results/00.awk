{
    if (min[$1] == 0) min[$1] = 1e15
    if ($2 < min[$1]) min[$1] = $2
    if ($2 > max[$1]) max[$1] = $2
    b[$1] += $2
    c[$1]++
}

END {
    split(FILENAME, a, "-")
    for (i in b) printf "%16s %14.1f %s %s %s %d %d %.2f\n", i, b[i]/c[i], a[1], a[2], a[3], c[i], max[i] - min[i], (max[i] - min[i])*100./b[i]*c[i]
}

