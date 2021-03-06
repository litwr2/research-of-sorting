#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

struct Transition {
    unsigned char c;
    int t;
    int next;
};
struct Data {
    int data;
    int next;
};
struct Elem {
    int pdata;
    int ts;
};

#define vE(n) ((Elem&)v[n])
#define vT(n) ((Transition&)v[n])
#define vD(n) ((Data&)v[n])

template<class T> struct Trie {
    vector<char[max(sizeof(Transition), max(sizeof(Elem), sizeof(Data)))]> v;
    vector<T> &a, ca;
    int maxl, cnt;
    Trie(vector<T> &a, size_t sz) : v((2*sz + 1)*a.size() + 1), a(a), ca(a), maxl(sz), cnt(0) {
        for (int i = 0; i < v.size(); ++i)
            vE(i).pdata = vE(i).ts = -1;
    }
    void newe(Elem &e, int index) {
        int tp = ++cnt;
        vD(tp).next = e.pdata;
        e.pdata = tp;
        vD(tp).data = index;
    }
    void add(int index, int d = 0, int ce = 0) {
        unsigned char tc = *((char*)&ca[index] + maxl - 1 - d);
        if (vE(ce).ts < 0) {
            vE(ce).ts = ++cnt;
            vT(vE(ce).ts).c = tc;
            vT(vE(ce).ts).t = ++cnt;
            vT(vE(ce).ts).next = -1;
            if (++d == maxl)
                newe(vE(cnt), index);
            else
                add(index, d, cnt);
        } else {
            int p = vE(ce).ts, pp = p;
            while (p >= 0 && vT(p).c < tc) {
                pp = p;
                p = vT(p).next;
            }
            if (p < 0) {
                p = vT(pp).next = ++cnt;
                vT(p).next = -1;
                vT(p).c = tc;
                vT(p).t = ++cnt;
                if (++d == maxl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            } else if (vT(p).c == tc)
                if (++d == maxl)
                    newe(vE(vT(p).t), index);
                else
                    add(index, d, vT(p).t);
            else if (p != pp) {
                int t = ++cnt;
                vT(t).next = p;
                vT(pp).next = t;
                vT(t).c = tc;
                vT(t).t = ++cnt;
                if (++d == maxl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            } else {
                pp = vE(ce).ts = ++cnt;
                vT(pp).next = p;
                vT(pp).c = tc;
                vT(pp).t = ++cnt;
                if (++d == maxl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            }
        }
    }
    void traversal(int ce = 0) {
        int d = vE(ce).pdata;
        while (d >= 0) {
            a[cnt++] = ca[vD(d).data];
            d = vD(d).next;
        }
        int p = vE(ce).ts;
        while (p >= 0) {
            traversal(vT(p).t);
            p = vT(p).next;
        }
    }
    static void sort(vector<T> &a) {
        Trie<T> trie(a, sizeof(T) == sizeof(int)*5 ? sizeof(int) : sizeof(T));
        for (int i = 0; i < a.size(); ++i)
            trie.add(i);
        trie.cnt = 0;
        trie.traversal();
    }
};

template<> struct Trie<string> {
    vector<char[max(sizeof(Transition), max(sizeof(Elem), sizeof(Data)))]> v;
    vector<string> &a, ca;
    int maxl, cnt;
    Trie(vector<string> &a, size_t as) : v(as), a(a), ca(a), cnt(0) {
        for (int i = 0; i < v.size(); ++i)
            vE(i).pdata = vE(i).ts = -1;
    }
    void newe(Elem &e, int index) {
        int tp = ++cnt;
        vD(tp).next = e.pdata;
        e.pdata = tp;
        vD(tp).data = index;
    }
    void add(int index, int d = 0, int ce = 0) {
        size_t sl = ca[index].length();
        if (sl == 0) {
            newe(vE(0), index);
            return;
        }
        unsigned char tc = ca[index][d];
        if (vE(ce).ts < 0) {
            vE(ce).ts = ++cnt;
            vT(vE(ce).ts).c = tc;
            vT(vE(ce).ts).t = ++cnt;
            vT(vE(ce).ts).next = -1;
            if (++d == sl)
                newe(vE(cnt), index);
            else
                add(index, d, cnt);
        } else {
            int p = vE(ce).ts, pp = p;
            while (p >= 0 && vT(p).c < tc) {
                pp = p;
                p = vT(p).next;
            }
            if (p < 0) {
                p = vT(pp).next = ++cnt;
                vT(p).next = -1;
                vT(p).c = tc;
                vT(p).t = ++cnt;
                if (++d == sl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            } else if (vT(p).c == tc)
                if (++d == sl)
                    newe(vE(vT(p).t), index);
                else
                    add(index, d, vT(p).t);
            else if (p != pp) {
                int t = ++cnt;
                vT(t).next = p;
                vT(pp).next = t;
                vT(t).c = tc;
                vT(t).t = ++cnt;
                if (++d == sl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            } else {
                pp = vE(ce).ts = ++cnt;
                vT(pp).next = p;
                vT(pp).c = tc;
                vT(pp).t = ++cnt;
                if (++d == sl)
                    newe(vE(cnt), index);
                else
                    add(index, d, cnt);
            }
        }
    }
    void traversal(int ce = 0) {
        int d = vE(ce).pdata;
        while (d >= 0) {
            swap(a[cnt++], ca[vD(d).data]);
            d = vD(d).next;
        }
        int p = vE(ce).ts;
        while (p >= 0) {
            traversal(vT(p).t);
            p = vT(p).next;
        }
    }
    static void sort(vector<string> &a) {
        size_t l = 0;
        for (int i = 0; i < a.size(); ++i)
            l += a[i].length();
        Trie<string> trie(a, 2*l + a.size() + 1);
        for (int i = 0; i < a.size(); ++i)
            trie.add(i);
        trie.cnt = 0;
        trie.traversal();
    }
};

template<> struct Trie<const char*> {
    vector<char[max(sizeof(Transition), max(sizeof(Elem), sizeof(Data)))]> v;
    vector<const char*> &a, ca;
    int maxl, cnt;
    Trie(vector<const char*> &a, size_t as) : v(as), a(a), ca(a), cnt(0) {
        for (int i = 0; i < v.size(); ++i)
            vE(i).pdata = vE(i).ts = -1;
    }
    void newe(Elem &e, int index) {
        int tp = ++cnt;
        vD(tp).next = e.pdata;
        e.pdata = tp;
        vD(tp).data = index;
    }
    void add(int index, int d = 0, int ce = 0) {
        unsigned char tc = ca[index][d];
        if (tc == 0) {
            newe(vE(ce), index);
            return;
        }
        if (vE(ce).ts < 0) {
            vE(ce).ts = ++cnt;
            vT(vE(ce).ts).c = tc;
            vT(vE(ce).ts).t = ++cnt;
            vT(vE(ce).ts).next = -1;
            add(index, d + 1, cnt);
        } else {
            int p = vE(ce).ts, pp = p;
            while (p >= 0 && vT(p).c < tc) {
                pp = p;
                p = vT(p).next;
            }
            if (p < 0) {
                p = vT(pp).next = ++cnt;
                vT(p).next = -1;
                vT(p).c = tc;
                vT(p).t = ++cnt;
                add(index, d + 1, cnt);
            } else if (vT(p).c == tc)
                add(index, d + 1, vT(p).t);
            else if (p != pp) {
                int t = ++cnt;
                vT(t).next = p;
                vT(pp).next = t;
                vT(t).c = tc;
                vT(t).t = ++cnt;
                add(index, d + 1, cnt);
            } else {
                pp = vE(ce).ts = ++cnt;
                vT(pp).next = p;
                vT(pp).c = tc;
                vT(pp).t = ++cnt;
                add(index, d + 1, cnt);
            }
        }
    }
    void traversal(int ce = 0) {
        int d = vE(ce).pdata;
        while (d >= 0) {
            a[cnt++] = ca[vD(d).data]; 
            d = vD(d).next;
        }
        int p = vE(ce).ts;
        while (p >= 0) {
            traversal(vT(p).t);
            p = vT(p).next;
        }
    }
    static void sort(vector<const char*> &a) {
        size_t l = 0;
        for (int i = 0; i < a.size(); ++i)
            l += strlen(a[i]);
        Trie<const char*> trie(a, 2*l + a.size() + 1);
        for (int i = 0; i < a.size(); ++i)
            trie.add(i);
        trie.cnt = 0;
        trie.traversal();
    }
};

