#define MEDIAN3
namespace SafeQuicksortWithInsertionSort {
    jmp_buf jmpdata;
    template <class T>
    void qsort_safe(vector<T> &a, int LBound, int UBound, int lvl) {  //modified Hoare quicksort
        if (UBound - LBound <= 16) { // insertion sort on tiny array
            for (int i = LBound + 1; i <= UBound; i++)
                for (int j = i; j > LBound && a[j] < a[j - 1]; j--)
                    swap(a[j - 1], a[j]);
            return;
        }
        if (--lvl == 0) longjmp(jmpdata, 1);
        int i = LBound, j = UBound;
        T x = a[(i + j)/2];
#ifdef MEDIAN3
        if (a[i] < x) {  //median of 3
            if (x >= a[j])
                x = a[i] < a[j] ? a[j] : a[i];
        } else
            if (x <= a[j])
                x = a[i] < a[j] ? a[i] : a[j];
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
        if (LBound < j) qsort_safe(a, LBound, j, lvl);
        if (i < UBound) qsort_safe(a, i, UBound, lvl);
    }

    template <>
    void qsort_safe(vector<const char*> &a, int LBound, int UBound, int lvl) {  //modified Hoare quicksort
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
        if (strcmp(a[i], x) < 0) {  //median of 3
            if (strcmp(x, a[j]) >= 0)
                x = strcmp(a[i], a[j]) < 0 ? a[j] : a[i];
        } else
            if (strcmp(x, a[j]) <= 0)
                x = strcmp(a[i], a[j]) < 0 ? a[i] : a[j];
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
        if (LBound < j) qsort_safe(a, LBound, j, lvl);
        if (i < UBound) qsort_safe(a, i, UBound, lvl);
    }
}

template <class T>
void qsort_safe(vector<T> &a, int LBound, int UBound) {
    int lvl = log(UBound - LBound)*4;
    setjmp(SafeQuicksortWithInsertionSort::jmpdata);
    SafeQuicksortWithInsertionSort::qsort_safe(a, LBound, UBound, lvl);
}

