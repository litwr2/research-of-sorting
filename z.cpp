#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#include "baseop.cpp"

void printstr20(const char *s) {
    for (int i = 0; i < 20; ++i)
        cout << (int) s[i] << ' ';
    cout << endl;
}

int main() {
    string in1, in2, out;
    getline(cin, in1);
    getline(cin, in2);
    char *p = pchar_difference(in1.c_str(), in2.c_str());
    printstr20(p);
}

