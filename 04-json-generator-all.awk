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
          printf "\"n/a\""
      }
      printf "]"
    }
    printf "}"
  }
  print "}'"
}

