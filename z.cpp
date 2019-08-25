#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
//#include <set>
#include <cstdlib>
//#include <boost/sort/spreadsort/spreadsort.hpp>
//#include <boost/sort/pdqsort/pdqsort.hpp>
//#include <boost/sort/sort.hpp>
//#include <boost/container/set.hpp>

using namespace std;

#define SS 10'000

#include "baseop.cpp"
#include "bubble.cpp"
#include "std.cpp"
#include "trie.cpp"

#define N 64

int main() {
    vector<const char*> a;
    //vector<char[12]> a(SS);
    a.reserve(SS);
    for (int i = 0; i < SS; ++i) {
       char *s = new char[N];
       for (int i = 0; i < N; ++i) s[i] = rand()%26 + 'A';
       s[N - 1] = 0;
       a.push_back(s);
    }
cout << "ok to sort" << endl;
    //bubble_sort(a);
    //qsort0(a);
    Trie<const char*>::sort(a);
    for (int i = 0; i < SS; ++i) delete [] a[i];
    return 0;
}

