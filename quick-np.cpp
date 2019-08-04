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
