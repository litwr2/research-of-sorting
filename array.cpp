template<class T>
int array_index(const T &a, T minElem, T maxElem, int c1) {
    return long(a - minElem)*c1/(maxElem - minElem);
}

template<>
int array_index(const int64_t &a, int64_t minElem, int64_t maxElem, int c1) {
    return (long double)(a - minElem)*c1/(maxElem - minElem);
}

template<>
int array_index(const __int128 &a, __int128 minElem, __int128 maxElem, int c1) {
    return (long double)(a - minElem)*c1/(maxElem - minElem);
}

template<class T> void array_sort(vector<T> &a, const int f) {
    T maxElem = a[0], minElem = a[0];
    int i, j, l, k, m;
    for (int i = 1; i < SS; ++i) {
	if (maxElem < a[i]) maxElem = a[i];
	if (minElem > a[i]) minElem = a[i];
    }
    if (maxElem == minElem) return;
    int c1 = f*SS - 1, c2 = maxElem - minElem;
    //if (sizeof(int)*f - f >> 3 > sizeof(T)*(f - 1)) {
    if (sizeof(T) <= sizeof(int)) {
	    vector<T> auxArray(f*SS);
	    vector<bool> used(f*SS);
	    for (i = 0; i < SS; ++i) {
		j = array_index(a[i], minElem, maxElem, c1);
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
		       auxArray[l] = auxArray[l - k];
                       used[l] = true;
		       l -= k;
		   }
		   auxArray[j] = a[i];used[j] = true;
		}
	    }
	    for (i = j = 0; i < SS; ++j)
		if (used[j])
		    a[i++] = auxArray[j];
    } else {
	    vector<int> auxArray(f*SS, -1);
	    for (i = 0; i < SS; ++i) {
		j = array_index(a[i], minElem, maxElem, f);
		if (auxArray[j] < 0)
		    auxArray[j] = i;
		else {
		    if (a[auxArray[j]] > a[i]) {
		        while (j > 0)
		            if (auxArray[j - 1] >= 0 && a[auxArray[j - 1]] > a[i])
		                --j;
		            else
		                break;
		        m = -1;
		    } else {
		        while (j + 1 < f*SS)
		            if (auxArray[j + 1] >= 0 && a[auxArray[j + 1]] < a[i])
		                ++j;
		            else
		                break;
		        m = 1;
		   }
		   k = 0;
		   for (;;) {
		       if (k + j >= 0 && k + j < f*SS && auxArray[k + j] < 0)
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
		   auxArray[j] = i;
		}
	    }
            auto copy_of_a = a;
	    for (i = j = 0; i < SS; ++j)
		if (auxArray[j] >= 0)
		    a[i++] = copy_of_a[auxArray[j]];
    }
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
    if (maxElem == minElem) return;
    int c1 = f*SS - 1, c2 = convert(maxElem) - convert(minElem);
    if (c2 == 0) c2 = 1;
    for (i = 0; i < SS; ++i) {
        j = long(convert(a[i]) - convert(minElem))*c1/c2;
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

