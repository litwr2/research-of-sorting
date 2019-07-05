#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#include "baseop.cpp"

int main() {
    string in1, in2, out;
    getline(cin, in1);
    getline(cin, in2);
    cout << fixed << convert(in1.c_str()) << ' ' << convert(in2.c_str()) << endl;
}

