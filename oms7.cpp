#include "opt/oms7base.cpp"  //from https://habr.com/ru/post/335920/

template<class T>
void oms7_helper(vector<T> &a, int type) {
#if T==int
    //if (typeid(T) != typeid(int)) throw "only int type supported";
    switch (type) {
    case 0: shellsort(&a[0], &a[a.size()]); break;
    case 1: shellsorthib(&a[0], &a[a.size()]); break;
    case 2: shellsortsedgwick(&a[0], &a[a.size()]); break;
    case 3: shellsortpratt(&a[0], &a[a.size()]); break;
    case 4: myshell1(&a[0], &a[0] + a.size()); break;
    case 5: myshell2(&a[0], &a[0] + a.size()); break;
    case 6: myshell3(&a[0], &a[a.size()]); break;
    case 7: radixsort(&a[0], &a[a.size()]); break;
    case 8: radixsortmsd(&a[0], &a[a.size()]); break;
    }
#endif
}

