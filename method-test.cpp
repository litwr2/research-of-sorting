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
#define SS 10000 //limits due to int types of indice are slightly above 2'000'000'000
#endif

#define RANDOM
#define LOW_VARIATION_CONST 0
#define STRINGS_SHORT

#include "oms7.cpp"
#include "baseop.cpp"
#include "fillings.cpp"
#include "tim.cpp"
#include "std.cpp"
#include "boost.cpp"
#include "bsd.cpp"
#include "radix.cpp"
#include "qsort.cpp"
#include "dp-quick.cpp"
#include "shell.cpp"
#include "tree.cpp"
#include "hash.cpp"
#include "hashtree.cpp"
#include "array.cpp"
#include "bubble.cpp"
#include "selection.cpp"
#include "insertion.cpp"

int main() {
    vector<string> a;
    fill(a);
///    for (int i = 0; i < SS; ++i) a.push_back(uint64_t(rand())*rand());
//    for (int i = 0; i < SS; ++i) cout << a[i] << ' '; cout << endl;
//    radixsortmsd(a, 4);
//    insertion_sort(a);
      radixsort(a, 8);
//    for (int i = 0; i < SS; ++i) cout << a[i] << '\n'; cout << endl;
    for (int i = 1; i < SS; ++i) if (a[i - 1] > a[i]) {cout << "ERROR" << endl; break;}
//    for (int i = 1; i < SS; ++i) if (strcmp(a[i - 1], a[i]) > 0) {cout << "ERROR" << endl; break;}
    return 0;
}

