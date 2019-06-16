#define STRING_BASE 1'000'000'000

template<class T> T cnv(int n) {
    return {n};
}

template<> string cnv(int n) {
    return to_string(n + STRING_BASE).c_str();
}

template<> const char *cnv(int n) {
    char *s = new char [to_string(n).length() + 1];
    strcpy(s, to_string(n + STRING_BASE).c_str());
    return s;
}

template<class T> T nxt(T n) {
    return {n + 1};
}

template<> string nxt(string n) {
    return to_string(stoi(n) + 1).c_str();
}

template<> const char *nxt(const char *n) {
    int t = atoi(n) + 1;
    delete n;
    char *s = new char [to_string(t).length() + 1];
    strcpy(s, to_string(t).c_str());
    return s;
}

template<class T>
void insert2(vector<T> &v, list<T> &l, int final = 0) {
	v.push_back(nxt(v.back()));
	l.push_back(l.front());
	l.erase(l.begin());
	if (!final) {
		l.push_back(v.back());
                v.back() = nxt(v.back());
        }
}

template<>
void insert2(vector<const char*> &v, list<const char*> &l, int final) {
        const char *s = v.back();
        const char *cs = new char [strlen(s) + 1];
        strcpy((char*)cs, s);
	v.push_back(nxt(cs));
	l.push_back(l.front());
	l.erase(l.begin());
	if (!final) {
                s = v.back();
		l.push_back(s);
                cs = new char [strlen(s) + 1];
                strcpy((char*)cs, s);
                v.back() = nxt(cs);
        }
}

template<class T>
void fill_for_quadratic_qsort1(vector<T> &v) {
	v = {cnv<T>(1), cnv<T>(3)};
	list<T> l{cnv<T>(2), cnv<T>(0)};
	for (int i = 0; i < (SS - 4)/2; i++)
		insert2(v, l);
	if (SS%2)
		insert2(v, l, 1);
	v.insert(v.end(), l.begin(), l.end());     
}

template<class T> void fill(vector<T> &v) {
#ifdef SLOW_QSORT1_ORDER
    fill_for_quadratic_qsort1(v);
#else
    for (int i = 0; i < SS; i++)
#ifdef RANDOM_ORDER
#ifdef STRINGS_SHORT
       v.push_back([]{ string s = ""; int lim = rand()%16 + 1; for (int i = 0; i < lim; ++i) s += ' ' + rand()%94; return s;}());
#elif defined(STRINGS)
       v.push_back([]{ string s = ""; int lim = rand()%256 + 1; for (int i = 0; i < lim; ++i) s += ' ' + rand()%94; return s;}());
#elif defined(STRINGS_LONG)
       v.push_back([]{
           static uint64_t sum = 0, cnt = 0;
           string s ="";
           int lim = rand()%(1 << 20) + 1;
           if (cnt++ >= SS*256/((1 << 20) - 256) && sum + lim > 512*cnt)
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
           if (cnt++ >= SS*256/((1 << 20) - 256) && sum + lim > 512*cnt)
               lim = min(lim, rand()%256 + 1);
           sum += lim;
           char *s = new char[lim + 1];
           int i = 0;
           for (; i < lim; ++i)
               s[i] = ' ' + rand()%94;
           s[i] = 0;
           return s;}());
#else
       v.push_back({X{1}*abs(rand()*rand())});
#endif
#elif defined(ASCENDED_ORDER) || defined(ASCENDED_RANDOM_ORDER)
       v.push_back(cnv<T>(i));
#elif defined(DESCENDED_ORDER)
       v.push_back(cnv<T>(SS - i));
#elif defined(LOW_VARIATION_ORDER)
       v.push_back(cnv<T>(rand()%LOW_VARIATION_CONST));
#else
#error NO ORDER IS SET
#endif
#endif

#ifdef ASCENDED_RANDOM_ORDER
    for (int i = 0; i < SS/100; i++)
        v[rand()%SS] = cnv<T>(rand()%STRING_BASE);
#endif
}

