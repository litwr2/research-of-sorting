/**
* @author Vladimir Yaroslavskiy
* @version 2009.09.17 m765.817
* Conversion to C++ by litwr, 2019.07.14
*/

template<class T> struct DualPivotQuicksort817 {
    static const int DIST_SIZE = 13;
    static const int TINY_SIZE = 17;
    static void sort(vector<T> &a) {
        dualPivotQuicksort(a, 0, a.size() - 1);
    }
    static void dualPivotQuicksort(vector<T> &a, int left, int right) {
        int len = right - left;
        if (len < TINY_SIZE) { // insertion sort on tiny array
            for (int i = left + 1; i <= right; i++)
                for (int j = i; j > left && a[j] < a[j - 1]; j--)
                    swap(a[j - 1], a[j]);
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
        if (a[m1] > a[m2]) swap(a[m1], a[m2]);
        if (a[m4] > a[m5]) swap(a[m4], a[m5]);
        if (a[m1] > a[m3]) swap(a[m1], a[m3]);
        if (a[m2] > a[m3]) swap(a[m2], a[m3]);
        if (a[m1] > a[m4]) swap(a[m1], a[m4]);
        if (a[m3] > a[m4]) swap(a[m3], a[m4]);
        if (a[m2] > a[m5]) swap(a[m2], a[m5]);
        if (a[m2] > a[m3]) swap(a[m2], a[m3]);
        if (a[m4] > a[m5]) swap(a[m4], a[m5]);
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
        if (diffPivots)
            for (int k = less; k <= great; k++) {
                if (a[k] < pivot1)
                    swap(a[k], a[less++]);
                else if (a[k] > pivot2) {
                    while (a[great] > pivot2 && k < great)
                        great--;
                    swap(a[k], a[great--]);
                    if (a[k] < pivot1)
                        swap(a[k], a[less++]);
                }
            }
        else
            for (int k = less; k <= great; k++)
                if (a[k] == pivot1)
                    continue;
                else if (a[k] < pivot1)
                    swap(a[k], a[less++]);
                else {
                    while (a[great] > pivot2 && k < great)
                        great--;
                    swap(a[k], a[great--]);
                    if (a[k] < pivot1)
                        swap(a[k], a[less++]);
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
        if (great - less > len - DIST_SIZE && diffPivots)
            for (int k = less; k <= great; k++)
                if (a[k] == pivot1)
                    swap(a[k], a[less++]);
                else if (a[k] == pivot2) {
                    swap(a[k], a[great--]);
                    if (a[k] == pivot1)
                        swap(a[k],  a[less++]);
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
        dualPivotQuicksort(a, 0, a.size() - 1);
    }
    static void dualPivotQuicksort(vector<const char*> &a, int left, int right) {
        int len = right - left;
        if (len < TINY_SIZE) { // insertion sort on tiny array
            for (int i = left + 1; i <= right; i++)
                for (int j = i; j > left && strcmp(a[j], a[j - 1]) < 0; j--)
                    swap(a[j - 1], a[j]);
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
        if (strcmp(a[m1], a[m2]) > 0) swap(a[m1], a[m2]);
        if (strcmp(a[m4], a[m5]) > 0) swap(a[m4], a[m5]);
        if (strcmp(a[m1], a[m3]) > 0) swap(a[m1], a[m3]);
        if (strcmp(a[m2], a[m3]) > 0) swap(a[m3], a[m2]);
        if (strcmp(a[m1], a[m4]) > 0) swap(a[m1], a[m4]);
        if (strcmp(a[m3], a[m4]) > 0) swap(a[m3], a[m4]);
        if (strcmp(a[m2], a[m5]) > 0) swap(a[m5], a[m2]);
        if (strcmp(a[m2], a[m3]) > 0) swap(a[m3], a[m2]);
        if (strcmp(a[m4], a[m5]) > 0) swap(a[m4], a[m5]);
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
        if (diffPivots)
            for (int k = less; k <= great; k++) {
                if (strcmp(a[k], pivot1) < 0)
                    swap(a[k], a[less++]);
                else if (strcmp(a[k], pivot2) > 0) {
                    while (strcmp(a[great], pivot2) > 0 && k < great)
                        great--;
                    swap(a[k], a[great--]);
                    if (strcmp(a[k], pivot1) < 0)
                        swap(a[k], a[less++]);
                }
            }
        else
            for (int k = less; k <= great; k++)
                if (strcmp(a[k], pivot1) == 0)
                    continue;
                else if (strcmp(a[k], pivot1) < 0)
                    swap(a[k], a[less++]);
                else {
                    while (strcmp(a[great], pivot2) > 0 && k < great)
                        great--;
                    swap(a[k], a[great--]);
                    if (strcmp(a[k], pivot1) < 0)
                        swap(a[k], a[less++]);
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
        if (great - less > len - DIST_SIZE && diffPivots)
            for (int k = less; k <= great; k++)
                if (strcmp(a[k], pivot1) == 0)
                    swap(a[k], a[less++]);
                else if (strcmp(a[k], pivot2) == 0) {
                    swap(a[k], a[great--]);
                    if (strcmp(a[k], pivot1) == 0)
                        swap(a[k], a[less++]);
                }
        // center part
        if (diffPivots)
            dualPivotQuicksort(a, less, great);
    }
};

template<class T> void dualPivotQuicksort(vector<T> &a) {
    DualPivotQuicksort817<T>::sort(a);
}

