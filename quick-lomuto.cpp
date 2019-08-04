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
