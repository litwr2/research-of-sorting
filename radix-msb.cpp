template<class T> void _radixsortmsd(T *l, T *r, int N, int d, vector<T> &temp) {
	if (d == -1) return;
	if (r - l <= 32) {
		_insertionsort(l, r);
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
		if (r != 0)
            _radixsortmsd(l + cnt[r - 1], l + cnt[r], N, d - 1, temp);
		else
            _radixsortmsd(l, l + cnt[r], N, d - 1, temp);
	}
}

template<class T> void radixsortmsd(vector<T> &a, int N) {
    vector<T> temp(a);
    int s = sizeof(T);
    if (s == sizeof(int(a[0]))) s = 4; //for X type
    int d = (s*8 + N - 1) / N - 1;
	_radixsortmsd(&a[0], &a[0] + a.size(), N, d, temp);
}

