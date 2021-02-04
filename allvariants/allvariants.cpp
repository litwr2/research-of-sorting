#include <iostream>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <chrono>
using namespace std;
#ifndef N
#define N 4
#endif
#ifndef P
#define P 400
#endif
//#define PERMUTATION_ONLY

int ops, csp, msp, cnt;

inline uint64_t rdtsc(){
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

void qsort_hoare10(int *a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    int x = a[(i + j)/2];
    do {
        while (a[i] < x) ++i;
        while (x < a[j]) --j;
        if (i <= j) {
            if (i != j) swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    while (i <= j);
    if (LBound < j) qsort_hoare10(a, LBound, j);
    if (i < UBound) qsort_hoare10(a, i, UBound);
}

void qsort_hoare1(int *a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    int x = a[(i + j)/2];
    cnt++;
    csp++;
    if (csp > msp) msp = csp;
    ops += 6;
    do {
        while (a[i] < x) ++i, ops += 3;
        while (x < a[j]) --j, ops += 3;
        ops += 5;
        if (i <= j) {
            if (i != j) ops += 3, swap(a[i], a[j]);
            ++i;
            --j;
            ops += 3;
        }
        ++ops;
    }
    while (i <= j);
    if (LBound < j) ops += 5, qsort_hoare1(a, LBound, j);
    ++ops;
    if (i < UBound) ops += 5, qsort_hoare1(a, i, UBound);
    ++ops;
    csp--;
}
int main() {
#ifdef PERMUTATION_ONLY
    uint64_t tim;
    int a0[N], a[N], ac[P][N];
    for (int i = 0; i < N; i++)
        a0[i] = i;
    do {
        for (int i = 0; i < N; i++) {
            a[i] = a0[i];
#else
    uint64_t max = 1, tim;
    int a[N], ac[P][N];
    for (int i = 0; i < N; i++)
        max *= N;
    for (int i = 0; i < max; i++) {
        int cv = i;
        for (int i = 0; i < N; i++) {
            a[i] = cv%N, cv /= N;
#endif
            for (int k = 0; k < P; k++)
                ac[k][i] = a[i];
        }
        //cout << i << ' ';
        for (int i = 0; i < N; i++)
            cout << a[i] << ' ';
        ops = 5, cnt = csp = msp = 0;
        qsort_hoare1(a, 0, N - 1);
#if 0
        uint64_t ti = rdtsc();
        for (int i = 0; i < P; ++i)
            qsort_hoare10(ac[i], 0, N - 1);
        tim = rdtsc() - ti;
        tim = tim/P + (tim%P >= tim/2);
#else
        tim = numeric_limits<uint64_t>::max();;
        for (int i = 0; i < P; ++i) {
            //auto ti = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            uint64_t ti = rdtsc();
            qsort_hoare10(ac[i], 0, N - 1);
            //ti = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - ti;
            ti = rdtsc() - ti;
            if (ti < tim) tim = ti;
        }
#endif
        cout << ops << ' ' << msp << ' ' << cnt << ' ' << tim << endl;
    }
#ifdef PERMUTATION_ONLY
    while (next_permutation(a0, a0 + N));
#endif
    return 0;
}

