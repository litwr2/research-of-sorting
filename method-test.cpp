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

#ifndef SS
#define SS 10'000 //limits due to int types of indice are slightly above 2'000'000'000
#endif

#define RANDOM
#define LOW_VARIATION_CONST 0
#define CSTRINGS

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
#include "insertion.cpp"
#include "baseop.cpp"
#include "fillings.cpp"
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

int main() {
    vector<X> a;
    fill(a);
///    for (int i = 0; i < SS; ++i) a.push_back(uint64_t(rand())*rand());
//    for (int i = 0; i < SS; ++i) cout << a[i] << ' '; cout << endl;
//    radixsortmsd(a, 4);
//    insertion_sort(a);
     radixsort(a, 8);
    //MsbRadix<X>(a, 16)();
//    radix_msb(a, 8);
//    dualPivotQuicksort(a);
//    for (int i = 0; i < SS; ++i) cout << a[i] << '\n'; cout << endl;
#if defined(CSTRINGS) || defined(CSTRINGS_LONG) || defined(CSTRINGS_SHORT)
    for (int i = 1; i < SS; ++i) if (strcmp(a[i - 1], a[i]) > 0) {cout << "ERROR" << endl; break;}
#else
    for (int i = 1; i < SS; ++i) if (a[i - 1] > a[i]) {cout << "ERROR" << endl; break;}
#endif
    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    return 0;
}

