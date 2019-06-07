template <class T>
void qsort1(vector<T> &a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    T x = a[(i + j)/2];
    do {
#ifdef COUNTERS
       while (a[i] < x) ++i, ++comp_cnt;
       while (x < a[j]) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
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
#ifdef COUNTERS
       while (strcmp(a[i], x) < 0) ++i, ++comp_cnt;
       while (strcmp(x, a[j]) < 0) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (strcmp(a[i], x) < 0) ++i;
       while (strcmp(x, a[j]) < 0) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
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
#ifdef COUNTERS
       while (a[i] < x) ++i, ++comp_cnt;
       while (x < a[j]) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
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
#ifdef COUNTERS
       do ++i, ++comp_cnt; while (a[i] < x);
       do --j, ++comp_cnt; while (x < a[j]);
       comp_cnt += 2;
       if (i >= j) break;
       swap(a[i], a[j]); ++exch_cnt;
#else
       do ++i; while (a[i] < x);
       do --j; while (x < a[j]);
       if (i >= j) break;
       swap(a[i], a[j]);
#endif
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
#ifdef COUNTERS
       do ++i, ++comp_cnt; while (strcmp(a[i], x) < 0);
       do --j, ++comp_cnt; while (strcmp(x, a[j]) < 0);
       comp_cnt += 2;
       if (i >= j) break;
       swap(a[i], a[j]); ++exch_cnt;
#else
       do ++i; while (strcmp(a[i], x) < 0);
       do --j; while (strcmp(x, a[j]) < 0);
       if (i >= j) break;
       swap(a[i], a[j]);
#endif
    }
    qsort3(a, LBound, j);
    qsort3(a, j + 1, UBound);
}

template <class T>
void qsort4(vector<T> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    T x = a[UBound];
#ifdef COUNTERS
    for (int j = LBound; j < UBound; ++j)
       if (a[j] < x)
          ++exch_cnt, ++comp_cnt, swap(a[i++], a[j]);
    swap(a[i], a[UBound]); ++exch_cnt;
#else
    for (int j = LBound; j < UBound; ++j)
       if (a[j] < x)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
#endif
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template <>
void qsort4(vector<const char*> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    const char *x = a[UBound];
#ifdef COUNTERS
    for (int j = LBound; j < UBound; ++j)
       if (strcmp(a[j], x) < 0)
          ++exch_cnt, ++comp_cnt, swap(a[i++], a[j]);
    swap(a[i], a[UBound]); ++exch_cnt;
#else
    for (int j = LBound; j < UBound; ++j)
       if (strcmp(a[j], x) < 0)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
#endif
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template<class T>
void qsort2(vector<T> &a, int LBound, int UBound) { //no pivot
    int i = LBound, j = UBound;
    while (i != j) {
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (a[i] <= a[j])
                --j;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (a[i] <= a[j])
                ++i;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
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
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (strcmp(a[i], a[j]) <= 0)
                --j;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (strcmp(a[i], a[j]) <= 0)
                ++i;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
    }
    if (i - 1 > LBound) qsort2(a, LBound, i - 1);
    if (j + 1 < UBound) qsort2(a, j + 1, UBound);
}

