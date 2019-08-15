#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

struct Transition {
    unsigned char c;
    int t;
    Transition *next;
};
template<class T>
struct Data {
    int data;
    Data<T> *next;
};
template<class T>
struct Elem {
    Data<T>* pdata;
    Transition *ts;
};
template<class T> struct Trie {
    vector<Elem<T>> v;
    vector<T> &a, ca;
    int maxl, cnt;
    Trie(vector<T> &a, int m) : v(a.size()*4), a(a), ca(a), maxl(m), cnt(0) {}
    void newe(Elem<T> &e, int index) {
        Data<T> *tp = new Data<T>;
        tp->next = e.pdata;
        e.pdata = tp;
        tp->data = index;
    }
    void add(int index, int d = 0, int ce = 0) {
        unsigned char tc = *((char*)&ca[index] + maxl - 1 - d);
        if (v[ce].ts == 0) {
            v[ce].ts = new Transition;
            v[ce].ts->c = tc;
            v[ce].ts->t = ++cnt;
            v[ce].ts->next = 0;
            if (++d == maxl)
                newe(v[cnt], index);
            else
                add(index, d, cnt);
        } else {
            Transition *p = v[ce].ts, *pp = p;
            while (p && p->c < tc) {
                pp = p;
                p = p->next;
            }
            if (p == 0) {
                p = pp->next = new Transition;
                p->next = 0;
                p->c = tc;
                p->t = ++cnt;
                if (++d == maxl)
                    newe(v[cnt], index);
                else
                    add(index, d, cnt);
            } else if (p->c == tc)
                if (++d == maxl)
                    newe(v[p->t], index);
                else
                    add(index, d, p->t);
            else if (p != pp) {
                Transition *t = new Transition;
                t->next = p;
                pp->next = t;
                t->c = tc;
                t->t = ++cnt;
                if (++d == maxl)
                    newe(v[cnt], index);
                else
                    add(index, d, cnt);
            } else {
                v[ce].ts = new Transition;
                v[ce].ts->next = p;
                v[ce].ts->c = tc;
                v[ce].ts->t = ++cnt;
                if (++d == maxl)
                    newe(v[cnt], index);
                else
                    add(index, d, cnt);
            }
        }
    }
    void traversal(int ce = 0) {
        Data<T> *d = v[ce].pdata;
        while (d) {
            a[cnt++] = ca[d->data];
            d = d->next;
        }
        Transition *p = v[ce].ts;
        while (p) {
            traversal(p->t);
            p = p->next;
        }
    }
    static void sort(vector<T> &a) {
        Trie<int> trie(a, sizeof(int));
        for (int i = 0; i < a.size(); ++i)
            trie.add(i);
        trie.cnt = 0;
        trie.traversal();
    }
};

int main() {
    vector<int> a(1'000'000);
    for (int i = 0; i < 1'000'000; ++i) a[i] = rand()%70000;
    Trie<int>::sort(a);
    for (int i = 1; i < a.size(); ++i)
       if (a[i - 1] > a[i]) return 1;
    cout << "ok\n";
    return 0;
}

