#include <set>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <list>
#include <cstdlib>
#include <typeinfo>
#include <algorithm>
#include <chrono>
#include <string>
#include <functional>
#include <climits>
#include <limits>
#include <cstring>

using namespace std;

#ifndef PASSES
#define PASSES 1
#endif
//#define PLAININT
//#define INT1P4
//#define INT64
//#define INT128
//#define FLOAT
//#define STRINGS_SHORT
//#define STRINGS
//#define STRINGS_LONG
//#define CSTRINGS_SHORT
//#define CSTRINGS
//#define CSTRINGS_LONG

#ifndef SS
#define SS 8
#endif

#define RDTSC

#define LOW_VARIATION_CONST 0 //fake definition for the filling module
#define RANDOM  //fake definition for the filling module

#ifndef REPEATS
#define REPEATS 2
#endif

#if defined(PLAININT) + defined(STRINGS) + defined(CSTRINGS) + defined(CSTRINGS_SHORT) + defined(CSTRINGS_LONG) + defined(STRINGS_SHORT) + defined(STRINGS_LONG) + defined(INT64) + defined(FLOAT) + defined(INT128) + defined(INT1P4) > 1
#error AMBIGUOUS TYPE
#endif

#if defined(PLAININT) + defined(STRINGS) + defined(CSTRINGS_SHORT) + defined(CSTRINGS_LONG) + defined(STRINGS_SHORT) + defined(STRINGS_LONG) + defined(CSTRINGS) + defined(INT64) + defined(FLOAT) + defined(INT128) + defined(INT1P4) == 0
#define PLAININT
#endif

uint64_t rdtsc(){
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

#ifdef PLAININT
typedef int X;
#elif defined(STRINGS) || defined(STRINGS_SHORT) || defined(STRINGS_LONG)
typedef string X;
#elif defined(CSTRINGS) || defined(CSTRINGS_SHORT) || defined(CSTRINGS_LONG)
typedef const char *X;
#elif defined(INT64)
typedef int64_t X;
#elif defined(INT128)
typedef __int128 X;
#elif defined(FLOAT)
typedef double X;
#elif defined(INT1P4)
struct X {
    int k;
    int v[4];
    operator int() const { return k; }
};
//bool operator<(const X &a, const X &b) { return a.k < b.k; }
int operator-(const X &a, const X &b) { return a.k - b.k; }
#else
#error This type is not known
#endif

ostream& operator<<(ostream& os, const __int128 &v) {
    os << (size_t)(v >> 96) << ':' << (size_t)((v >> 64) & 0xffff'ffff)  << ':' << (size_t)((v >> 32) & 0xffff'ffff) << ':' << (size_t)(v & 0xffff'ffff);
    return os;
}

#include "oms7.cpp"
#include "baseop.cpp"
#include "fillings.cpp"
#include "insertion.cpp"
#include "tim.cpp"
#include "std.cpp"
#include "boost.cpp"
#include "bsd.cpp"
#include "radix.cpp"
#include "radix-msb.cpp"
#include "qsort.cpp"
#include "dp-quick.cpp"
#include "shell.cpp"
#include "tree.cpp"
#include "hash.cpp"
#include "hashtree.cpp"
#include "array.cpp"
#include "bubble.cpp"
#include "selection.cpp"

template<class T>
void dummy(vector<T>& v) {
    v[1] = v[0];
}

template<class T>
void check(vector<T>& v) {
    for (int i = 1; i < v.size(); ++i)
        if (v[i - 1] > v[i]) exit(2);
}

template<>
void check(vector<const char*>& v) {
    for (int i = 1; i < v.size(); ++i)
        if (strcmp(v[i - 1], v[i]) > 0) exit(2);
}

template<class T>
void test(vector<T> &v, function<void(vector<T>&)> f, const char *title) {
    int MXD = 32/(1 << (v.size() - 7));
    if (MXD == 0) ++MXD;
    size_t total = 0, counter = 0, maxda[MXD] = {}, maxd = 0, mind = numeric_limits<size_t>::max();
    auto vs = v, vx = v, maxv = v;
    double adjustment = 0;
    do {
        for (int cl = 0; cl < MXD; ++cl) {
            counter++;
#ifndef RDTSC
            auto ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#else
            auto ts = rdtsc();
#endif
            for (unsigned n = 0; n < 10; ++n)
                dummy(vx = vs);
#ifndef RDTSC
            adjustment += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts;
            ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
#else
            adjustment += rdtsc() - ts;
            ts = rdtsc();
#endif
            for (unsigned n = 0; n < REPEATS; ++n)
                //f(vx);
                f(v = vs);
#ifndef RDTSC
            auto d = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts;
#else
            auto d = rdtsc() - ts;
#endif
            total += d;
            if (d < mind) mind = d;
            if (d > maxda[cl]) maxda[cl] = d;
            check(v);
        }
        int z = maxda[0];
        for (int i = 1; i < MXD; ++i)
            if (z > maxda[i]) z = maxda[i];
        if (maxd < z) maxd = z, maxv = vs;
        maxda[0] = maxda[1] = 0;
    } while (next_permutation(vs.begin(), vs.end()));
    v = vs;
    if (title[0] != 'Z') {
        cout << setw(16) << left << title << right << setw(11) << fixed << setprecision(2) << ((long double)total/REPEATS - adjustment/10.)/counter << ' ' << double(mind)/REPEATS  - adjustment/10./counter << ' ' << double(maxd)/REPEATS - adjustment/10./counter << ' ' << adjustment/10./counter;
        for (int i = 0; i < SS - 1; ++i) cout << ' ' << maxv[i];
        cout << ' ' << maxv[SS - 1] << endl;
    }
}

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v(SS);
    for (int i = 0; i < SS; ++i) v[i] = cnv<X>(i);
    double adjustment_sum = 0;
    for (int i = 0; i < 10; ++i)
        test<X>(v, bind(shell3<X>, placeholders::_1), "Z");

    int passes = PASSES;
L:
    test<X>(v, bind(shell1<X>, placeholders::_1), "shell_a3n");
    test<X>(v, bind(shell3<X>, placeholders::_1), "shell_10/3");
    test<X>(v, bind(shell2<X>, placeholders::_1, 0), "shell_prime_e");
    test<X>(v, bind(shell2<X>, placeholders::_1, 1), "shell_a102549");
    test<X>(v, bind(shell2<X>, placeholders::_1, 2), "shell_exp_tab");
    test<X>(v, bind(shell2<X>, placeholders::_1, 4), "shell_prime_10/3");

#if !defined(FLOAT)
    test<X>(v, bind(radixsort<X>, placeholders::_1, 8), "radix8");
    test<X>(v, bind(radixsort<X>, placeholders::_1, 11), "radix11");
    test<X>(v, bind(radixsort<X>, placeholders::_1, 16), "radix16");
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 8), "radix8_msb");
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG) && !defined(CSTRINGS) && !defined(CSTRINGS_SHORT) && !defined(CSTRINGS_LONG)
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 11), "radix11_msb");
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 16), "radix16_msb");
#endif
#endif
#ifdef PLAININT
    test<X>(v, bind(oms7_helper<X>, placeholders::_1, 5), "shell_10/3_oms7");
    test<X>(v, bind(oms7_helper<X>, placeholders::_1, 7), "radix8_oms7");
    test<X>(v, bind(oms7_helper<X>, placeholders::_1, 8), "radix8_msb_oms7");
#endif
    test<X>(v, bind(hsortstl<X>, placeholders::_1), "heapsort_stl");
#if defined(CSTRINGS) || defined(CSTRINGS_SHORT) || defined(CSTRINGS_LONG)
    test<X>(v, bind(radix_bsd<X>, placeholders::_1), "radix_bsd");
    test<X>(v, bind(sradix_bsd<X>, placeholders::_1), "sradix_bsd");
#endif
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    test<X>(v, bind(qsort0<X>, placeholders::_1), "clib_qsort");
    test<X>(v, bind(hsort_bsd<X>, placeholders::_1), "heapsort_bsd");
    test<X>(v, bind(mergesort_bsd<X>, placeholders::_1), "mergesort_bsd");
#endif
    test<X>(v, bind(qsort1<X>, placeholders::_1, 0, SS - 1), "qsort_hoare");
    //test<X>(v, bind(qsort1tc<X>, placeholders::_1, 0, SS - 1), "qsort_hoare_tco"); //not tested with all data types 
    test<X>(v, bind(qsort2<X>, placeholders::_1, 0, SS - 1), "qsort_no_pivot");
    test<X>(v, bind(qsort3<X>, placeholders::_1, 0, SS - 1), "qsort_hoare2");
    test<X>(v, bind(qsort4<X>, placeholders::_1, 0, SS - 1), "qsort_lomuto");
    test<X>(v, bind(dualPivotQuicksort<X>, placeholders::_1), "qsort_dualpivot");
    test<X>(v, bind(stl_sort<X>, placeholders::_1), "stlsort");
    test<X>(v, bind(stl_stable_sort<X>, placeholders::_1), "stlstable");

    test<X>(v, bind(timsort<X>, placeholders::_1), "timsort");

    test<X>(v, bind(spreadsort<X>, placeholders::_1), "spread");
    test<X>(v, bind(pdqsort<X>, placeholders::_1), "pdq");
    test<X>(v, bind(spinsort<X>, placeholders::_1), "spin");
    test<X>(v, bind(flat_stable_sort<X>, placeholders::_1), "flat_stable");

    test<X>(v, bind(bubble_sort<X>, placeholders::_1), "bubble");
    test<X>(v, bind(selection_sort<X>, placeholders::_1), "selection");
    test<X>(v, bind(insertion_sort<X>, placeholders::_1), "insertion");

    test<X>(v, bind(tree_sort_stl<X>, placeholders::_1), "tree_stl");
    test<X>(v, bind(tree_sort_boost<X>, placeholders::_1), "tree_boost");

    test<X>(v, bind(array_sort<X>, placeholders::_1, 1), "array*1");
    test<X>(v, bind(array_sort<X>, placeholders::_1, 2), "array*2");
    test<X>(v, bind(array_sort<X>, placeholders::_1, 3), "array*3");
    test<X>(v, bind(array_sort<X>, placeholders::_1, 5), "array*5");
    test<X>(v, bind(array_sort<X>, placeholders::_1, 7), "array*7");

    test<X>(v, bind(hash_sort<X>, placeholders::_1), "hash");
    test<X>(v, bind(hashbt_sort_std<X>, placeholders::_1), "hashbt_std");
    test<X>(v, bind(hashbt_sort2<X>, placeholders::_1), "hashbt");
    test<X>(v, bind(hashbt_sort_boost<X>, placeholders::_1), "hashbt_boost");

    if (--passes) goto L;

    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    //for (int i = 0; i < SS; ++i) cout << v[i] << '\n';
    return 0;
}

