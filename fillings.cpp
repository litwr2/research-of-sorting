#define STRING_BASE 1'000'000'000    //10 digits

#if defined(STRINGS_SHORT) || defined(CSTRINGS_SHORT)
#define SL 6
#elif defined(STRINGS) || defined(CSTRINGS)
#define SL 246
#else
#define SL 502
#endif

template<class T> T cnv(int n) {
    return {n};
}

template<> string cnv(int n) {
    if (LOW_VARIATION_CONST == 0)
        return to_string(n + STRING_BASE) + string(rand()%SL + 1, 'A');
    return to_string(n + STRING_BASE);
}

template<> const char *cnv(int n) {
    unsigned r = rand()%SL + 1;
    unsigned l = to_string(n + STRING_BASE).length() + r + 1;
    char *s;
    if (LOW_VARIATION_CONST == 0) {
        s = new char [l];
        strcpy(s, to_string(n + STRING_BASE).c_str());
        strcat(s, string(r, 'A').c_str());
    } else {
        s = new char [l - r];
        strcpy(s, to_string(n + STRING_BASE).c_str());
    }
    return s;
}

template<class T> T nxt(T n) {
    return {n + 2};
}

template<> string nxt(string n) {
    return to_string(stoi(n) + 2) + string(rand()%SL + 1, 'A');
}

template<> const char *nxt(const char *n) {
    int t = atoi(n) + 2;
    unsigned r = rand()%SL + 1;
    unsigned l = to_string(t).length() + r + 1;
    char *s = new char [l];
    strcpy(s, to_string(t).c_str());
    strcat(s, string(r, 'A').c_str());
    return s;
}

template<class T>
void fill_for_quadratic_qsort_hoare(vector<T> &v) {
    v = {cnv<T>(1), cnv<T>(3), cnv<T>(5), cnv<T>(0), cnv<T>(2), cnv<T>(4)};
    v.resize(SS);
    for (int i = 3; i < SS/2; i++) {
	    v[2*i] = v[i];
        v[2*i + 1] = nxt(v[2*i - 1]);
        v[i] = cnv<T>(2*i + 1);
    }
}

int gena1(int j) {
    if ((j & 1) == 1) return j - 1;
    return gena1(j/2) + j;
}

int gena(int j, int i) {
    if (i == 0) return 0;
    if ((j - i & 1) == 0) return j - i;
    return gena1(j + i - 1 >> 1) + j - i + 1;
}

template<class T>
void fill_for_quadratic_qsort_hoare_l(vector<T> &v) {
    int sz = SS/2;
    v.resize(SS);
    for (int i = 0; i < sz; i++) {
        v[sz - i - 1] = cnv<T>(gena(sz, i));
        v[i + sz] = cnv<T>(2*i + 1);
    }
}

template<class T>
void fill_homebrew_randomly(vector<T> &v) {
    v.resize(SS);
    for (int i = 1; i < SS; i++)
        v[i] = (i >> 2 | (v[i - 1]  & 3) << 6) + i*i%43;
}

template<class T> void fill(vector<T> &v) {
#ifdef SLOW_QSORT_HOARE
    fill_for_quadratic_qsort_hoare(v);
#elif defined(SLOW_QSORT_HOARE_L)
    fill_for_quadratic_qsort_hoare_l(v);
#else
    for (int i = 0; i < SS; i++)
#ifdef RANDOM
#ifdef STRINGS_SHORT
       v.push_back([]{ string s = ""; int lim = rand()%16 + 1; for (int i = 0; i < lim; ++i) s += ' ' + rand()%94; return s;}());
#elif defined(STRINGS)
       v.push_back([]{ string s = ""; int lim = rand()%256 + 1; for (int i = 0; i < lim; ++i) s += ' ' + rand()%94; return s;}());
#elif defined(STRINGS_LONG)
       v.push_back([]{
           static uint64_t sum = 0, cnt = 0;
           string s ="";
           int lim = rand()%(1 << 20) + 1;
           if (cnt++ >= (size_t)SS*256/((1 << 20) - 256) && sum + lim > 512*cnt)
               lim = min(lim, rand()%256 + 1);
           sum += lim;
           for (int i = 0; i < lim; ++i)
               s += '@' + rand()%26;
           return s;}());
#elif defined(CSTRINGS_SHORT)
       v.push_back([]{ int lim = rand()%16 + 1; char *s = new char[lim + 1]; int i = 0; for (; i < lim; ++i) s[i] = ' ' + rand()%94; s[i] = 0; return s;}());
#elif defined(CSTRINGS)
       v.push_back([]{ int lim = rand()%256 + 1; char *s = new char[lim + 1]; int i = 0; for (; i < lim; ++i) s[i] = ' ' + rand()%94; s[i] = 0; return s;}());
#elif defined(CSTRINGS_LONG)
       v.push_back([]{
           static uint64_t sum = 0, cnt = 0;
           int lim = rand()%(1 << 20) + 1;
           if (cnt++ >= (size_t)SS*256/((1 << 20) - 256) && sum + lim > 512*cnt)
               lim = min(lim, rand()%256 + 1);
           sum += lim;
           char *s = new char[lim + 1];
           int i = 0;
           for (; i < lim; ++i)
               s[i] = ' ' + rand()%94;
           s[i] = 0;
           return s;}());
#else
       v.push_back({[]{ X v{rand()*rand()}; if (v < 0) return X{1}*-(v/2); return X{1}*v;}()});
#endif
#elif defined(ORDERED) || defined(PARTIALLY_ORDERED)
       v.push_back(cnv<T>(i));
#elif defined(REVERSED) || defined(PARTIALLY_REVERSED)
       v.push_back(cnv<T>(SS - i));
#elif LOW_VARIATION_CONST
       v.push_back(cnv<T>(rand()%LOW_VARIATION_CONST));
#else
#error NO ORDER IS SET
#endif
#endif

#if defined(PARTIALLY_ORDERED) || defined(PARTIALLY_REVERSED)
    for (int i = 0; i < SS/100; i++)
        v[rand()%SS] = cnv<T>(rand()%STRING_BASE);
#endif
}

