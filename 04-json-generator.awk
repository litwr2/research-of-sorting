{
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
        for (l = 0; l < 3; ++l) {
          if (lflag) printf ","
          lflag = 1
          if (l in a[i][j][k]) 
            printf "%d", a[i][j][k][l]
          else
            printf "\"n/a\""
        }
        printf "]"
      }
      printf "}"
    }
    printf "}"
  }
  print "}'"
}
