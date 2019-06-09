#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/sort.hpp>
#include <boost/container/set.hpp>

template <class T>
void spreadsort(vector<T> &a) {
    //boost::sort::spreadsort::spreadsort(&a[0], &a[0] + SS);
    boost::sort::spreadsort::integer_sort(&a[0], &a[0] + SS);
}

template <>
void spreadsort(vector<double> &a) {
    boost::sort::spreadsort::spreadsort(&a[0], &a[0] + SS);
}

template <>
void spreadsort(vector<string> &a) {
    boost::sort::spreadsort::string_sort(&a[0], &a[0] + SS);
}

template <>
void spreadsort(vector<int> &a) {
    boost::sort::spreadsort::integer_sort(&a[0], &a[0] + SS);
}

struct bracket {
    inline unsigned char operator()(const char* x, size_t offset) const {
      return x[offset];
    }
};

struct getsize {
    inline size_t operator()(const char *x) const { return strlen(x); }
};

template <>
void spreadsort(vector<const char*> &a) {
    boost::sort::spreadsort::string_sort(&a[0], &a[0] + SS, bracket(), getsize());
}

template <class T>
void pdqsort(vector<T> &a) {
    boost::sort::pdqsort(&a[0], &a[0] + SS);
}

template <>
void pdqsort(vector<const char*> &a) {
    boost::sort::pdqsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void spinsort(vector<T> &a) {
    boost::sort::spinsort(&a[0], &a[0] + SS);
}

template <>
void spinsort(vector<const char*> &a) {
    boost::sort::spinsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void flat_stable_sort(vector<T> &a) {
    boost::sort::flat_stable_sort(&a[0], &a[0] + SS);
}

template <>
void flat_stable_sort(vector<const char*> &a) {
    boost::sort::flat_stable_sort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

