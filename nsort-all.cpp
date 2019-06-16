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

#define SS 12
#define RDTSC

uint64_t rdtsc(){
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

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
bool operator<(const X &a, const X &b) { return a.k < b.k; }
int operator-(const X &a, const X &b) { return a.k - b.k; }
#else
#error This type is not known
#endif

template<class T>
void insert2(vector<T> &v, list<T> &l, int final = 0) {
	v.push_back(v.back() + 1);
	l.push_back(l.front());
	l.erase(l.begin());
	if (!final)
		l.push_back(v.back()++);
}

template<class T>
void fill_for_quadratic_qsort1(vector<T> &v, int size) {
	v = {1, 3};
	list<T> l{2, 0};
	for (int i = 0; i < (size - 4)/2; i++)
		insert2(v, l);
	if (SS%2)
		insert2(v, l, 1);
	v.insert(v.end(), l.begin(), l.end());     
}

#include "oms7.cpp"
#include "baseop.cpp"
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

int main() {
    //cerr << sizeof(X) << endl;
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v, vs;

    for (int i = 0; i < SS; ++i) v.push_back(i);
    uint64_t counter = 0, timer_sum = 0;
    do {
        counter++;
        vs = v;
#ifdef RDTSC
	auto ts = rdtsc();
#else
        auto ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#endif
        //qsort0(vs);
        //qsort2(vs, 0, SS - 1);
        //shell2(vs, 1);
        sort(vs.begin(), vs.end());
        //stable_sort(vs.begin(), vs.end());
        //gfx::timsort(vs.begin(), vs.end(), std::less<X>());
        //heapsort(&vs[0], SS, sizeof(X), cmpfunc<X>);
        //hsortstl(vs);
        //tree_sort(vs);
        //hash_sort(vs);
        //array_sort(vs);
        //boost::sort::spreadsort::integer_sort(&vs[0], &vs[0] + SS);
        //boost::sort::pdqsort(&vs[0], &vs[0] + SS);
        //boost::sort::spinsort(&vs[0], &vs[0] + SS);
        //boost::sort::flat_stable_sort(&vs[0], &vs[0] + SS);
        //bubble_sort<X>(vs);
        //selection_sort<X>(vs);
#ifdef RDTSC
	auto te = rdtsc();
#else
        auto te = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#endif
        check(vs);
        timer_sum += te - ts;
    }
    while (next_permutation(v.begin(), v.end()));
    cout << double(timer_sum)/counter << endl;

    cerr << "zok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    //for (int i = 0; i < SS; ++i) cout << v[i] << '\n';
    return 0;
}

