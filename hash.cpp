template<class T> int hash_func(T d, T minElem, double diff) {
    return (long double)(d - minElem)*(SS - 1)/diff;
}

template<> int hash_func(int64_t d, int64_t minElem, double diff) {
    return (long double)(d - minElem)*(SS - 1)/diff;
}

template<> int hash_func(__int128 d, __int128 minElem, double diff) {
    return (long double)(d - minElem)*(SS - 1)/diff;
}

template<> int hash_func(const char *d, const char *minElem, double diff) {
    return (convert(d) - convert(minElem))*(SS - 1)/diff;
}

template<class T> struct HashSort {
    struct HashElement {
        T data;
        int next;
    };
    vector<HashElement> hashData;
    vector<int> hashPtr;
    int freePtr;
    HashSort() : hashData(SS), hashPtr(SS, -1), freePtr(0) {}
    T minElem, maxElem;
    double diff;
    void addElement(T d) {
        int prevPtr, j = hash_func(d, minElem, diff), curPtr = hashPtr[j];
        if (curPtr == -1) {
           hashPtr[j] = freePtr;
           goto l1;
        }
        prevPtr = -1;
        while (curPtr != -1) {
           if (hashData[curPtr].data > d) {
              if (prevPtr == -1) {
                 hashData[freePtr].next = hashPtr[j];
                 hashPtr[j] = freePtr;
              } else {
                 hashData[prevPtr].next = freePtr;
                 hashData[freePtr].next = curPtr;
              }
              goto l2;
           }
           prevPtr = curPtr;
           curPtr = hashData[curPtr].next;
        }
        hashData[prevPtr].next = freePtr;
l1:
        hashData[freePtr].next = -1;
l2:
        hashData[freePtr++].data = d;
     }
};

template<>
void HashSort<const char*>::addElement(const char *d) {
    int prevPtr, j = hash_func(d, minElem, diff), curPtr = hashPtr[j];
    if (curPtr == -1) {
        hashPtr[j] = freePtr;
        goto l1;
    }
    prevPtr = -1;
    while (curPtr != -1) {
        if (strcmp(hashData[curPtr].data, d) > 0) {
            if (prevPtr == -1) {
                hashData[freePtr].next = hashPtr[j];
                hashPtr[j] = freePtr;
             } else {
                hashData[prevPtr].next = freePtr;
                hashData[freePtr].next = curPtr;
             }
             goto l2; 
        }
        prevPtr = curPtr;
        curPtr = hashData[curPtr].next;
    }
    hashData[prevPtr].next = freePtr;
l1:
    hashData[freePtr].next = -1;
l2:
    hashData[freePtr++].data = d;
}

template<class T> void hash_sort(vector<T> &a) {
    HashSort<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    hs.diff = hs.maxElem - hs.minElem;
    if (hs.diff == 0) hs.diff = 1;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    hs.freePtr = 0;
    for (int i = 0; i < SS; ++i) {
         int j = hs.hashPtr[i];
         while (j != -1) {
             a[hs.freePtr++] = hs.hashData[j].data;
             j = hs.hashData[j].next;
         }
    }
}

template<> void hash_sort(vector<const char*> &a) {
    HashSort<const char *> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    hs.diff = convert(hs.maxElem) - convert(hs.minElem);
    if (hs.diff == 0) hs.diff = 1;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    hs.freePtr = 0;
    for (int i = 0; i < SS; ++i) {
         int j = hs.hashPtr[i];
         while (j != -1) {
             a[hs.freePtr++] = hs.hashData[j].data;
             j = hs.hashData[j].next;
         }
    }
}

