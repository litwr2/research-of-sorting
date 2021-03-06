template<class T>
void bubble_sort(vector<T> &a) {
    bool epf;
    int UBound = a.size() - 1;
    do {
        epf = false;
        for (int i = 0; i < UBound; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                epf = true;
            }
        --UBound;
    }
    while (epf);
}

template<>
void bubble_sort(vector<const char*> &a) {
    bool epf;
    int UBound = a.size() - 1;
    do {
        epf = false;
        for (int i = 0; i < UBound; ++i)
            if (strcmp(a[i], a[i + 1]) > 0) {
                swap(a[i], a[i + 1]);
                epf = true;
            }
        --UBound;
    }
    while (epf);
}

