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

template <class T>
void qsort3(vector<T> &a, int LBound, int UBound) { //Hoare, varian 2
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
void qsort3(vector<const char*> &a, int LBound, int UBound) { //Hoare, varian 2
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

template <class T>
void qsort4(vector<T> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    T x = a[UBound];
    for (int j = LBound; j < UBound; ++j)
       if (a[j] < x)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template <>
void qsort4(vector<const char*> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    const char *x = a[UBound];
    for (int j = LBound; j < UBound; ++j)
       if (strcmp(a[j], x) < 0)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template<class T>
void qsort2(vector<T> &a, int LBound, int UBound) { //no pivot
    int i = LBound, j = UBound;
    while (i != j) {
        while (i != j) {
            if (a[i] <= a[j])
                --j;
            else {
                swap(a[i], a[j]);
                break;
            }
        }
        while (i != j) {
            if (a[i] <= a[j])
                ++i;
            else {
                swap(a[i], a[j]);
                break;
            }
        }
    }
    if (i - 1 > LBound) qsort2(a, LBound, i - 1);
    if (j + 1 < UBound) qsort2(a, j + 1, UBound);
}

template<>
void qsort2(vector<const char*> &a, int LBound, int UBound) { //no pivot
    int i = LBound, j = UBound;
    while (i != j) {
        while (i != j) {
            if (strcmp(a[i], a[j]) <= 0)
                --j;
            else {
                swap(a[i], a[j]);
                break;
            }
        }
        while (i != j) {
            if (strcmp(a[i], a[j]) <= 0)
                ++i;
            else {
                swap(a[i], a[j]);
                break;
            }
        }
    }
    if (i - 1 > LBound) qsort2(a, LBound, i - 1);
    if (j + 1 < UBound) qsort2(a, j + 1, UBound);
}

