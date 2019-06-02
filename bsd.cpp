#include <bsd/stdlib.h>

template <class T>
void mergesort_bsd(vector<T> &a) {
     mergesort(&a[0], SS, sizeof(T), cmpfunc<T>);
}

template <>
void mergesort_bsd(vector<const char*> &a) {
     mergesort(&a[0], SS, sizeof(char*), cmpfunc_char);
}

template <class T>
void hsort_bsd(vector<T> &a) {
     heapsort(&a[0], SS, sizeof(T), cmpfunc<T>);
}

template <>
void hsort_bsd(vector<const char*> &a) {
     heapsort(&a[0], SS, sizeof(char*), cmpfunc_char);
}

template<class T>
void radix_bsd(vector<T> &a) {
    throw "not implementented";
}

template<>
void radix_bsd(vector<const char*> &a) {
    radixsort((const unsigned char**)&a[0], SS, 0, 0);   
}

template<class T>
void sradix_bsd(vector<T> &a) {
    throw "not implementented";
}

template<>
void sradix_bsd(vector<const char*> &a) {
    sradixsort((const unsigned char**)&a[0], SS, 0, 0);   
}

