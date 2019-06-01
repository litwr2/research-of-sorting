template<class T>
void selection_sort(vector<T> &a) {
    int max_i, min_i, i = 0;

    while (a.size() - 2*i > 1) {
        T max = a[max_i = a.size() - i - 1], min = a[min_i = i];
        for (int k = i; k < a.size() - i; k++) {
            if (max < a[k]) max = a[max_i = k];
            if (min > a[k]) min = a[min_i = k];
        }
        if (max_i != a.size() - i - 1) swap(a[a.size() - i - 1], a[max_i]);
        if (a.size() - i - 1 == min_i) min_i = max_i;
        if (min_i != i) swap(a[i], a[min_i]);
        ++i;
    }
}

template<>
void selection_sort(vector<const char*> &a) {
    int max_i, min_i, i = 0;

    while (a.size() - 2*i > 1) {
        const char *max = a[max_i = a.size() - i - 1], *min = a[min_i = i];
        for (int k = i; k < a.size() - i; k++) {
            if (strcmp(max, a[k]) < 0) max = a[max_i = k];
            if (strcmp(min, a[k]) > 0) min = a[min_i = k];
        }
        if (max_i != a.size() - i - 1) swap(a[a.size() - i - 1], a[max_i]);
        if (a.size() - i - 1 == min_i) min_i = max_i;
        if (min_i != i) swap(a[i], a[min_i]);
        ++i;
    }
}

