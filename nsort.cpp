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
//#define RANDOM_ORDER
//#define ASCENDED_ORDER
//#define ASCENDED_RANDOM_ORDER
//#define DESCENDED_ORDER
//#define LOW_VARIATION_ORDER
//#define SLOW_QSORT1_ORDER

#ifndef LOW_VARIATION_CONST
#define LOW_VARIATION_CONST 100
#endif

#ifndef SS
#define SS 10'000 //limits due to int types of indice are slightly above 2'000'000'000
#endif

#if defined(RANDOM_ORDER) + defined(ASCENDED_ORDER) + defined(ASCENDED_RANDOM_ORDER) + defined(DESCENDED_ORDER) + defined(LOW_VARIATION_ORDER) + defined(SLOW_QSORT1_ORDER) > 1
#error AMBIGUOUS ORDER
#endif

#if defined(RANDOM_ORDER) + defined(ASCENDED_ORDER) + defined(ASCENDED_RANDOM_ORDER) + defined(DESCENDED_ORDER) + defined(LOW_VARIATION_ORDER) + defined(SLOW_QSORT1_ORDER) == 0
#define RANDOM_ORDER
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
#include "tim.cpp"
#include "std.cpp"
#include "boost.cpp"
#include "bsd.cpp"
#include "radix.cpp"
#include "qsort.cpp"
#include "shell.cpp"
#include "tree.cpp"
#include "hash.cpp"
#include "hashtree.cpp"
#include "array.cpp"
#include "bubble.cpp"
#include "selection.cpp"

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
    cout << setw(16) << left << title << setw(11) << right << te - ts
        << endl;
L:
    fio.seekg(0);
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(T));
#else
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
    cout << setw(16) << left << title << setw(11) << right << te - ts
        << endl;
L:
    fio.seekg(0);
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(char*));
    return te - ts;
}

int main() {
    //cerr << sizeof(X) << endl;
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v;
    fstream fio(FN, fio.binary | fio.trunc | fio.in | fio.out);

    fill(v);

#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    fio.write(reinterpret_cast<char*>(&v[0]), SS*sizeof(X));
#else
    for (int i = 0; i < SS; ++i) fio << v[i] << endl;
#endif

    size_t eps, itv, tv = test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell3<X>, placeholders::_1)), "Z"); //train gc & cache, it is just a delay
    do {
        itv = test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell3<X>, placeholders::_1)), "Z");
        eps = abs(int((double(itv)/tv - 1)*100));
        tv = itv;
    } while (eps > 2);

    int passes = PASSES;
L:
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell1<X>, placeholders::_1)), "shell_a3n");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell3<X>, placeholders::_1)), "shell_10/3");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 0)), "shell_prime_e");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 1)), "shell_a102549");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 2)), "shell_exp_tab");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 4)), "shell_prime_10/3");

#if !defined(STRINGS) && !defined(CSTRINGS) && !defined(STRINGS_SHORT) && !defined(CSTRINGS_SHORT) && !defined(STRINGS_LONG) && !defined(CSTRINGS_LONG) && !defined(FLOAT)
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radixsort<X>, placeholders::_1, 8)), "radix8");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radixsort<X>, placeholders::_1, 11)), "radix11");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radixsort<X>, placeholders::_1, 16)), "radix16");
#endif
#ifdef PLAININT
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 5)), "shell_10/3_oms7");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 7)), "radix8_oms7");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 8)), "msd8_oms7");
#endif
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hsortstl<X>, placeholders::_1)), "heapsort_stl");
#if defined(CSTRINGS) || defined(CSTRINGS_SHORT) || defined(CSTRINGS_LONG)
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radix_bsd<X>, placeholders::_1)), "radix_bsd");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(sradix_bsd<X>, placeholders::_1)), "sradix_bsd");
#endif
#if !defined(STRINGS) && !defined(STRINGS_SHORT) && !defined(STRINGS_LONG)
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort0<X>, placeholders::_1)), "clib_qsort");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hsort_bsd<X>, placeholders::_1)), "heapsort_bsd");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(mergesort_bsd<X>, placeholders::_1)), "mergesort_bsd");
#endif
 //   test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort1<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare");
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort1tc<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare_tco"); //not tested with all data types 
 //   test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort2<X>, placeholders::_1, 0, SS - 1)), "qsort_no_pivot");
 //   test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort3<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare2");
 //   test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort4<X>, placeholders::_1, 0, SS - 1)), "qsort_lomuto");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(stl_sort<X>, placeholders::_1)), "stlsort");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(stl_stable_sort<X>, placeholders::_1)), "stlstable");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(timsort<X>, placeholders::_1)), "timsort");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(spreadsort<X>, placeholders::_1)), "spread");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(pdqsort<X>, placeholders::_1)), "pdq");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(spinsort<X>, placeholders::_1)), "spin");
 //   test(fio, v, static_cast<function<void(vector<X>&)>>(bind(flat_stable_sort<X>, placeholders::_1)), "flat_stable");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(bubble_sort<X>, placeholders::_1)), "bubble");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(selection_sort<X>, placeholders::_1)), "selection");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_stl<X>, placeholders::_1)), "tree_stl");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_boost<X>, placeholders::_1)), "tree_boost");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 1)), "array*1");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 2)), "array*2");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 3)), "array*3");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 5)), "array*5");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 7)), "array*7");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hash_sort<X>, placeholders::_1)), "hash");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort_std<X>, placeholders::_1)), "hashbt_std");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort2<X>, placeholders::_1)), "hashbt");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort_boost<X>, placeholders::_1)), "hashbt_boost");

    if (--passes) goto L;
    fio.close();
    remove(FN);

    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    //for (int i = 0; i < SS; ++i) cout << v[i] << '\n';
    return 0;
}

