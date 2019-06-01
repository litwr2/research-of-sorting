template<class T> struct BinaryTreeForHash {
     struct Node {
         T data;
         int l, r;
     };
     int i, *storageRoot;
     Node *storage;
     int allocIdx = 0;
     T maxElem, minElem;
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
         int j = hash_func(d, minElem, maxElem);
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
         int j = hash_func(d, minElem, maxElem);
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

template<class T> void hashbt_sort2(vector<T> &a) {
    BinaryTreeForHash<T> bt;
    
    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (bt.maxElem < a[i]) bt.maxElem = a[i];
        if (bt.minElem > a[i]) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

template<> void hashbt_sort2(vector<const char* > &a) {
    BinaryTreeForHash<const char*> bt;
    
    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(bt.maxElem, a[i]) < 0) bt.maxElem = a[i];
        if (strcmp(bt.minElem, a[i]) > 0) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

