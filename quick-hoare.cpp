template <class T>
void qsort1(vector<T> &a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    T x = a[(i + j)/2];
    do {
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (LBound < j) qsort1(a, LBound, j);
    if (i < UBound) qsort1(a, i, UBound);
}

template <>
void qsort1(vector<const char*> &a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    const char *x = a[(i + j)/2];
    do {
       while (strcmp(a[i], x) < 0) ++i;
       while (strcmp(x, a[j]) < 0) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (LBound < j) qsort1(a, LBound, j);
    if (i < UBound) qsort1(a, i, UBound);
}

template <class T>
void qsort1tc(vector<T> &a, int LBound, int UBound) { //tail call optimization
    int i = LBound, j = UBound;
LOOP:
    T x = a[(i + j)/2];
    do {
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (j - LBound < UBound - i) {
        if (LBound < j) qsort1(a, LBound, j);
        if (i < UBound) {   // qsort1(a, i, UBound);
            LBound = i;
            j = UBound;
            goto LOOP;
        }
    }
    else {
    if (i < UBound) qsort1(a, i, UBound);
        if (LBound < j) {  // qsort1(a, LBound, j);
            i = LBound;
            UBound = j;
            goto LOOP;
        }
    }
}

template <>
void qsort1tc(vector<const char*> &a, int LBound, int UBound) { //tail call optimization
    int i = LBound, j = UBound;
LOOP:
    const char *x = a[(i + j)/2];
    do {
       while (strcmp(a[i], x) < 0) ++i;
       while (strcmp(x, a[j]) < 0) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (j - LBound < UBound - i) {
        if (LBound < j) qsort1(a, LBound, j);
        if (i < UBound) {   // qsort1(a, i, UBound);
            LBound = i;
            j = UBound;
            goto LOOP;
        }
    }
    else {
    if (i < UBound) qsort1(a, i, UBound);
        if (LBound < j) {  // qsort1(a, LBound, j);
            i = LBound;
            UBound = j;
            goto LOOP;
        }
    }
}

template <class T>
void qsort3(vector<T> &a, int LBound, int UBound) { //Hoare, variant 2
    if (LBound >= UBound) return;
    int i = LBound - 1, j = UBound + 1;
    T x = a[(i + j)/2];
    for(;;) {
       do ++i; while (a[i] < x);
       do --j; while (x < a[j]);
       if (i >= j) break;
       swap(a[i], a[j]);
    }
    qsort3(a, LBound, j);
    qsort3(a, j + 1, UBound);
}

template <>
void qsort3(vector<const char*> &a, int LBound, int UBound) { //Hoare, variant 2
    if (LBound >= UBound) return;
    int i = LBound - 1, j = UBound + 1;
    const char *x = a[(i + j)/2];
    for(;;) {
       do ++i; while (strcmp(a[i], x) < 0);
       do --j; while (strcmp(x, a[j]) < 0);
       if (i >= j) break;
       swap(a[i], a[j]);
    }
    qsort3(a, LBound, j);
    qsort3(a, j + 1, UBound);
}

