#include <boost/container/flat_set.hpp>
#include <iostream>
#include <utility>
#define SS 200'000
int main() {
    boost::container::flat_multiset<int> fms;
    for (int i = 0; i < SS; ++i) fms.insert(rand());
    return 0;
}
