#define MEDIAN3
namespace SafeQuicksortWithInsertionSort {
    jmp_buf jmpdata;
    template <class T>
    void qsort_safe1(vector<T> &a, int LBound, int UBound, int lvl) {  //modified Hoare quicksort
        if (UBound - LBound <= 16) { // insertion sort on tiny array
            for (int i = LBound + 1; i <= UBound; i++)
                for (int j = i; j > LBound && a[j] < a[j - 1]; j--)
                    swap(a[j - 1], a[j]);
            return;
        }
        if (--lvl == 0) longjmp(jmpdata, 1);
        int i = LBound, j = UBound, p = (i + j)/2;
        T x = a[(i + j)/2];
#ifdef MEDIAN3
        if (a[0] < x) {  //median of 3
            if (x >= a[j])
                x = a[0] < a[j] ? a[j] : a[0];
        } else 
            if (x <= a[j])
                x = a[0] < a[j] ? a[0] : a[j];
#endif
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
        if (LBound < j) qsort_safe1(a, LBound, j, lvl);
        if (i < UBound) qsort_safe1(a, i, UBound, lvl);
    }

    template <>
    void qsort_safe1(vector<const char*> &a, int LBound, int UBound, int lvl) {  //modified Hoare quicksort
        if (UBound - LBound <= 16) { // insertion sort on tiny array
            for (int i = LBound + 1; i <= UBound; i++)
                for (int j = i; j > LBound && strcmp(a[j], a[j - 1]) < 0; j--)
                    swap(a[j - 1], a[j]);
            return;
        }
        if (--lvl == 0) longjmp(jmpdata, 1);
        int i = LBound, j = UBound;
        const char *x = a[(i + j)/2];
#ifdef MEDIAN3
        if (strcmp(a[0], x) < 0) {  //median of 3
            if (strcmp(x, a[j]) >= 0)
                x = strcmp(a[0], a[j]) < 0 ? a[j] : a[0];
        } else 
            if (strcmp(x, a[j]) <= 0)
                x = strcmp(a[0], a[j]) < 0 ? a[0] : a[j];
#endif
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
        if (LBound < j) qsort_safe1(a, LBound, j, lvl);
        if (i < UBound) qsort_safe1(a, i, UBound, lvl);
    }
}

template <class T>
void qsort_safe(vector<T> &a, int LBound, int UBound) {
    int lvl = log(UBound - LBound)*4;
    setjmp(SafeQuicksortWithInsertionSort::jmpdata);
    SafeQuicksortWithInsertionSort::qsort_safe1(a, LBound, UBound, lvl);
}

