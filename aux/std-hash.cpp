#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

namespace std {

  struct hashkey {
    size_t operator()(const int& k) const {
      return k;
    }
  };

}

struct hashequal {
    bool operator()(const int &a, const int &b) const {
        return a == b;
    } 
};

//template<class T>
void hash_sort_stl(vector<int>& a) {
    unordered_multiset<int, hashkey, hashequal> ms;
    for (auto i: a)
        ms.insert(i);
    int i = 0;
    for (auto e: ms)
        a[i++] = e;
}


int main() {
    vector<int> a(10);
    for (int &i: a) i = rand()%1000;
    hash_sort_stl(a);
    for (int i = 0; i < a.size(); ++i) cout << a[i] << ' ';cout << endl;
    for(int i = 1; i < a.size(); ++i)
        if (a[i - 1] > a[i])
            cout << i << " ERROR!\n";
    return 0;
}
