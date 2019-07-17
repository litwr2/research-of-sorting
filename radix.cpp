template<class T>
void radixsort(vector<T> &a, int N) {
	int s = sizeof(T);
    if (s == sizeof(int(a[0]))) s = 4; //for X type
    int k = (s*8 + N - 1) / N;
	int M = 1 << N;
	vector<T> b(a.size());
	for (int i = 0; i < k; i++) {
        int c[M] = {};
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

template<>
void radixsort(vector<string> &a, int N) { //N must be = 8
    int s = 0;
    for (int i = 0; i < a.size(); ++i)
        if (a[i].length() > s) s = a[i].length();
	int M = 1 << N;
	vector<string> b(a.size());
	for (int i = s - 1; i >= 0; --i) {
        int c[M] = {};
		for (int j = 0; j < a.size(); j++)
			c[i >= a[j].length() ? 0 :  (unsigned char)a[j][i]]++;
		for (int j = 1; j < M; j++)
			c[j] += c[j - 1];
		for (int j = a.size() - 1; j >= 0; j--)
			b[--c[i >= a[j].length() ? 0 : (unsigned char)a[j][i]]] = a[j];
		a = b;
	}
}

template<>
void radixsort(vector<const char*> &a, int N) { //N must be = 8
    int s = 0;
    for (int i = 0; i < a.size(); ++i)
        if (strlen(a[i]) > s) s = strlen(a[i]);
	int M = 1 << N;
	vector<char*> b(a.size());
	for (int i = s - 1; i >= 0; --i) {
        int c[M] = {};
		for (int j = 0; j < a.size(); j++)
			c[i >= strlen(a[j]) ? 0 : (unsigned char)a[j][i]]++;
		for (int j = 1; j < M; j++)
			c[j] += c[j - 1];
		for (int j = a.size() - 1; j >= 0; j--) {
            int d = i >= strlen(a[j]) ? 0 : (unsigned char)a[j][i];
            b[--c[d]] = new char [strlen(a[j]) + 1];
			strcpy(b[c[d]], a[j]);
        }
        for (int j = 0; j < a.size(); ++j) {
            delete [] a[j];
		    a[j] = b[j];
        }
	}
}

