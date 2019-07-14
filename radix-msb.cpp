#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <algorithm>  //swap
using namespace std;

template<class T> //dublicate, see radix
inline int digit(T n, int k, int N, int M) {
	return n >> N*k & M - 1;
}

template<class T> void insertionsort(T* l, T* r) { //make alone!
	for (T *i = l + 1; i < r; i++) {
		T* j = i;
		while (j > l && *(j - 1) > *j) {
			swap(*(j - 1), *j);
			j--;
		}
	}
}

template<class T> void _radixsortmsd(T *l, T *r, int N, int d, vector<T> &temp) {
	if (d == -1) return;
	if (r - l <= 32) {
		insertionsort(l, r);
		return;
	}
	int M = 1 << N;
	int cnt[M + 1] = {};
	int cur = 0;
	for (T* i = l; i < r; i++) {
		temp[cur++] = *i;
		cnt[digit(*i, d, N, M) + 1]++;
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
		int ind = digit(temp[cur], d, N, M);
		*(l + cnt[ind]) = temp[cur];
		cur++;
		cnt[ind]++;
	}
	for (int i = 0; i < sz; i++) {
		int r = run[i];
		if (r != 0) _radixsortmsd(l + cnt[r - 1], l + cnt[r], N, d - 1, temp);
		else _radixsortmsd(l, l + cnt[r], N, d - 1, temp);
	}
}

template<class T> void radixsortmsd(vector<T> &a, int N, int d) {
    vector<T> temp(a);
	_radixsortmsd(&a[0], &a[a.size() - 1] + 1, N, d, temp);
}

int main() {
    const int sz = 100;
    vector<int> a;
    for (int i = 0; i < sz; ++i) a.push_back(rand()%1000);
//    for (int i = 0; i < sz; ++i) cout << a[i] << ' '; cout << endl;
    radixsortmsd(a, 8, 3);
//    for (int i = 0; i < sz; ++i) cout << a[i] << ' '; cout << endl;
    for (int i = 1; i < sz; ++i) if (a[i - 1] > a[i]) cout << "ERROR" << endl;
    return 0;
}

