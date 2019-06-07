template<class T> int hash_func(T d, T minElem, T maxElem) {
    return long(d - minElem)*(SS - 1)/(maxElem - minElem);
}

template<> int hash_func(int64_t d, int64_t minElem, int64_t maxElem) {
    return (long double)(d - minElem)*(SS - 1)/(maxElem - minElem);
}

template<> int hash_func(const char *d, const char *minElem, const char *maxElem) {
    return long(convert(d) - convert(minElem))*(SS - 1)/(convert(maxElem) - convert(minElem));
}

template<class T> struct HashSort {
    struct HashElement {
        T data;
        int next;
    };
    HashElement *hashData;
    int *hashPtr, freePtr;
    T minElem, maxElem;
    HashSort() {
        hashData = new HashElement[SS];
        hashPtr = new int[SS];
        freePtr = 0;
        for (int i = 0; i < SS; ++i)
           hashPtr[i] = -1;
    }
    ~HashSort() {
        delete [] hashData;
        delete [] hashPtr;
    }
    void addElement(T d) {
        int prevPtr, j = hash_func(d, minElem, maxElem), curPtr = hashPtr[j];
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
    int prevPtr, j = hash_func(d, minElem, maxElem), curPtr = hashPtr[j];
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

template<> void hash_sort(vector<const char *> &a) {
    HashSort<const char *> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
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

template<class T> struct HashBTSort {
    typedef std::multiset<T> HashElement;
    HashElement *hashData;
    T minElem, maxElem;
    HashBTSort() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort() {
        delete [] hashData;
    }
    void addElement(T d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<> struct HashBTSort<const char*> {
    typedef std::multiset<const char*, pchar_less> HashElement;
    HashElement *hashData;
    const char *minElem, *maxElem;
    HashBTSort() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort() {
        delete [] hashData;
    }
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<class T> void hashbt_sort_std(vector<T> &a) {
    HashBTSort<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<> void hashbt_sort_std(vector<const char*> &a) {
    HashBTSort<const char*> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<class T> struct HashBTSort_boost {
    typedef boost::container::multiset<T> HashElement;
    HashElement *hashData;
    T minElem, maxElem;
    HashBTSort_boost() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort_boost() {
        delete [] hashData;
    }
    void addElement(T d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<> struct HashBTSort_boost<const char*> {
    typedef boost::container::multiset<const char*, pchar_less> HashElement;
    HashElement *hashData;
    const char *minElem, *maxElem;
    HashBTSort_boost() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort_boost() {
        delete [] hashData;
    }
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<class T> void hashbt_sort_boost(vector<T> &a) {
    HashBTSort_boost<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<> void hashbt_sort_boost(vector<const char*> &a) {
    HashBTSort_boost<const char*> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

