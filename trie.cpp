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
    T* data;
    Data<T> *next;
};
template<class T>
struct Elem {
    Data<T>* pdata;
    Transition *ts;
};
template<class T> struct Trie {
    vector<Elem<T>> v;
    int maxl, cnt;
    Trie(int sz, int m) : v(sz), maxl(m), cnt(0) {}
    void newe(Elem<T> &e, T* pd) {
        Data<T> *tp = new Data<T>;
        tp->next = e.pdata;
        e.pdata = tp;
        tp->data = pd;
    }
    void add(T *pd, int d = 0, int ce = 0) {
        unsigned char tc = *((char*)pd + maxl - 1 - d);
        if (v[ce].ts == 0) {
            v[ce].ts = new Transition;
            v[ce].ts->c = tc;
            v[ce].ts->t = ++cnt;
            v[ce].ts->next = 0;
            if (++d == maxl)
                newe(v[cnt], pd);
            else
                add(pd, d, cnt);
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
                    newe(v[cnt], pd);
                else
                    add(pd, d, cnt);
            } else if (p->c == tc)
                if (++d == maxl)
                    newe(v[p->t], pd);
                else
                    add(pd, d, p->t);
            else if (p != pp) {
                Transition *t = new Transition;
                t->next = p;
                pp->next = t;
                t->c = tc;
                t->t = ++cnt;
                if (++d == maxl)
                    newe(v[cnt], pd);
                else
                    add(pd, d, cnt);
            } else {
                v[ce].ts = new Transition;
                v[ce].ts->next = p;
                v[ce].ts->c = tc;
                v[ce].ts->t = ++cnt;
                if (++d == maxl)
                    newe(v[cnt], pd);
                else
                    add(pd, d, cnt);
            }
        }
    }
    void traversal(int ce = 0) {
        Data<T> *d = v[ce].pdata;
        while (d) {
            //cout << *d->data << endl;
            d = d->next;
        }
        Transition *p = v[ce].ts;
        while (p) {
            traversal(p->t);
            p = p->next;
        }
    }
};

int main() {
    vector<int> a(1'000'000);
    for (int i = 0; i < 1'000'000; ++i) a[i] = rand()%70000;
    Trie<int> trie(a.size()*4, sizeof(int));
    for (int i = 0; i < a.size(); ++i) trie.add(&a[i]);
    trie.traversal();
}

