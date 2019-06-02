template <class T>
void hsortstl(vector<T> &a) {
    make_heap(a.begin(), a.end());
    sort_heap(a.begin(), a.end());
}

template <>
void hsortstl(vector<const char*> &a) {
    make_heap(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
    sort_heap(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void stl_sort(vector<T> &a) {
    sort(a.begin(), a.end());
}

template <>
void stl_sort(vector<const char*> &a) {
    sort(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void stl_stable_sort(vector<T> &a) {
    stable_sort(a.begin(), a.end());
}

template <>
void stl_stable_sort(vector<const char*> &a) {
    stable_sort(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

