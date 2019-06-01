template<class T, int S> class Sort_alloc : public allocator<T> {
   void* pool;
   int count;
public:
   template<class U> struct rebind { typedef Sort_alloc<U, S> other; };
   Sort_alloc() { count = 0; pool = new char [sizeof(T)*S]; }
   T* allocate(size_t, void* = 0);
   void deallocate(T*, size_t) {}
   ~Sort_alloc() { delete [] (char*)pool; }
};

template<class T, int S> T* Sort_alloc<T, S>::allocate(size_t n, void*) {
   T* p = static_cast<T*>(pool) + count;
   count += n;
   return p;
}

template<class T>
void tree_sort_stl(vector<T>& a) {
    multiset<T, less<T>, Sort_alloc<T, SS>> ms;
    //multiset<T> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

struct pchar_less {
    bool operator()(const char *l, const char *r) const { return strcmp(l, r) < 0; }
};
 
template<>
void tree_sort_stl(vector<const char*>& a) {
    multiset<const char*, pchar_less, Sort_alloc<const char*, SS>> ms;
    //multiset<const char*, pchar_less> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

template<class T>
void tree_sort_boost(vector<T>& a) {
    boost::container::multiset<T, less<T>, Sort_alloc<T, SS>> ms;
    //boost::container::multiset<T> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

template<>
void tree_sort_boost(vector<const char*>& a) {
    boost::container::multiset<const char*, pchar_less, Sort_alloc<const char*, SS>> ms;
    //boost::container::multiset<const char*, pchar_less> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

