template <class T>
int cmpfunc(const void *a, const void *b) {
    T r = *(T*)a - *(T*)b;  //may be the overflow for int
    if (r < 0) return -1;
    return r > 0;
}

template<>
int cmpfunc<const char*>(const void *s1, const void *s2) {
    return strcmp(*(const char**)s1, *(const char**)s2);
}

long double convert(const char *s) {
    long double r = 0;
    for (int i = 0; s[i] && i < 8; ++i)
        r += s[i]*(1LLU << ((7 - i) << 3));
    return r;
}

long double operator-(const string &s1, const string &s2) {
    return convert(s1.c_str()) - convert(s2.c_str());
}

