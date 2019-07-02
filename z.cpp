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
    cout << pchar_difference(in1.c_str(), in2.c_str()) << endl;
}

