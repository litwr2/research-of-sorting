#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib>
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/sort.hpp>
#include <boost/container/set.hpp>

using namespace std;

#define SS 100'000'000
#include "tree.cpp"


int main() {
    string in1, in2, out;
    vector<int> v(SS);
    for (int i = 0; i < SS; ++i) v[i] = rand()%7777;
    cout << "ready\n";
    //tree_sort_stl(v);
    system("ps -A|grep out >zz");
    return 0;
}

