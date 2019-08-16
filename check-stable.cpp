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

#define PASSES 1
#define INT1P4

#define LOW_VARIATION2
#define LOW_VARIATION_CONST 2

#ifndef SS
#define SS 10'000 //limits due to int types of indice are slightly above 2'000'000'000
#endif

struct X {
    int k;
    int v[4];
    operator int() const { return k; }
};
int operator-(const X &a, const X &b) { return a.k - b.k; }

#include "oms7.cpp"
#include "insertion.cpp"
#include "baseop.cpp"
#include "fillings.cpp"
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

bool stable;

template<class T>
void check(vector<T>& v) {
    for (int i = 1; i < v.size(); ++i) {
        if (v[i - 1] > v[i]) exit(2);
        if (v[i - 1] == v[i] && v[i - 1].v[0] > v[i].v[0]) stable = false;
    }
}

template<class T>
size_t test(vector<T> &v, function<void(vector<T>&)> f, const char *title) {
    vector<T> vs(v);
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    stable = true;
    check(v);
    cout << setw(16) << left << title << setw(11) << right << te - ts << ' '
        << stable << endl;
    v = vs;
    return te - ts;
}

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v;

    fill(v);
    for (int i = 0; i < SS; ++i) v[i].v[0] = i;

    test<X>(v, bind(shell1<X>, placeholders::_1), "shell_a3n");
    test<X>(v, bind(shell3<X>, placeholders::_1), "shell_10/3");
    test<X>(v, bind(shell2<X>, placeholders::_1, 0), "shell_prime_e");
    test<X>(v, bind(shell2<X>, placeholders::_1, 1), "shell_a102549");
    test<X>(v, bind(shell2<X>, placeholders::_1, 2), "shell_exp_tab");
    test<X>(v, bind(shell2<X>, placeholders::_1, 4), "shell_prime_10/3");
    test<X>(v, bind(shell2<X>, placeholders::_1, 5), "shell_a102549m");
    test<X>(v, bind(shell2<X>, placeholders::_1, 6), "shell_2.25");

    test<X>(v, bind(radixsort<X>, placeholders::_1, 8), "radix8");
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 8), "radix8_msb");
    test<X>(v, bind(radixsort<X>, placeholders::_1, 11), "radix11");
    test<X>(v, bind(radixsort<X>, placeholders::_1, 16), "radix16");
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 11), "radix11_msb");
    test<X>(v, bind(radix_msb<X>, placeholders::_1, 16), "radix16_msb");
    test<X>(v, bind(Trie<X>::sort, placeholders::_1), "radix8_trie");
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
    test<X>(v, bind(qsort0<X>, placeholders::_1), "clib_qsort");
    test<X>(v, bind(hsort_bsd<X>, placeholders::_1), "heapsort_bsd");
    test<X>(v, bind(mergesort_bsd<X>, placeholders::_1), "mergesort_bsd");
    test<X>(v, bind(qsort1<X>, placeholders::_1, 0, SS - 1), "qsort_hoare");
    test<X>(v, bind(qsort1tc<X>, placeholders::_1, 0, SS - 1), "qsort_hoare_tco");
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

    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    return 0;
}

