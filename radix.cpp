template<class T>
void radixsort(vector<T> &a, int N) {
	int s = sizeof(T);
    if (s == sizeof(int(a[0]))) s = 4; //for X type
    int k = (s*8 + N - 1) / N;
	int M = 1 << N;
	vector<T> b(a.size());
	for (int i = 0; i < k; i++) {
                int c[M] = {0};
		for (int j = 0; j < a.size(); j++)
			c[a[j] >> N*i & M - 1]++;
		for (int j = 1; j < M; j++)
			c[j] += c[j - 1];
		for (int j = a.size() - 1; j >= 0; j--)
			b[--c[a[j] >> N*i & M - 1]] = a[j];
		a = b;
        //if (i + 2 == k) M = 1 << N + s*8 - k*N;
	}
}

