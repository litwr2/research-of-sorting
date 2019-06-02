#include "opt/timsort.hpp"   // https://github.com/gfx/cpp-TimSort - only the header is required

template <class T>
void timsort(vector<T> &a) {
   gfx::timsort(a.begin(), a.end(), std::less<T>());
}

template <>
void timsort(vector<const char*> &a) {
   gfx::timsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

