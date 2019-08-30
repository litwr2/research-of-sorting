{
  M = 6
  n = substr($3, 3) - 3
  a[$5][$4][$1][n] = $2
}
END {
  printf "var json = '{"
  for (i in a) {
    if (iflag) printf ","
    iflag = 1
    jflag = 0
    printf "\"%s\":{", i
    for (j in a[i]) {
      if (jflag) printf ","
      jflag = 1
      kflag = 0
      printf "\"%s\":{", j
      for (k in a[i][j]) {
        if (kflag) printf ","
        kflag = 1
        lflag = 0
        printf "\"%s\":[", k
        for (l = 0; l < M; ++l) {
          if (lflag) printf ","
          lflag = 1
          if (l in a[i][j][k])
            printf "%.3f", a[i][j][k][l]/1000.
          else
            printf "\"n/d\""
        }
        #start of a and k coefficients calculation
        for (l = M - 1; l >= 0; --l)
          if (l in a[i][j][k]) {
            r = l
            break
          }
        #c1 = log(a[i][j][k][r]/a[i][j][k][r - 1])/log(10)
        t = 0
        while (a[i][j][k][t] < 10 || a[i][j][k][t]*5 > a[i][j][k][t + 1] && t + 1 < r) ++t
        c1 = log(a[i][j][k][r]/a[i][j][k][t])/log(10)/(r - t)
        #c3 = log(a[i][j][k][r]/a[i][j][k][r - 1])/log(10)
        #if (c1 < 0.95 && c3 >= 0.95) c2 = c3;
        c2 = a[i][j][k][r]/10^(c1*(r + 3))
        printf ",%f,%f]", c1, c2
        #end of the calculation
        #printf "]"
      }
      printf "}"
    }
    printf "}"
  }
  print "}'"
}
