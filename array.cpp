template<class T> void array_sort(vector<T> &a, const int f) {
    vector<T> auxArray(f*SS);
    T maxElem = a[0], minElem = a[0];
    vector<bool> used(f*SS);
    int i, j, l, k, m;
    for (int i = 1; i < SS; ++i) {
        if (maxElem < a[i]) maxElem = a[i];
        if (minElem > a[i]) minElem = a[i];
    }
    if (maxElem == minElem) return;
    for (i = 0; i < SS; ++i) {
        j = long(a[i] - minElem)*(f*SS - 1)/(maxElem - minElem);
        if (!used[j])
            auxArray[j] = a[i], used[j] = true;
        else {
            if (auxArray[j] > a[i]) {
                while (j > 0)
                    if (used[j - 1] && auxArray[j - 1] > a[i])
                        --j;
                    else
                        break;
                m = -1;
            } else {
                while (j + 1 < f*SS)
                    if (used[j + 1] && auxArray[j + 1] < a[i])
                        ++j;
                    else
                        break;
                m = 1;
           }
           k = 0;
           for (;;) {
               if (k + j >= 0 && k + j < f*SS && !used[k + j])
                   break;
               if (k > 0) k = -k; else k = 1 - k;
           }
           l = j + k;
           if (k > 0) k = 1; else k = -1;
           j += (m + k)/2;
           while (l != j) {
               auxArray[l] = auxArray[l - k];used[l] = true;
               l -= k;
           }
           auxArray[j] = a[i];used[j] = true;
        }
    }
    for (i = j = 0; i < SS; ++j)
        if (used[j])
            a[i++] = auxArray[j];
}

template<> void array_sort(vector<const char*> &a, const int f) {
    vector<const char*> auxArray(f*SS);
    const char *maxElem = a[0], *minElem = a[0];
    vector<bool> used(f*SS);
    int i, j, l, k, m;
    for (int i = 1; i < SS; ++i) {
        if (strcmp(maxElem, a[i]) < 0) maxElem = a[i];
        if (strcmp(minElem, a[i]) > 0) minElem = a[i];
    }
    int c1 = f*SS - 1, c2 = convert(maxElem) - convert(minElem);
    for (i = 0; i < SS; ++i) {
        j = long(convert(a[i]) - convert(minElem))*(f*SS - 1)/(convert(maxElem) - convert(minElem));
        if (!used[j])
            auxArray[j] = a[i], used[j] = true;
        else {
            if (strcmp(auxArray[j], a[i]) > 0) {
                while (j > 0)
                    if (used[j - 1] && strcmp(auxArray[j - 1], a[i]) > 0)
                        --j;
                    else
                        break;
                m = -1;
            } else {
                while (j + 1 < f*SS)
                    if (used[j + 1] && strcmp(auxArray[j + 1], a[i]) < 0)
                        ++j;
                    else
                        break;
                m = 1;
           }
           k = 0;
           for (;;) {
               if (k + j >= 0 && k + j < f*SS && !used[k + j])
                   break;
               if (k > 0) k = -k; else k = 1 - k;
           }
           l = j + k;
           if (k > 0) k = 1; else k = -1;
           j += (m + k)/2;
           while (l != j) {
               auxArray[l] = auxArray[l - k];used[l] = true;
               l -= k;
           }
           auxArray[j] = a[i];used[j] = true;
        }
    }
    for (i = j = 0; i < SS; ++j)
        if (used[j])
            a[i++] = auxArray[j];

}
