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
#include "timsort.hpp"   // https://github.com/gfx/cpp-TimSort - only the header is required
#include <bsd/stdlib.h>  // for heapsort
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/sort.hpp>
#include <boost/container/set.hpp>
using namespace std;

#include "oms7.cpp" //from https://habr.com/ru/post/335920/

#define FN "tempd1"
//#define PLAININT
#define STRINGS
//#define CSTRINGS
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
#define SS 10'000 //limits due to int types of indice are slightly above 2'000'000'000
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

template <class T>
void timsort(vector<T> &a) {
   gfx::timsort(a.begin(), a.end(), std::less<T>());
}

template <>
void timsort(vector<const char*> &a) {
   gfx::timsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void spreadsort(vector<T> &a) {
   //boost::sort::spreadsort::spreadsort(&a[0], &a[0] + SS);
   boost::sort::spreadsort::integer_sort(&a[0], &a[0] + SS);
}

template <>
void spreadsort(vector<string> &a) {
   boost::sort::spreadsort::string_sort(&a[0], &a[0] + SS);
}

template <>
void spreadsort(vector<int> &a) {
   boost::sort::spreadsort::integer_sort(&a[0], &a[0] + SS);
}

/*struct bracket {
  inline unsigned char operator()(const char* x, size_t offset) const {
    return x[offset];
  }
};

struct getsize {
  inline size_t operator()(const char *x) const { return strlen(x); }
};

template <>
void spreadsort(vector<const char*> &a) {
   boost::sort::spreadsort::string_sort(&a[0], &a[0] + SS, bracket(), getsize());
}*/

template <class T>
void pdqsort(vector<T> &a) {
   boost::sort::pdqsort(&a[0], &a[0] + SS);
}

template <>
void pdqsort(vector<const char*> &a) {
   boost::sort::pdqsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void spinsort(vector<T> &a) {
   boost::sort::spinsort(&a[0], &a[0] + SS);
}

template <>
void spinsort(vector<const char*> &a) {
   boost::sort::spinsort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void flat_stable_sort(vector<T> &a) {
   boost::sort::flat_stable_sort(&a[0], &a[0] + SS);
}

template <>
void flat_stable_sort(vector<const char*> &a) {
   boost::sort::flat_stable_sort(&a[0], &a[0] + SS, [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
int cmpfunc(const void *a, const void *b) {
#ifndef STRINGS
   return *(T*)a - *(T*)b;
#else
   return ((string*)a)->compare(*(string*)b);  //doesn't work
#endif
}

int cmpfunc_char(const void *s1, const void *s2) {
        return strcmp(*(const char**)s1, *(const char**)s2);
}

template <class T>
void qsort0(vector<T> &a) {
   qsort((void*)&a[0], SS, sizeof(T), cmpfunc<T>);
}

template <>
void qsort0(vector<const char*> &a) {
   qsort((void*)&a[0], SS, sizeof(char*), cmpfunc_char);
}

template <class T>
void mergesort_bsd(vector<T> &a) {
   mergesort(&a[0], SS, sizeof(T), cmpfunc<T>);
}

template <>
void mergesort_bsd(vector<const char*> &a) {
   mergesort(&a[0], SS, sizeof(char*), cmpfunc_char);
}

template <class T>
void hsort_bsd(vector<T> &a) {
   heapsort(&a[0], SS, sizeof(T), cmpfunc<T>);
}

template <>
void hsort_bsd(vector<const char*> &a) {
   heapsort(&a[0], SS, sizeof(char*), cmpfunc_char);
}

template <class T>
void hsortstl(vector<T> &a) {
   make_heap(a.begin(), a.end());
   sort_heap(a.begin(), a.end());
}

template <>
void hsortstl(vector<const char*> &a) {
   make_heap(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
   sort_heap(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template<class T>
void radix_bsd(vector<T> &a) {
}

template<>
void radix_bsd(vector<const char*> &a) {
    radixsort((const unsigned char**)&a[0], SS, 0, 0);   
}

template<class T>
void sradix_bsd(vector<T> &a) {
}

template<>
void sradix_bsd(vector<const char*> &a) {
    sradixsort((const unsigned char**)&a[0], SS, 0, 0);   
}

template <class T>
void stl_sort(vector<T> &a) {
   sort(a.begin(), a.end());
}

template <>
void stl_sort(vector<const char*> &a) {
   sort(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template <class T>
void stl_stable_sort(vector<T> &a) {
   stable_sort(a.begin(), a.end());
}

template <>
void stl_stable_sort(vector<const char*> &a) {
   stable_sort(a.begin(), a.end(), [](const char *l, const char *r) { return strcmp(l, r) < 0; });
}

template<class T>
inline int digit(T n, int k, int N, int M) {
	return n >> N*k & M - 1;
}

template<class T>
void radixsort(vector<T> &a, int N) {
#ifndef STRINGS
	int k = 8;
        if (sizeof(T) == sizeof(int(a[0])) || typeid(T) == typeid(int)) k = 4;
        k = (k*8 + N - 1) / N;
	int M = 1 << N;
	vector<T> b(a.size());
	for (int i = 0; i < k; i++) {
                int c[M] = {0};
		for (int j = 0; j < a.size(); j++)
			c[digit(a[j], i, N, M)]++;
		for (int j = 1; j < M; j++)
			c[j] += c[j - 1];
		for (int j = a.size() - 1; j >= 0; j--)
			b[--c[digit(a[j], i, N, M)]] = a[j];
		a = b;
	}
#endif
}

template <class T>
void qsort1(vector<T> &a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    T x = a[(i + j)/2];
    do {
#ifdef COUNTERS
       while (a[i] < x) ++i, ++comp_cnt;
       while (x < a[j]) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (LBound < j) qsort1(a, LBound, j);
    if (i < UBound) qsort1(a, i, UBound);
}

template <>
void qsort1(vector<const char*> &a, int LBound, int UBound) { //Hoare, variant 1
    int i = LBound, j = UBound;
    const char *x = a[(i + j)/2];
    do {
#ifdef COUNTERS
       while (strcmp(a[i], x) < 0) ++i, ++comp_cnt;
       while (strcmp(x, a[j]) < 0) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (strcmp(a[i], x) < 0) ++i;
       while (strcmp(x, a[j]) < 0) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (LBound < j) qsort1(a, LBound, j);
    if (i < UBound) qsort1(a, i, UBound);
}

template <class T>
void qsort1tc(vector<T> &a, int LBound, int UBound) { //tail call optimization
    int i = LBound, j = UBound;
LOOP:
    T x = a[(i + j)/2];
    do {
#ifdef COUNTERS
       while (a[i] < x) ++i, ++comp_cnt;
       while (x < a[j]) --j, ++comp_cnt;
       comp_cnt += 2;
       if (i <= j) {
          if (i != j) {swap(a[i], a[j]); ++exch_cnt;}
#else
       while (a[i] < x) ++i;
       while (x < a[j]) --j;
       if (i <= j) {
          if (i != j) swap(a[i], a[j]);
#endif
          ++i;
          --j;
       }
    }
    while (i <= j);
    if (j - LBound < UBound - i) {
    if (LBound < j) qsort1(a, LBound, j);
    if (i < UBound) {   // qsort1(a, i, UBound);
        LBound = i;
        j = UBound;
        goto LOOP;
    }
    }
    else {
    if (i < UBound) qsort1(a, i, UBound);
    if (LBound < j) {  // qsort1(a, LBound, j);
        i = LBound;
        UBound = j;
        goto LOOP;
    }
    }
}

template <class T>
void qsort3(vector<T> &a, int LBound, int UBound) { //Hoare, varian 2
    if (LBound >= UBound) return;
    int i = LBound - 1, j = UBound + 1;
    T x = a[(i + j)/2];
    for(;;) {
#ifdef COUNTERS
       do ++i, ++comp_cnt; while (a[i] < x);
       do --j, ++comp_cnt; while (x < a[j]);
       comp_cnt += 2;
       if (i >= j) break;
       swap(a[i], a[j]); ++exch_cnt;
#else
       do ++i; while (a[i] < x);
       do --j; while (x < a[j]);
       if (i >= j) break;
       swap(a[i], a[j]);
#endif
    }
    qsort3(a, LBound, j);
    qsort3(a, j + 1, UBound);
}

template <>
void qsort3(vector<const char*> &a, int LBound, int UBound) { //Hoare, varian 2
    if (LBound >= UBound) return;
    int i = LBound - 1, j = UBound + 1;
    const char *x = a[(i + j)/2];
    for(;;) {
#ifdef COUNTERS
       do ++i, ++comp_cnt; while (strcmp(a[i], x) < 0);
       do --j, ++comp_cnt; while (strcmp(x, a[j]) < 0);
       comp_cnt += 2;
       if (i >= j) break;
       swap(a[i], a[j]); ++exch_cnt;
#else
       do ++i; while (strcmp(a[i], x) < 0);
       do --j; while (strcmp(x, a[j]) < 0);
       if (i >= j) break;
       swap(a[i], a[j]);
#endif
    }
    qsort3(a, LBound, j);
    qsort3(a, j + 1, UBound);
}

template <class T>
void qsort4(vector<T> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    T x = a[UBound];
#ifdef COUNTERS
    for (int j = LBound; j < UBound; ++j)
       if (a[j] < x)
          ++exch_cnt, ++comp_cnt, swap(a[i++], a[j]);
    swap(a[i], a[UBound]); ++exch_cnt;
#else
    for (int j = LBound; j < UBound; ++j)
       if (a[j] < x)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
#endif
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template <>
void qsort4(vector<const char*> &a, int LBound, int UBound) { //Lomuto
    if (LBound >= UBound) return;
    int i = LBound;
    const char *x = a[UBound];
#ifdef COUNTERS
    for (int j = LBound; j < UBound; ++j)
       if (strcmp(a[j], x) < 0)
          ++exch_cnt, ++comp_cnt, swap(a[i++], a[j]);
    swap(a[i], a[UBound]); ++exch_cnt;
#else
    for (int j = LBound; j < UBound; ++j)
       if (strcmp(a[j], x) < 0)
          swap(a[i++], a[j]);
    swap(a[i], a[UBound]);
#endif
    qsort4(a, LBound, i - 1);
    qsort4(a, i + 1, UBound);
}

template<class T>
void qsort2(vector<T> &a, int LBound, int UBound) { //no pivot
    int i = LBound, j = UBound;
    while (i != j) {
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (a[i] <= a[j])
                --j;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (a[i] <= a[j])
                ++i;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
    }
    if (i - 1 > LBound) qsort2(a, LBound, i - 1);
    if (j + 1 < UBound) qsort2(a, j + 1, UBound);
}

template<>
void qsort2(vector<const char*> &a, int LBound, int UBound) { //no pivot
    int i = LBound, j = UBound;
    while (i != j) {
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (strcmp(a[i], a[j]) <= 0)
                --j;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
        while (i != j) {
#ifdef COUNTERS
            ++comp_cnt;
#endif
            if (strcmp(a[i], a[j]) <= 0)
                ++i;
            else {
                swap(a[i], a[j]);
#ifdef COUNTERS
                ++exch_cnt;
#endif
                break;
            }
        }
    }
    if (i - 1 > LBound) qsort2(a, LBound, i - 1);
    if (j + 1 < UBound) qsort2(a, j + 1, UBound);
}

template<class T>  //Shell sort v1 (stepping by a value close to 3)
void shell1(vector<T> &a) {
  int i, j, h;
  T v;
  h = 1;
  while (h < a.size())
     h = 3*h + 1;
  h = (h - 1)/3;
  while (h) {
     i = h;
     j = i;
     v = a[i];
     while (i < a.size()) {
        j -= h;
        while (j >= 0 && v <= a[j]) {
           a[j + h] = a[j];
           j -= h;
        }
        a[j + h] = v;
        ++i;
        j = i;
        v = a[i];
     }
     h = (h - 1)/3;
  }
}

template<class T>  //Shell sort v2 (table)
void shell2(vector<T> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2

  //static const int x2[] = {230242168, 84701360, 31159889, 11463083, 4217032, 1551360, 570713, 209954, 77238, 28414, 10453, 3845, 1415, 520, 191, 70, 26, 10, 4, 1, 0}; //experimental

  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (a[j] > a[j + gap]) {
           //a[j] = a[j + gap];
#ifdef COUNTERS
           ++comp_cnt;
           ++exch_cnt;
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        ++comp_cnt;
#else
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
#endif
        //a[j] = t;
     }
  }
}

template<>  //Shell sort v2 (table)
void shell2(vector<const char*> &a, int type) {
  static const int x0[] = {485165237, 178482289, 65659969, 24154967, 8886109, 3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes approximately close to powers of e
//static const int x0[] = {485165237, 178482289, 65659969, 24154957, 8886113, 3269011, 1202603, 442399, 162751, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0};  //primes close to powers of e
  static const int x1[] = {284820883, 104779757, 38546311, 14180393, 5216681, 1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};  //8 first numbers of A102549 and approximation
  static const int x2[] = {67108859, 33554393, 16777213, 8388617, 4194301, 2097143, 1048571, 524287, 262253, 131063, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 2, 1, 0};  //primes close to powers of 2

  //static const int x2[] = {230242168, 84701360, 31159889, 11463083, 4217032, 1551360, 570713, 209954, 77238, 28414, 10453, 3845, 1415, 520, 191, 70, 26, 10, 4, 1, 0}; //experimental

  static const int x3[] = {485165195, 178482301, 65659969, 24154953, 8886111, 3269017, 1202604, 442413, 162755, 59874, 22026, 8103, 2981, 1097, 403, 148, 55, 20, 7, 3, 1, 0};  //values close to powers of e
  static const int x4[] = {688549733, 206564921, 61969477, 18590849, 5577239, 1673179, 501953, 150587, 45179, 13553, 4073, 1223, 367, 109, 31, 11, 3, 1, 0};  //values of primes close to numbers from sequence s[n+1] = 10s[n]/3
  const int *p;
  switch (type) {
      case 0: p = x0; break;
      case 1: p = x1; break;
      case 2: p = x2; break;
      case 3: p = x3; break;
      case 4: p = x4; break;
  }
  int i, j, k = 0, gap;
  while (p[k] >= a.size()) ++k;
  while (p[k]) {
     gap = p[k++];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (strcmp(a[j], a[j + gap]) > 0) {
           //a[j] = a[j + gap];
#ifdef COUNTERS
           ++comp_cnt;
           ++exch_cnt;
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        ++comp_cnt;
#else
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
#endif
        //a[j] = t;
     }
  }
}

template<class T>  //Shell sort v3 (stepping by values from the sequence s[n+1] = 10s[n]/3)
void shell3(vector<T> &a) {
  static const int maxi = 19; 
  static int p[maxi] = {0, 1};
  int i, j, k, gap;
  if (p[2] == 0)
    for (k = 2; k < maxi; ++k) p[k] = 10*p[k - 1]/3;
  else
    k = maxi;
  while (p[--k] >= a.size());
  while (p[k]) {
     gap = p[k--];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (a[j] > a[j + gap]) {
           //a[j] = a[j + gap];
#ifdef COUNTERS
           ++comp_cnt;
           ++exch_cnt;
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        ++comp_cnt;
#else
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
#endif
        //a[j] = t;
     }
  }
}

template<>  //Shell sort v3 (stepping by values from the sequence s[n+1] = 10s[n]/3)
void shell3(vector<const char *> &a) {
  static const int maxi = 19; 
  static int p[maxi] = {0, 1};
  int i, j, k, gap;
  if (p[2] == 0)
    for (k = 2; k < maxi; ++k) p[k] = 10*p[k - 1]/3;
  else
    k = maxi;
  while (p[--k] >= a.size());
  while (p[k]) {
     gap = p[k--];
     for (i = gap; i < a.size(); ++i) {
        j = i - gap;
        //T t = a[j + gap];
        while (strcmp(a[j], a[j + gap]) > 0) {
           //a[j] = a[j + gap];
#ifdef COUNTERS
           ++comp_cnt;
           ++exch_cnt;
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
        ++comp_cnt;
#else
           swap(a[j], a[j + gap]);
           if (j >= gap) j -= gap; else break;
        }
#endif
        //a[j] = t;
     }
  }
}

template<class T>
void bubble_sort(vector<T> &a) {
    int i, UBound;
    bool epf;
    UBound = a.size() - 1;
    do {
        epf = false;
        for (i = 0; i < UBound; ++i)
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                epf = true;
            }
        --UBound;
    }
    while (epf);
}

template<>
void bubble_sort(vector<const char*> &a) {
    int i, UBound;
    bool epf;
    UBound = a.size() - 1;
    do {
        epf = false;
        for (i = 0; i < UBound; ++i)
            if (strcmp(a[i], a[i + 1]) > 0) {
                swap(a[i], a[i + 1]);
                epf = true;
            }
        --UBound;
    }
    while (epf);
}

template<class T>
void selection_sort(vector<T> &a) {
    int max_i, min_i, i = 0;

    while (a.size() - 2*i > 1) {
        T max = a[max_i = a.size() - i - 1], min = a[min_i = i];
        for (int k = i; k < a.size() - i; k++) {
            if (max < a[k]) max = a[max_i = k];
            if (min > a[k]) min = a[min_i = k];
        }
        if (max_i != a.size() - i - 1) swap(a[a.size() - i - 1], a[max_i]);
        if (a.size() - i - 1 == min_i) min_i = max_i;
        if (min_i != i) swap(a[i], a[min_i]);
        ++i;
    }
}

template<>
void selection_sort(vector<const char*> &a) {
    int max_i, min_i, i = 0;

    while (a.size() - 2*i > 1) {
        const char *max = a[max_i = a.size() - i - 1], *min = a[min_i = i];
        for (int k = i; k < a.size() - i; k++) {
            if (strcmp(max, a[k]) < 0) max = a[max_i = k];
            if (strcmp(min, a[k]) > 0) min = a[min_i = k];
        }
        if (max_i != a.size() - i - 1) swap(a[a.size() - i - 1], a[max_i]);
        if (a.size() - i - 1 == min_i) min_i = max_i;
        if (min_i != i) swap(a[i], a[min_i]);
        ++i;
    }
}

template<class T, int S> class Sort_alloc : public allocator<T> {
   void* pool;
   int count;
public:
   template<class U> struct rebind { typedef Sort_alloc<U, S> other; };
   Sort_alloc() { count = 0; pool = new char [sizeof(T)*S]; }
   T* allocate(size_t, void* = 0);
   void deallocate(T*, size_t) {}
   ~Sort_alloc() { delete [] (char*)pool; }
};

template<class T, int S> T* Sort_alloc<T, S>::allocate(size_t n, void*) {
   T* p = static_cast<T*>(pool) + count;
   count += n;
   return p;
}

template<class T>
void tree_sort_stl(vector<T>& a) {
    multiset<T, less<T>, Sort_alloc<T, SS>> ms;
    //multiset<T> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

struct pchar_less {
    bool operator()(const char *l, const char *r) const { return strcmp(l, r) < 0; }
};
 
template<>
void tree_sort_stl(vector<const char*>& a) {
    multiset<const char*, pchar_less, Sort_alloc<const char*, SS>> ms;
    //multiset<const char*, pchar_less> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

template<class T>
void tree_sort_boost(vector<T>& a) {
    boost::container::multiset<T, less<T>, Sort_alloc<T, SS>> ms;
    //boost::container::multiset<T> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

template<>
void tree_sort_boost(vector<const char*>& a) {
    boost::container::multiset<const char*, pchar_less, Sort_alloc<const char*, SS>> ms;
    //boost::container::multiset<const char*, pchar_less> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}

uint32_t convert(const char *s) {
    uint32_t r = 0.;
    for (int i = 0; s[i] && i < 4; ++i)
        r += s[i]*(1U << ((3 - i) << 3));
    return r;
}
 
uint32_t operator-(const string &s1, const string &s2) {
    return convert(s1.c_str()) - convert(s2.c_str());
}

template<class T> int hash_func(T d, T minElem, T maxElem) {
    return long(d - minElem)*(SS - 1)/(maxElem - minElem);
}

template<> int hash_func(const char *d, const char *minElem, const char *maxElem) {
    return long(convert(d) - convert(minElem))*(SS - 1)/(convert(maxElem) - convert(minElem));
}

template<class T> struct HashSort {
    struct HashElement {
        T data;
        int next;
    };
    HashElement *hashData;
    int *hashPtr, freePtr;
    T minElem, maxElem;
    HashSort() {
        hashData = new HashElement[SS];
        hashPtr = new int[SS];
        freePtr = 0;
        for (int i = 0; i < SS; ++i)
           hashPtr[i] = -1;
    }
    ~HashSort() {
        delete [] hashData;
        delete [] hashPtr;
    }
    void addElement(T d) {
        int prevPtr, j = hash_func(d, minElem, maxElem), curPtr = hashPtr[j];
        if (curPtr == -1) {
           hashPtr[j] = freePtr;
           goto l1;
        }
        prevPtr = -1;
        while (curPtr != -1) {
           if (hashData[curPtr].data > d) {
              if (prevPtr == -1) {
                 hashData[freePtr].next = hashPtr[j];
                 hashPtr[j] = freePtr;
              } else {
                 hashData[prevPtr].next = freePtr;
                 hashData[freePtr].next = curPtr;
              }
              goto l2; 
           }
           prevPtr = curPtr;
           curPtr = hashData[curPtr].next;
        }
        hashData[prevPtr].next = freePtr;
l1:
        hashData[freePtr].next = -1;
l2:
        hashData[freePtr++].data = d;
     }
};

template<>
void HashSort<const char*>::addElement(const char *d) {
    int prevPtr, j = hash_func(d, minElem, maxElem), curPtr = hashPtr[j];
    if (curPtr == -1) {
        hashPtr[j] = freePtr;
        goto l1;
    }
    prevPtr = -1;
    while (curPtr != -1) {
        if (strcmp(hashData[curPtr].data, d) > 0) {
            if (prevPtr == -1) {
                hashData[freePtr].next = hashPtr[j];
                hashPtr[j] = freePtr;
             } else {
                hashData[prevPtr].next = freePtr;
                hashData[freePtr].next = curPtr;
             }
             goto l2; 
        }
        prevPtr = curPtr;
        curPtr = hashData[curPtr].next;
    }
    hashData[prevPtr].next = freePtr;
l1:
    hashData[freePtr].next = -1;
l2:
    hashData[freePtr++].data = d;
}

template<class T> void hash_sort(vector<T> &a) {
    HashSort<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    hs.freePtr = 0;
    for (int i = 0; i < SS; ++i) {
         int j = hs.hashPtr[i];
         while (j != -1) {
             a[hs.freePtr++] = hs.hashData[j].data;
             j = hs.hashData[j].next;
         }
    }
}

template<> void hash_sort(vector<const char *> &a) {
    HashSort<const char *> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    hs.freePtr = 0;
    for (int i = 0; i < SS; ++i) {
         int j = hs.hashPtr[i];
         while (j != -1) {
             a[hs.freePtr++] = hs.hashData[j].data;
             j = hs.hashData[j].next;
         }
    }
}

template<class T> struct HashBTSort {
    typedef std::multiset<T> HashElement;
    HashElement *hashData;
    T minElem, maxElem;
    HashBTSort() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort() {
        delete [] hashData;
    }
    void addElement(T d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<> struct HashBTSort<const char*> {
    typedef std::multiset<const char*, pchar_less> HashElement;
    HashElement *hashData;
    const char *minElem, *maxElem;
    HashBTSort() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort() {
        delete [] hashData;
    }
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<class T> void hashbt_sort_std(vector<T> &a) {
    HashBTSort<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<> void hashbt_sort_std(vector<const char*> &a) {
    HashBTSort<const char*> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<class T> struct HashBTSort_boost {
    typedef boost::container::multiset<T> HashElement;
    HashElement *hashData;
    T minElem, maxElem;
    HashBTSort_boost() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort_boost() {
        delete [] hashData;
    }
    void addElement(T d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<> struct HashBTSort_boost<const char*> {
    typedef boost::container::multiset<const char*, pchar_less> HashElement;
    HashElement *hashData;
    const char *minElem, *maxElem;
    HashBTSort_boost() {
        hashData = new HashElement[SS];
    }
    ~HashBTSort_boost() {
        delete [] hashData;
    }
    void addElement(const char *d) {
        hashData[hash_func(d, minElem, maxElem)].insert(d);
    }
};

template<class T> void hashbt_sort_boost(vector<T> &a) {
    HashBTSort_boost<T> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (hs.maxElem < a[i]) hs.maxElem = a[i];
        if (hs.minElem > a[i]) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<> void hashbt_sort_boost(vector<const char*> &a) {
    HashBTSort_boost<const char*> hs;
    hs.maxElem = hs.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(hs.maxElem, a[i]) < 0) hs.maxElem = a[i];
        if (strcmp(hs.minElem, a[i]) > 0) hs.minElem = a[i];
    }
    if (hs.maxElem == hs.minElem) return;
    for (int i = 0; i < SS; ++i) 
         hs.addElement(a[i]);
    int n = 0;
    for (int i = 0; i < SS; ++i)
        for (auto it: hs.hashData[i])
             a[n++] = it;
}

template<class T> struct BinaryTreeForHash {
     struct Node {
         T data;
         int l, r;
     };
     int i, *storageRoot;
     Node *storage;
     int allocIdx = 0;
     T maxElem, minElem;
     BinaryTreeForHash() {
         storageRoot = new int[SS];
         for (int i = 0; i < SS; ++i) storageRoot[i] = -1;
         storage = new Node[SS];
     }
     ~BinaryTreeForHash() {
         delete [] storageRoot;
         delete [] storage;
     }
     void insert(T d) {
         int j = hash_func(d, minElem, maxElem);
         int t = storageRoot[j], p = t, dir;
         storage[allocIdx] = {d, -1, -1};
         while (t >= 0) {
              p = t;
              if (d < storage[t].data)
                  t = storage[t].l, dir = 0;
              else if (d > storage[t].data)
                  t = storage[t].r, dir = 1;
              else if (rand()&1)
                  t = storage[t].l, dir = 0;
              else
                  t = storage[t].r, dir = 1;
         }
         if (p == -1)
             storageRoot[j] = allocIdx;
         else if (dir == 0)
            storage[p].l = allocIdx;
         else
            storage[p].r = allocIdx;
         ++allocIdx;
     }
     void traversal(vector<T> &a, int idx) {
          if (idx < 0) return;
          traversal(a, storage[idx].l);
          a[i++] = storage[idx].data;
          traversal(a, storage[idx].r);
     }
};

template<> struct BinaryTreeForHash<const char*> {
     struct Node {
         const char* data;
         int l, r;
     };
     int i, *storageRoot;
     Node *storage;
     int allocIdx = 0;
     const char *maxElem, *minElem;
     BinaryTreeForHash() {
         storageRoot = new int[SS];
         for (int i = 0; i < SS; ++i) storageRoot[i] = -1;
         storage = new Node[SS];
     }
     ~BinaryTreeForHash() {
         delete [] storageRoot;
         delete [] storage;
     }
     void insert(const char *d) {
         int j = hash_func(d, minElem, maxElem);
         int t = storageRoot[j], p = t, dir;
         storage[allocIdx] = {d, -1, -1};
         while (t >= 0) {
              p = t;
              if (strcmp(d, storage[t].data) < 0)
                  t = storage[t].l, dir = 0;
              else if (strcmp(d, storage[t].data) > 0)
                  t = storage[t].r, dir = 1;
              else if (rand()&1)
                  t = storage[t].l, dir = 0;
              else
                  t = storage[t].r, dir = 1;
         }
         if (p == -1)
             storageRoot[j] = allocIdx;
         else if (dir == 0)
            storage[p].l = allocIdx;
         else
            storage[p].r = allocIdx;
         ++allocIdx;
     }
     void traversal(vector<const char *> &a, int idx) {
          if (idx < 0) return;
          traversal(a, storage[idx].l);
          a[i++] = storage[idx].data;
          traversal(a, storage[idx].r);
     }
};

template<class T> void hashbt_sort2(vector<T> &a) {
    BinaryTreeForHash<T> bt;
    
    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (bt.maxElem < a[i]) bt.maxElem = a[i];
        if (bt.minElem > a[i]) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

template<> void hashbt_sort2(vector<const char* > &a) {
    BinaryTreeForHash<const char*> bt;
    
    bt.maxElem = bt.minElem = a[0];
    for (int i = 1; i < SS; ++i) {
        if (strcmp(bt.maxElem, a[i]) < 0) bt.maxElem = a[i];
        if (strcmp(bt.minElem, a[i]) > 0) bt.minElem = a[i];
    }
    if (bt.maxElem == bt.minElem) return;
    for (int i = 0; i < SS; ++i) 
        bt.insert(a[i]);
    bt.i = 0;
    for (int i = 0; i < SS; ++i)
        bt.traversal(a, bt.storageRoot[i]);
}

template<class T> void array_sort(vector<T> &a) {
    T *auxArray = new T[SS], maxElem = a[0], minElem = a[0];
    int i, j, l, k, m;
    for (int i = 1; i < SS; ++i) {
        if (maxElem < a[i]) maxElem = a[i];
        if (minElem > a[i]) minElem = a[i];
    }
    if (maxElem == minElem) return;
    for (i = 0; i < SS; ++i)
#ifndef STRINGS
        auxArray[i] = {-1};    //so we can't use negative numbers
#else
        auxArray[i] = {0};
#endif
    for (i = 0; i < SS; ++i) {
        j = long(a[i] - minElem)*(SS - 1)/(maxElem - minElem);
#ifndef STRINGS
        if (auxArray[j] == -1)
#else
        if (auxArray[j] == string({0}))
#endif
            auxArray[j] = a[i];
        else {
            if (auxArray[j] > a[i]) {
                while (j > 0)
                    if (auxArray[j - 1] > a[i])
                        --j;
                    else
                        break;
                m = -1;
            } else {
                while (j + 1 < SS)
#ifndef STRINGS
                    if (auxArray[j + 1] < a[i] && auxArray[j + 1] != -1)
#else
                    if (auxArray[j + 1] < a[i] && auxArray[j + 1] != string({0}))
#endif
                        ++j;
                    else
                        break;
                m = 1;
           }
           k = 0;
           for (;;) {
#ifndef STRINGS
               if (k + j >= 0 && k + j < SS && auxArray[k + j] == -1)
#else
               if (k + j >= 0 && k + j < SS && auxArray[k + j] == string({0}))
#endif
                   break;
               if (k > 0) k = -k; else k = 1 - k;
           }
           l = j + k;
           if (k > 0) k = 1; else k = -1;
           j += (m + k)/2;
           while (l != j) {
               auxArray[l] = auxArray[l - k];
               l -= k;
           }
           auxArray[j] = a[i];
        }
    }
    for (i = 0; i < SS; ++i)
        a[i] = auxArray[i];
    delete [] auxArray;
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
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(char*));
#else
    for (int i = 0; i < SS; ++i) getline(fio, v[i]);
#endif
}

template<>
void test(fstream &fio, vector<const char*> &v, function<void(vector<const char*>&)> f, const char *title) {
//vector<char*> cv(SS); for (int i = 0; i < SS; ++i) { cv[i] = new char [strlen(v[i]) + 1]; strcpy(cv[i], v[i]); }
    comp_cnt = exch_cnt = 0;
//for (int i = 0; i < SS; i++) cout << v[i] << "\n";cout << endl;
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    f(v);
    auto te = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//for (int i = 0; i < SS; i++) cout << v[i] << "\n";cout << endl;
    check(v);
    cout << setw(16) << left << title << setw(10) << right << te - ts
#ifdef COUNTERS
        << "\t" << comp_cnt << "\t" << exch_cnt
#endif
        << endl;

    fio.seekg(0);
    fio.read(reinterpret_cast<char*>(&v[0]), SS*sizeof(char*));
//for(int i = 0; i < SS; ++i) { if (strcmp(cv[i], v[i])) throw 1; delete [] cv[i]; }
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
    for (int i = 0; i < SS; ++i) fio << v[i] << endl;
#endif
    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(shell1<X>, placeholders::_1)), "shell1");
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

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(bubble_sort<X>, placeholders::_1)), "bubble");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(selection_sort<X>, placeholders::_1)), "selection");

    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_stl<X>, placeholders::_1)), "tree_stl");
    test(fio, v, static_cast<function<void(vector<X>&)>>(bind(tree_sort_boost<X>, placeholders::_1)), "tree_boost");

    //test(fio, v, static_cast<function<void(vector<X>&)>>(bind(array_sort<X>, placeholders::_1)), "array");
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

