template<class T> void _insertion_sort(T* l, T* r) {
    for (T *i = l + 1; i < r; i++) {
        T* j = i;
        while (j > l && *(j - 1) > *j) {
            swap(*(j - 1), *j);
            j--;
        }
    }
}

template<> void _insertion_sort(const char** l, const char** r) {
    for (const char **i = l + 1; i < r; i++) {
        const char** j = i;
        while (j > l && strcmp(*(j - 1), *j) > 0) {
            swap(*(j - 1), *j);
            j--;
        }
    }
}

template<class T> void insertion_sort(vector<T> &a) {
    _insertion_sort(&a[0], &a[0] + a.size());
}

