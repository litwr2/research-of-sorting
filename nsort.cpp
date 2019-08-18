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
#include <limits>
#include <cstring>

using namespace std;

#ifndef FN
#define FN "tempd"
#endif
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
//#define RANDOM
//#define ORDERED
//#define PARTIALLY_ORDERED
//#define PARTIALLY_REVERSED
//#define REVERSED
//#define LOW_VARIATION1
//#define LOW_VARIATION2
//#define LOW_VARIATION100
//#define SLOW_QSORT_HOARE

#ifdef LOW_VARIATION1
#define LOW_VARIATION_CONST 1
#elif defined(LOW_VARIATION2)
#define LOW_VARIATION_CONST 2
#elif defined(LOW_VARIATION100)
#define LOW_VARIATION_CONST 100
#else
#define LOW_VARIATION_CONST 0
#endif

#ifndef SS
#define SS 10'000 //limits due to int types of indice are slightly above 2'000'000'000
#endif

#if defined(RANDOM) + defined(ORDERED) + defined(PARTIALLY_ORDERED) + defined(PARTIALLY_REVERSED)+ defined(REVERSED) + defined(LOW_VARIATION1) + defined(LOW_VARIATION2) + defined(LOW_VARIATION100) + defined(SLOW_QSORT_HOARE) > 1
#error AMBIGUOUS ORDER
#endif

#if defined(RANDOM) + defined(ORDERED) + defined(PARTIALLY_ORDERED) + defined(PARTIALLY_REVERSED)+ defined(REVERSED) + defined(LOW_VARIATION1) + defined(LOW_VARIATION2) + defined(LOW_VARIATION100) + defined(SLOW_QSORT_HOARE) == 0
#define RANDOM
#endif

#if defined(PLAININT) + defined(STRINGS) + defined(CSTRINGS) + defined(CSTRINGS_SHORT) + defined(CSTRINGS_LONG) + defined(STRINGS_SHORT) + defined(STRINGS_LONG) + defined(INT64) + defined(FLOAT) + defined(INT128) + defined(INT1P4) > 1
#error AMBIGUOUS TYPE
#endif

#if defined(PLAININT) + defined(STRINGS) + defined(CSTRINGS_SHORT) + defined(CSTRINGS_LONG) + defined(STRINGS_SHORT) + defined(STRINGS_LONG) + defined(CSTRINGS) + defined(INT64) + defined(FLOAT) + defined(INT128) + defined(INT1P4) == 0
#define PLAININT
#endif

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
#include "quick-np.cpp"
#include "quick-hoare.cpp"
#include "quick-lomuto.cpp"
#include "quick-dp.cpp"
#include "shell.cpp"
#include "tree.cpp"
#include "hash.cpp"
#include "hashtree.cpp"
#include "array.cpp"
#include "bubble.cpp"
#include "selection.cpp"
#include "trie.cpp"

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
size_t test(fstream &fio, vector<T> &v, function<void(vector<T>&)> f, const char *title) {
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    check(v);
    if (title[0] == 'Z') goto L;
    cout << setw(16) << left << title << setw(14) << right << te - ts << endl;
L:
    fio.seekg(0);
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(T));
#else
    for (int i = 0; i < SS; ++i) v[i].clear();
    for (int i = 0; i < SS; ++i) getline(fio, v[i]);
#endif
    return te - ts;
}

template<>
size_t test(fstream &fio, vector<const char*> &v, function<void(vector<const char*>&)> f, const char *title) {
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    check(v);
    if (title[0] == 'Z') goto L;
    cout << setw(16) << left << title << setw(14) << right << te - ts << endl;
L:
    fio.seekg(0);
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(char*));
    return te - ts;
}

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v;
    fstream fio(FN, fio.binary | fio.trunc | fio.in | fio.out);
    fill(v);
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    fio.write(reinterpret_cast<char*>(&v[0]), SS*sizeof(X));
#else
    for (int i = 0; i < SS; ++i) fio << v[i] << endl;
#endif
#if 1
    auto tp = chrono::steady_clock::now() + chrono::seconds(10);
    size_t eps, itv, tv = test<X>(fio, v, bind(shell3<X>, placeholders::_1), "Z"); //train gc & cache, it is just a delay
    do {
        itv = test<X>(fio, v, bind(shell3<X>, placeholders::_1), "Z");
        eps = int(double(abs(itv - tv))/tv*100);
        tv = itv;
    } while (eps > 10 && chrono::steady_clock::now() < tp);
#endif
    int passes = PASSES;
L:
    test<X>(fio, v, bind(shell1<X>, placeholders::_1), "shell_a3n");
    test<X>(fio, v, bind(shell3<X>, placeholders::_1), "shell_10/3");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 0), "shell_prime_e");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 1), "shell_a102549");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 2), "shell_exp_tab");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 4), "shell_prime_10/3");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 5), "shell_a102549m");
    test<X>(fio, v, bind(shell2<X>, placeholders::_1, 6), "shell_2.25");

    test<X>(fio, v, bind(selection_sort<X>, placeholders::_1), "selection");
    test<X>(fio, v, bind(insertion_sort<X>, placeholders::_1), "insertion");
    test<X>(fio, v, bind(bubble_sort<X>, placeholders::_1), "bubble");

#if !defined(FLOAT)
    test<X>(fio, v, bind(radixsort<X>, placeholders::_1, 8), "radix8");
    test<X>(fio, v, bind(radix_msb<X>, placeholders::_1, 8), "radix8_msb");
    test<X>(fio, v, bind((Trie<X>::sort), placeholders::_1), "radix8_trie");
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG) && !defined(CSTRINGS) && !defined(CSTRINGS_SHORT) && !defined(CSTRINGS_LONG)
    test<X>(fio, v, bind(radixsort<X>, placeholders::_1, 11), "radix11");
    test<X>(fio, v, bind(radixsort<X>, placeholders::_1, 16), "radix16");
    test<X>(fio, v, bind(radix_msb<X>, placeholders::_1, 11), "radix11_msb");
    test<X>(fio, v, bind(radix_msb<X>, placeholders::_1, 16), "radix16_msb");
#endif
#endif
#ifdef PLAININT
    test<X>(fio, v, bind(oms7_helper<X>, placeholders::_1, 5), "shell_10/3_oms7");
    test<X>(fio, v, bind(oms7_helper<X>, placeholders::_1, 7), "radix8_oms7");
    test<X>(fio, v, bind(oms7_helper<X>, placeholders::_1, 8), "radix8_msb_oms7");
#endif
    test<X>(fio, v, bind(hsortstl<X>, placeholders::_1), "heapsort_stl");
#if defined(CSTRINGS) || defined(CSTRINGS_SHORT) || defined(CSTRINGS_LONG)
    test<X>(fio, v, bind(radix_bsd<X>, placeholders::_1), "radix_bsd");
    test<X>(fio, v, bind(sradix_bsd<X>, placeholders::_1), "sradix_bsd");
#endif
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    test<X>(fio, v, bind(qsort0<X>, placeholders::_1), "clib_qsort");
    test<X>(fio, v, bind(hsort_bsd<X>, placeholders::_1), "heapsort_bsd");
    test<X>(fio, v, bind(mergesort_bsd<X>, placeholders::_1), "mergesort_bsd");
#endif
    test<X>(fio, v, bind(qsort1<X>, placeholders::_1, 0, SS - 1), "qsort_hoare");
    test<X>(fio, v, bind(qsort1tc<X>, placeholders::_1, 0, SS - 1), "qsort_hoare_tco");
    test<X>(fio, v, bind(qsort2<X>, placeholders::_1, 0, SS - 1), "qsort_no_pivot");
    test<X>(fio, v, bind(qsort3<X>, placeholders::_1, 0, SS - 1), "qsort_hoare2");
    test<X>(fio, v, bind(qsort4<X>, placeholders::_1, 0, SS - 1), "qsort_lomuto");
    test<X>(fio, v, bind(dualPivotQuicksort<X>, placeholders::_1), "qsort_dualpivot");
    test<X>(fio, v, bind(stl_sort<X>, placeholders::_1), "stlsort");
    test<X>(fio, v, bind(stl_stable_sort<X>, placeholders::_1), "stlstable");

    test<X>(fio, v, bind(timsort<X>, placeholders::_1), "timsort");

    test<X>(fio, v, bind(spreadsort<X>, placeholders::_1), "spread");
    test<X>(fio, v, bind(pdqsort<X>, placeholders::_1), "pdq");
    test<X>(fio, v, bind(flat_stable_sort<X>, placeholders::_1), "flat_stable");
    test<X>(fio, v, bind(spinsort<X>, placeholders::_1), "spin");

    test<X>(fio, v, bind(array_sort<X>, placeholders::_1, 1), "array*1");
    test<X>(fio, v, bind(array_sort<X>, placeholders::_1, 2), "array*2");
    test<X>(fio, v, bind(array_sort<X>, placeholders::_1, 3), "array*3");
    test<X>(fio, v, bind(array_sort<X>, placeholders::_1, 5), "array*5");
    test<X>(fio, v, bind(array_sort<X>, placeholders::_1, 7), "array*7");

    test<X>(fio, v, bind(hash_sort<X>, placeholders::_1), "hash");
    test<X>(fio, v, bind(hashbt_sort2<X>, placeholders::_1), "hashbt");

    test<X>(fio, v, bind(tree_sort_boost<X>, placeholders::_1), "tree_boost");
    test<X>(fio, v, bind(tree_sort_stl<X>, placeholders::_1), "tree_stl");

    test<X>(fio, v, bind(hashbt_sort_std<X>, placeholders::_1), "hashbt_std");
    test<X>(fio, v, bind(hashbt_sort_boost<X>, placeholders::_1), "hashbt_boost");

    if (--passes) goto L;
    fio.close();
    remove(FN);

    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    //for (int i = 0; i < SS; ++i) cout << v[i] << '\n';
    return 0;
}

