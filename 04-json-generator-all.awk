{
  M = 6
  a[$4][$1][$3 - 7] = $2
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
      lflag = 0
      printf "\"%s\":[", j
      for (l = 0; l < M; ++l) {
        if (lflag) printf ","
        lflag = 1
        if (l in a[i][j])
          printf "%d", a[i][j][l]
        else
          printf "\"n/d\""
      }
      #start of a and k coefficients calculation
      for (l = M - 1; l >= 0; --l)
        if (l in a[i][j]) {
          r = l
          break
        }
      c1 = log(a[i][j][r]/a[i][j][0])/log((r + 7)/7)
      #c3 = log(a[i][j][r]/a[i][j][r - 1])/log((r + 7)/(r + 6))
      #if (c1 < 0.95 && c3 >= 0.95) c2 = c3;
      c2 = a[i][j][r]/(r + 7)^c1
      printf ",%f,%f]", c1, c2
      #end of the calculation
      #printf "]"
    }
    printf "}"
  }
  print "}'"
}

