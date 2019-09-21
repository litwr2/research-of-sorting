// three sort methods which use hashes which use binary trees instead of lists
// the first method uses an unbalanced tree, the second - a tree (std::multiset) from the C++ standard library
// the third - a tree (boost::container::multiset) from the boost library

template<class T> struct BinaryTreeForHash {
     struct Node {
         T data;
         int l, r;
     };
     int i, *storageRoot;
     Node *storage;
     int allocIdx = 0;
     T maxElem, minElem;
     double diff;
     BinaryTreeForHash() {
         storageRoot = new int[SS];
         for (int i = 0; i < SS; ++i) storageRoot[i] = -1;
         storage = new Node[SS];
     }
     ~BinaryTreeForHash() {
         delete [] storageRoot;
         delete [] storage;
     }
     void insert(T d) {
         int j = hash_func(d, minElem, diff);
         int t = storageRoot[j], p = t, dir;
         storage[allocIdx] = {d, -1, -1};
         while (t >= 0) {
              p = t;
              if (d < storage[t].data)
                  t = storage[t].l, dir = 0;
              else if (d > storage[t].data)
                  t = storage[t].r, dir = 1;
              else if (rand()&1)
                  t = storage[t].l, dir = 0;
              else
                  t = storage[t].r, dir = 1;
         }
         if (p == -1)
             storageRoot[j] = allocIdx;
         else if (dir == 0)
            storage[p].l = allocIdx;
         else
            storage[p].r = allocIdx;
         ++allocIdx;
     }
     void traversal(vector<T> &a, int idx) {
          if (idx < 0) return;
          traversal(a, storage[idx].l);
          a[i++] = storage[idx].data;
          traversal(a, storage[idx].r);
     }
};

template<> struct BinaryTreeForHash<const char*> {
     struct Node {
         const char* data;
         int l, r;
     };
     int i, *storageRoot;
     Node *storage;
     int allocIdx = 0;
     const char *maxElem, *minElem;
     double diff;
     BinaryTreeForHash() {
         storageRoot = new int[SS];
         for (int i = 0; i < SS; ++i) storageRoot[i] = -1;
         storage = new Node[SS];
     }
     ~BinaryTreeForHash() {
         delete [] storageRoot;
         delete [] storage;
     }
     void insert(const char *d) {
         int j = hash_func(d, minElem, diff);
         int t = storageRoot[j], p = t, dir;
         storage[allocIdx] = {d, -1, -1};
         while (t >= 0) {
              p = t;
              if (strcmp(d, storage[t].data) < 0)
                  t = storage[t].l, dir = 0;
              else if (strcmp(d, storage[t].data) > 0)
                  t = storage[t].r, dir = 1;
              else if (rand()&1)
                  t = storage[t].l, dir = 0;
              else
                  t = storage[t].r, dir = 1;
         }
         if (p == -1)
             storageRoot[j] = allocIdx;
         else if (dir == 0)
            storage[p].l = allocIdx;
         else
            storage[p].r = allocIdx;
         ++allocIdx;
     }
     void traversal(vector<const char *> &a, int idx) {
          if (idx < 0) return;
          traversal(a, storage[idx].l);
          a[i++] = storage[idx].data;
          traversal(a, storage[idx].r);
     }
};

template<class T> void hashbt_sort(vector<T> &a) {
    BinaryTreeForHash<T> bt;

    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (bt.maxElem < a[i]) bt.maxElem = a[i];
        if (bt.minElem > a[i]) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    bt.diff = bt.maxElem - bt.minElem;
    if (bt.diff == 0) bt.diff = 1;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

template<> void hashbt_sort(vector<const char* > &a) {
    BinaryTreeForHash<const char*> bt;

    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(bt.maxElem, a[i]) < 0) bt.maxElem = a[i];
        if (strcmp(bt.minElem, a[i]) > 0) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    bt.diff = convert(bt.maxElem) - convert(bt.minElem);
    if (bt.diff == 0) bt.diff = 1;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

template<class T> struct HashBTSort {
    typedef std::multiset<T> HashElement;
    vector<HashElement> hashData;
    T minElem, maxElem;
    double diff;
    HashBTSort() : hashData(SS) {}
    void addElement(T d) {
        hashData[hash_func(d, minElem, diff)].insert(d);
    }
};

template<> struct HashBTSort<const char*> {
    typedef std::multiset<const char*, pchar_less> HashElement;
    vector<HashElement> hashData;
    const char *minElem, *maxElem;
    double diff;
    HashBTSort() : hashData(SS) {}
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, diff)].insert(d);
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
    hs.diff = hs.maxElem - hs.minElem;
    if (hs.diff == 0) hs.diff = 1;
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
    hs.diff = convert(hs.maxElem) - convert(hs.minElem);
    if (hs.diff == 0) hs.diff = 1;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<class T> struct HashBTSort_boost {
    typedef boost::container::multiset<T> HashElement;
    vector<HashElement> hashData;
    T minElem, maxElem;
    double diff;
    HashBTSort_boost() : hashData(SS) {}
    void addElement(T d) {
        hashData[hash_func(d, minElem, diff)].insert(d);
    }
};

template<> struct HashBTSort_boost<const char*> {
    typedef boost::container::multiset<const char*, pchar_less> HashElement;
    vector<HashElement> hashData;
    const char *minElem, *maxElem;
    double diff;
    HashBTSort_boost() : hashData(SS) {}
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, diff)].insert(d);
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
    hs.diff = hs.maxElem - hs.minElem;
    if (hs.diff == 0) hs.diff = 1;
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
    hs.diff = convert(hs.maxElem) - convert(hs.minElem);
    if (hs.diff == 0) hs.diff = 1;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

