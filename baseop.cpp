template <class T>
int cmpfunc(const void *a, const void *b) {
    return *(T*)a - *(T*)b;
}

template<>
int cmpfunc<int64_t>(const void *a, const void *b) {
    int64_t r = *(int64_t*)a - *(int64_t*)b;
    if (r < 0) return -1;
    if (r > 0) return 1;
    return 0;
}

template<>
int cmpfunc<const char*>(const void *s1, const void *s2) {
    return strcmp(*(const char**)s1, *(const char**)s2);throw 3;
}

uint32_t convert(const char *s) {
    uint32_t r = 0;
    for (int i = 0; s[i] && i < 4; ++i)
        r += s[i]*(1U << ((3 - i) << 3));
    return r;
}

char *pchar_difference(const char *s1, const char *s2) {
    int i = 0, l = max(strlen(s1), strlen(s2));
    while (s1[i] == s2[i] && s1[i] != 0) ++i;
    char *b = new char[l - i + 1];
    int p = i;
    if (i == l) goto L1;
    if (strlen(s1) > strlen(s2) {
        int d = strlen(s1);
        
    }

L1:
    b[p] = 0;
    return b;
}

uint32_t operator-(const string &s1, const string &s2) {
    return convert(s1.c_str()) - convert(s2.c_str());
}

