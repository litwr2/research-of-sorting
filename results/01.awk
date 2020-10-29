BEGIN {
    printf ".separator ' '\n"
    printf "create table r (id text, time real, size real, elementtype text, filling text, passes integer, diff real, deviation real);"
}
NF == 8 {
    printf "insert into r values ("
    printf "'%s', %.2f, %.0f, '%s', '%s', %d, %.2f, %.4f);\n", $1, $2, $3, $4, $5, $6, $7, $8
}
END {
    printf "select id,time,filling from r order by filling, time;\n"
}
