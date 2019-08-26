template<class T> struct MsdRadix {
    vector<T> temp;
    vector<T> &a;
    int N;
    int maxd;

    MsdRadix(vector<T> &a, int N) : a(a), N(N), temp(a.size()) {}

    void _radixsort_msd(T *l, T *r, int d) {
        if (r - l <= 32) {
            _insertion_sort(l, r);
            return;
        }
        int M = 1 << N;
        int cnt[M + 1] = {};
        int cur = 0;
        for (T* i = l; i < r; i++) {
            temp[cur++] = *i;
            cnt[(*i >> N*d & M - 1) + 1]++;
        }
        int sz = 0;
        for (int i = 1; i <= M; i++)
            if (cnt[i]) sz++;
        int run[sz];
        cur = 0;
        for (int i = 1; i <= M; i++)
            if (cnt[i]) run[cur++] = i - 1;
        for (int i = 1; i <= M; i++)
            cnt[i] += cnt[i - 1];
        cur = 0;
        for (T *i = l; i < r; i++) {
            int ind = temp[cur] >> N*d & M - 1;
            *(l + cnt[ind]) = temp[cur];
            cur++;
            cnt[ind]++;
        }
        for (int i = 0; i < sz; i++) {
            int r = run[i];
            if (d > 0)
                if (r != 0)
                    _radixsort_msd(l + cnt[r - 1], l + cnt[r], d - 1);
                else
                    _radixsort_msd(l, l + cnt[r], d - 1);
        }
    }

    void operator()() {
        int s = sizeof(T);
        if (s == sizeof(int)*5) s = sizeof(int); //for INT1P4 type
        int d = (s*8 + N - 1) / N - 1;
        _radixsort_msd(&a[0], &a[0] + a.size(), d);
    }
};

template<> MsdRadix<string>::MsdRadix(vector<string> &a, int N) : a(a), N(N), temp(a.size()) {
    if (N != 8) throw "radix-msd supports only N = 8 for strings";
    maxd = 0;
    for (int i = 0; i < a.size(); ++i)
        if (a[i].length() > maxd) maxd = a[i].length();
    maxd--;
}

template<> void MsdRadix<string>::_radixsort_msd(string *l, string *r, int d) {
    if (r - l <= 3) {
        _insertion_sort(l, r);
        return;
    }
    int M = 1 << N;
    vector<int> cnt(M + 1);
    int cur = 0;
    for (string* i = l; i < r; i++) {
        temp[cur++] = *i;
        cnt[(d < i->length() ? (unsigned char)(*i)[d] : 0) + 1]++;
    }
    int sz = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) sz++;
    vector<int> run(sz);
    cur = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) run[cur++] = i - 1;
    for (int i = 1; i <= M; i++)
        cnt[i] += cnt[i - 1];
    cur = 0;
    for (string *i = l; i < r; i++) {
        int ind = d < temp[cur].length() ? (unsigned char)temp[cur][d] : 0;
        *(l + cnt[ind]) = temp[cur];
        cur++;
        cnt[ind]++;
    }
    for (int i = 0; i < sz; i++) {
        int r = run[i];
        if (d < maxd)
            if (r != 0)
                _radixsort_msd(l + cnt[r - 1], l + cnt[r], d + 1);
            else
                _radixsort_msd(l, l + cnt[r], d + 1);
    }
}

template<> void MsdRadix<string>::operator()() {
    _radixsort_msd(&a[0], &a[0] + a.size(), 0);
}

template<> MsdRadix<const char*>::MsdRadix(vector<const char*> &a, int N) : a(a), N(N), temp(a.size()) {
    if (N != 8) throw "radix-msd supports only N = 8 for strings";
    maxd = 0;
    for (int i = 0; i < a.size(); ++i)
        if (strlen(a[i]) > maxd) maxd = strlen(a[i]);
    maxd--;
}

template<> void MsdRadix<const char*>::_radixsort_msd(const char **l, const char **r, int d) {
    if (r - l <= 32) {
        _insertion_sort(l, r);
        return;
    }
    int M = 1 << N;
    vector<int> cnt(M + 1);
    int cur = 0;
    for (const char** i = l; i < r; i++) {
        temp[cur++] = *i;
        cnt[(d < strlen(*i) ? (unsigned char)(*i)[d] : 0) + 1]++;
    }
    int sz = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) sz++;
    vector<int> run(sz);
    cur = 0;
    for (int i = 1; i <= M; i++)
        if (cnt[i]) run[cur++] = i - 1;
    for (int i = 1; i <= M; i++)
        cnt[i] += cnt[i - 1];
    cur = 0;
    for (const char **i = l; i < r; i++) {
        int ind = d < strlen(temp[cur]) ? (unsigned char)temp[cur][d] : 0;
        *(l + cnt[ind]) = temp[cur];
        cur++;
        cnt[ind]++;
    }
    for (int i = 0; i < sz; i++) {
        int r = run[i];
        if (d < maxd)
            if (r != 0)
                _radixsort_msd(l + cnt[r - 1], l + cnt[r], d + 1);
            else
                _radixsort_msd(l, l + cnt[r], d + 1);
    }
}

template<> void MsdRadix<const char*>::operator()() {
    _radixsort_msd(&a[0], &a[0] + a.size(), 0);

}

template<class T> void radix_msd(vector<T> &a, int N) {
    MsdRadix<T>(a, N)();
}

