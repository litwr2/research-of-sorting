template<class T> void _insertion_sort(T* l, T* r) {
	for (T *i = l + 1; i < r; i++) {
		T* j = i;
		while (j > l && *(j - 1) > *j) {
			swap(*(j - 1), *j);
			j--;
		}
	}
}

template<class T> void insertion_sort(vector<T> &a) {
    _insertion_sort(&a[0], &a[0] + a.size());
}

