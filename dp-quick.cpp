/**
* @author Vladimir Yaroslavskiy
* @version 2009.09.17 m765.817
* Conversion to C++ by litwr, 2019.07.14
*/

template<class T> struct DualPivotQuicksort817 {
static const int DIST_SIZE = 13;
static const int TINY_SIZE = 17;
static void sort(vector<T> &a) {
    sort(a, 0, a.size());
}
static void sort(vector<T> &a, int fromIndex, int toIndex) {
    //rangeCheck(a.size(), fromIndex, toIndex);
    dualPivotQuicksort(a, fromIndex, toIndex - 1);
}
static void rangeCheck(int length, int fromIndex, int toIndex) {
/*
    if (fromIndex > toIndex)
        throw runtime_error("fromIndex(" + to_string(fromIndex) + ") toIndex(" + to_string(toIndex) + ")");
    if (fromIndex < 0)
        throw runtime_error("ArrayIndexOutOfBoundsException(fromIndex)"); //FIXME!!
    if (toIndex > length)
        throw runtime_error("ArrayIndexOutOfBoundsException(toIndex)"); //FIXME!!
*/
}
static void dualPivotQuicksort(vector<T> &a, int left, int right) {
    int len = right - left;
    T x;
    if (len < TINY_SIZE) { // insertion sort on tiny array
        for (int i = left + 1; i <= right; i++) {
            for (int j = i; j > left && a[j] < a[j - 1]; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }
    // median indexes
    int sixth = len / 6;
    int m1 = left + sixth;
    int m2 = m1 + sixth;
    int m3 = m2 + sixth;
    int m4 = m3 + sixth;
    int m5 = m4 + sixth;
    // 5-element sorting network
    if (a[m1] > a[m2]) { x = a[m1]; a[m1] = a[m2]; a[m2] = x; }
    if (a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
    if (a[m1] > a[m3]) { x = a[m1]; a[m1] = a[m3]; a[m3] = x; }
    if (a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if (a[m1] > a[m4]) { x = a[m1]; a[m1] = a[m4]; a[m4] = x; }
    if (a[m3] > a[m4]) { x = a[m3]; a[m3] = a[m4]; a[m4] = x; }
    if (a[m2] > a[m5]) { x = a[m2]; a[m2] = a[m5]; a[m5] = x; }
    if (a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if (a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
    // pivots: [ < pivot1 | pivot1 <= && <= pivot2 | > pivot2 ]
    T pivot1 = a[m2];
    T pivot2 = a[m4];
    bool diffPivots = pivot1 != pivot2;
    a[m2] = a[left];
    a[m4] = a[right];
    // center part pointers
    int less = left + 1;
    int great = right - 1;
    // sorting
    if (diffPivots) {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (x < pivot1) {
                a[k] = a[less];
                a[less++] = x;
            } else if (x > pivot2) {
                while (a[great] > pivot2 && k < great)
                    great--;
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    } else {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (x == pivot1)
                continue;
            if (x < pivot1) {
                a[k] = a[less];
                a[less++] = x;
            } else {
                while (a[great] > pivot2 && k < great)
                    great--;
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }
    // swap
    a[left] = a[less - 1];
    a[less - 1] = pivot1;
    a[right] = a[great + 1];
    a[great + 1] = pivot2;
    // left and right parts
    dualPivotQuicksort(a, left, less - 2);
    dualPivotQuicksort(a, great + 2, right);
    // equal elements
    if (great - less > len - DIST_SIZE && diffPivots) {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (x == pivot1) {
                a[k] = a[less];
                a[less++] = x;
            } else if (x == pivot2) {
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (x == pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }
    // center part
    if (diffPivots)
        dualPivotQuicksort(a, less, great);
}
};

template<> struct DualPivotQuicksort817<const char*> {
static const int DIST_SIZE = 13;
static const int TINY_SIZE = 17;
static void sort(vector<const char*> &a) {
    sort(a, 0, a.size());
}
static void sort(vector<const char*> &a, int fromIndex, int toIndex) {
    rangeCheck(a.size(), fromIndex, toIndex);
    dualPivotQuicksort(a, fromIndex, toIndex - 1);
}
static void rangeCheck(int length, int fromIndex, int toIndex) {
/*
    if (fromIndex > toIndex)
        throw runtime_error("fromIndex(" + to_string(fromIndex) + ") toIndex(" + to_string(toIndex) + ")");
    if (fromIndex < 0)
        throw runtime_error("ArrayIndexOutOfBoundsException(fromIndex)"); //FIXME!!
    if (toIndex > length)
        throw runtime_error("ArrayIndexOutOfBoundsException(toIndex)"); //FIXME!!
*/
}
static void dualPivotQuicksort(vector<const char*> &a, int left, int right) {
    int len = right - left;
    const char* x;
    if (len < TINY_SIZE) { // insertion sort on tiny array
        for (int i = left + 1; i <= right; i++) {
            for (int j = i; j > left && strcmp(a[j], a[j - 1]) < 0; j--) {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
        return;
    }
    // median indexes
    int sixth = len / 6;
    int m1 = left + sixth;
    int m2 = m1 + sixth;
    int m3 = m2 + sixth;
    int m4 = m3 + sixth;
    int m5 = m4 + sixth;
    // 5-element sorting network
    if (strcmp(a[m1], a[m2]) > 0) { x = a[m1]; a[m1] = a[m2]; a[m2] = x; }
    if (strcmp(a[m4], a[m5]) > 0) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
    if (strcmp(a[m1], a[m3]) > 0) { x = a[m1]; a[m1] = a[m3]; a[m3] = x; }
    if (strcmp(a[m2], a[m3]) > 0) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if (strcmp(a[m1], a[m4]) > 0) { x = a[m1]; a[m1] = a[m4]; a[m4] = x; }
    if (strcmp(a[m3], a[m4]) > 0) { x = a[m3]; a[m3] = a[m4]; a[m4] = x; }
    if (strcmp(a[m2], a[m5]) > 0) { x = a[m2]; a[m2] = a[m5]; a[m5] = x; }
    if (strcmp(a[m2], a[m3]) > 0) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
    if (strcmp(a[m4], a[m5]) > 0) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
    // pivots: [ < pivot1 | pivot1 <= && <= pivot2 | > pivot2 ]
    const char* pivot1 = a[m2];
    const char* pivot2 = a[m4];
    bool diffPivots = pivot1 != pivot2;
    a[m2] = a[left];
    a[m4] = a[right];
    // center part pointers
    int less = left + 1;
    int great = right - 1;
    // sorting
    if (diffPivots) {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (strcmp(x, pivot1) < 0) {
                a[k] = a[less];
                a[less++] = x;
            } else if (strcmp(x, pivot2) > 0) {
                while (strcmp(a[great], pivot2) > 0 && k < great)
                    great--;
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (strcmp(x, pivot1) < 0) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    } else {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (strcmp(x, pivot1) == 0)
                continue;
            if (strcmp(x, pivot1) < 0) {
                a[k] = a[less];
                a[less++] = x;
            } else {
                while (strcmp(a[great], pivot2) > 0 && k < great)
                    great--;
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (strcmp(x, pivot1) < 0) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }
    // swap
    a[left] = a[less - 1];
    a[less - 1] = pivot1;
    a[right] = a[great + 1];
    a[great + 1] = pivot2;
    // left and right parts
    dualPivotQuicksort(a, left, less - 2);
    dualPivotQuicksort(a, great + 2, right);
    // equal elements
    if (great - less > len - DIST_SIZE && diffPivots) {
        for (int k = less; k <= great; k++) {
            x = a[k];
            if (strcmp(x, pivot1) == 0) {
                a[k] = a[less];
                a[less++] = x;
            } else if (strcmp(x, pivot2) == 0) {
                a[k] = a[great];
                a[great--] = x;
                x = a[k];
                if (strcmp(x, pivot1) == 0) {
                    a[k] = a[less];
                    a[less++] = x;
                }
            }
        }
    }
    // center part
    if (diffPivots)
        dualPivotQuicksort(a, less, great);
}
};

template<class T> void dualPivotQuicksort(vector<T> &a) {
    DualPivotQuicksort817<T>::sort(a);
}

