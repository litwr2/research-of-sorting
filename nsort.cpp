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

#define FN "tempd"
//#define PLAININT
//#define STRINGS
#define CSTRINGS
//#define COUNTERS
//#define ALL_VARIANTS  //SS must be less than 14 (14 means a many hours calculation)
#define RANDOM_ORDER
//#define ASCENDED_ORDER
//#define ASCENDED_RANDOM_ORDER
//#define DESCENDED_ORDER
//#define LOW_VARIATION_ORDER
#define LOW_VARIATION_CONST 100
//#define SLOW_QSORT1_ORDER

#ifndef ALL_VARIANTS
#define SS 100'000 //limits due to int types of indice are slightly above 2'000'000'000
#else
#define SS 12
#define RDTSC
#endif

uint64_t rdtsc(){
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

uint64_t comp_cnt, exch_cnt, comp_sum, exch_sum, total_sum, comp_max, total_max, comp_min = INT_MAX,
    exch_max, exch_min = INT_MAX, total_min = INT_MAX, total_min_comp, total_max_comp, total_min_exch,
    total_max_exch, counter, timer_sum;

#if defined(PLAININT) + defined(STRINGS) + defined(CSTRINGS) > 1
#error AMBIGUOUS TYPE
#endif

#ifdef PLAININT
typedef int X;
#elif defined(STRINGS)
typedef string X;
#elif defined(CSTRINGS)
typedef const char *X;
#else
struct X {
    int k;
    int v[4];
    operator int() { return k; }
};
bool operator<(const X &a, const X &b) { return a.k < b.k; }
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

template<class T>
void test(fstream &fio, vector<T> &v, function<void(vector<T>&)> f, const char *title) {
    comp_cnt = exch_cnt = 0;
//for (int i = 0; i < SS; i++) cout << v[i] << " ";cout << endl;
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//for (int i = 0; i < SS; i++) cout << v[i] << " ";cout << endl;
    check(v);
    cout << setw(16) << left << title << setw(10) << right << te - ts
#ifdef COUNTERS
        << "\t" << comp_cnt << "\t" << exch_cnt
#endif
        << endl;

    fio.seekg(0);
#ifndef STRINGS
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(T));
#else
    for (int i = 0; i < SS; ++i) getline(fio, v[i]);
#endif
}

template<>
void test(fstream &fio, vector<const char*> &v, function<void(vector<const char*>&)> f, const char *title) {
    comp_cnt = exch_cnt = 0;
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    check(v);
    cout << setw(16) << left << title << setw(10) << right << te - ts
#ifdef COUNTERS
        << "\t" << comp_cnt << "\t" << exch_cnt
#endif
        << endl;

    fio.seekg(0);
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(char*));
}

int main() {
    //cerr << sizeof(X) << endl;
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    vector<X> v;

#ifdef ALL_VARIANTS
    vector<X> vs;
    for (int i = 0; i < SS; ++i) v.push_back(i);
    do {
        vs = v;
        comp_cnt = exch_cnt = 0;
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
        counter++;
#ifdef COUNTERS
        comp_sum += comp_cnt;
        exch_sum += exch_cnt;
        total_sum += comp_cnt + exch_cnt;
        if (comp_min > comp_cnt) comp_min = comp_cnt;
        if (comp_max < comp_cnt) comp_max = comp_cnt;
        if (exch_min > exch_cnt) exch_min = exch_cnt;
        if (exch_max < exch_cnt) exch_max = exch_cnt;
        if (total_min > comp_cnt + exch_cnt) total_min = comp_cnt + exch_cnt, total_min_comp = comp_cnt, total_min_exch = exch_cnt;
        if (total_max < comp_cnt + exch_cnt) total_max = comp_cnt + exch_cnt, total_max_comp = comp_cnt, total_max_exch = exch_cnt;
#endif
        //for (int i = 0; i < SS; i++) cout << v[i].a << " ";
        //cout << comp_cnt << " " << exch_cnt << endl;
    }
    while (next_permutation(v.begin(), v.end()));
    cout << double(timer_sum)/counter
#ifdef COUNTERS
        << ' ' << comp_min << "/" << exch_min << "/" << total_min << "=" << total_min_comp << "+" << total_min_exch << " "
        << comp_max << "/" << exch_max << "/" << total_max << "=" << total_max_comp << "+" << total_max_exch << " " 
        << double(comp_sum)/counter << "+" << double(exch_sum)/counter << "=" << double(total_sum)/counter
#endif
        << endl;
#else
#ifdef SLOW_QSORT1_ORDER
    fill_for_quadratic_qsort1(v, SS);
#else
    for (int i = 0; i < SS; i++)
#ifdef RANDOM_ORDER
#ifdef STRINGS
       v.push_back([]{ string s =""; int lim = rand()%16 + 1; for (int i = 0; i < lim; ++i) s += ' ' + rand()%94; return s;}());
#elif defined(CSTRINGS)
       v.push_back([]{ int lim = rand()%16 + 1; char *s = new char[lim + 1]; int i; for (i = 0; i < lim; ++i) s[i] = ' ' + rand()%94; s[i] = 0; return s;}());
#else
       v.push_back({rand()});
#endif
#elif defined(ASCENDED_ORDER) || defined(ASCENDED_RANDOM_ORDER)
       v.push_back({i});
#elif defined(DESCENDED_ORDER)
       v.push_back({SS - i});
#elif defined(LOW_VARIATION_ORDER)
       v.push_back({rand()%LOW_VARIATION_CONST});
#else
#error NO ORDER IS SET
#endif
#endif

#ifdef ASCENDED_RANDOM_ORDER
    for (int i = 0; i < SS/100; i++)
        v[rand()%SS] = rand();
#endif
    fstream fio(FN, fio.binary | fio.trunc | fio.in | fio.out);
#ifndef STRINGS
    fio.write(reinterpret_cast<char*>(&v[0]), SS*sizeof(X));
#else
    for (int i = 0; i < 20; i++) { string s = v[0]; for (int i = 1; i < SS; i++) v[i - 1] = v[i]; v[SS - 1] = s; } //train garbage gc 
    for (int i = 0; i < SS; ++i) fio << v[i] << endl;
    fio.seekg(0);
    for (int i = 0; i < SS; ++i) getline(fio, v[i]);
#endif

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell3<X>, placeholders::_1)), "shell_10/3");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 0)), "shell_prime_e");
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 5)), "shell_10/3_oms7");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 1)), "shell_a102549");
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 2)), "shell_exp_tab");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell2<X>, placeholders::_1, 4)), "shell_prime_10/3");

#if !defined(STRINGS) && !defined(CSTRINGS)
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radixsort<X>, placeholders::_1, 8)), "radix8");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radixsort<X>, placeholders::_1, 16)), "radix16");
#ifdef PLAININT
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 7)), "radix8_oms7");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(oms7_helper<X>, placeholders::_1, 8)), "msd8_oms7");
#endif
#endif
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hsortstl<X>, placeholders::_1)), "heapsort_stl");
#ifndef STRINGS
#ifdef CSTRINGS
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(radix_bsd<X>, placeholders::_1)), "radix_bsd");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(sradix_bsd<X>, placeholders::_1)), "sradix_bsd");
#endif
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort0<X>, placeholders::_1)), "clib_qsort");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hsort_bsd<X>, placeholders::_1)), "heapsort_bsd");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(mergesort_bsd<X>, placeholders::_1)), "mergesort_bsd");
#endif
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort1<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare");
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort1tc<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare_tco");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort2<X>, placeholders::_1, 0, SS - 1)), "qsort_no_pivot");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort3<X>, placeholders::_1, 0, SS - 1)), "qsort_hoare2");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(qsort4<X>, placeholders::_1, 0, SS - 1)), "qsort_lomuto");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(stl_sort<X>, placeholders::_1)), "stlsort");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(stl_stable_sort<X>, placeholders::_1)), "stlstable");


    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(timsort<X>, placeholders::_1)), "timsort");
#ifndef CSTRINGS
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(spreadsort<X>, placeholders::_1)), "spread");
#endif
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(pdqsort<X>, placeholders::_1)), "pdq");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(spinsort<X>, placeholders::_1)), "spin");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(flat_stable_sort<X>, placeholders::_1)), "flat_stable");

    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(bubble_sort<X>, placeholders::_1)), "bubble");
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(selection_sort<X>, placeholders::_1)), "selection");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_stl<X>, placeholders::_1)), "tree_stl");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_boost<X>, placeholders::_1)), "tree_boost");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 1)), "array*1");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 2)), "array*2");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1, 3)), "array*3");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hash_sort<X>, placeholders::_1)), "hash");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort_std<X>, placeholders::_1)), "hashbt_std");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort2<X>, placeholders::_1)), "hashbt");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(hashbt_sort_boost<X>, placeholders::_1)), "hashbt_boost");

    fio.close();
    remove(FN);
#endif
    cout << "ok\t" << SS << ' ' <<  typeid(X).name() << "\n";
    //for (int i = 0; i < SS; ++i) cout << v[i] << '\n';
    return 0;
}

