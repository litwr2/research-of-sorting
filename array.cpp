template<class T> void array_sort(vector<T> &a) {
    const int f = 2;
    T *auxArray = new T[f*SS], maxElem = a[0], minElem = a[0];
    int i, j, l, k, m;
    for (int i = 1; i < SS; ++i) {
        if (maxElem < a[i]) maxElem = a[i];
        if (minElem > a[i]) minElem = a[i];
    }
    if (maxElem == minElem) return;
    for (i = 0; i < f*SS; ++i)
#ifndef STRINGS
        auxArray[i] = {-1};    //so we can't use negative numbers
#else
        auxArray[i] = {0};
#endif
    for (i = 0; i < SS; ++i) {
        j = long(a[i] - minElem)*(f*SS - 1)/(maxElem - minElem);
#ifndef STRINGS
        if (auxArray[j] == -1)
#else
        if (auxArray[j] == string({0}))
#endif
            auxArray[j] = a[i];
        else {
            if (auxArray[j] > a[i]) {
                while (j > 0)
                    if (auxArray[j - 1] > a[i])
                        --j;
                    else
                        break;
                m = -1;
            } else {
                while (j + 1 < f*SS)
#ifndef STRINGS
                    if (auxArray[j + 1] < a[i] && auxArray[j + 1] != -1)
#else
                    if (auxArray[j + 1] < a[i] && auxArray[j + 1] != string({0}))
#endif
                        ++j;
                    else
                        break;
                m = 1;
           }
           k = 0;
           for (;;) {
#ifndef STRINGS
               if (k + j >= 0 && k + j < f*SS && auxArray[k + j] == -1)
#else
               if (k + j >= 0 && k + j < f*SS && auxArray[k + j] == string({0}))
#endif
                   break;
               if (k > 0) k = -k; else k = 1 - k;
           }
           l = j + k;
           if (k > 0) k = 1; else k = -1;
           j += (m + k)/2;
           while (l != j) {
               auxArray[l] = auxArray[l - k];
               l -= k;
           }
           auxArray[j] = a[i];
        }
    }
    for (i = j = 0; i < SS; ++j)
#ifndef STRINGS
        if (auxArray[j] != -1)
#else
        if (auxArray[j] != string({0}))
#endif
            a[i++] = auxArray[j];
    delete [] auxArray;
}

