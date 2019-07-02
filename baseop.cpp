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
    return strcmp(*(const char**)s1, *(const char**)s2);
}

uint32_t convert(const char *s) {
    uint32_t r = 0;
    for (int i = 0; i < 4; ++i)
        r += s[i]*(1U << ((3 - i) << 3));
    return r;
}

uint32_t pchar_difference(const char *s1, const char *s2) {
    const size_t mbs = 4;
    char b[mbs] = {0};
    int i = 0, l1 = strlen(s1), l2 = strlen(s2), lmax = max(l1, l2), lmin = min(l1, l2);
    while (s1[i] == s2[i] && i < lmin) ++i;
    int p = i, sign = 0, u = 0;
    for (size_t k = 0; k < mbs; ++k) {
        int o1 = 0, o2 = 0, idx = p + mbs - k - 1;
        if (idx >= l1 && idx >= l2) { u++; continue; }
        if (idx < l1) o1 = s1[idx];
        if (idx < l2) o2 = s2[idx];
        b[mbs + u - k - 1] = o1 - o2 - sign;
        if (o1 < o2 + sign) sign = 1; else sign = 0;
    }
    return convert(b);
}

uint32_t operator-(const string &s1, const string &s2) {
    return pchar_difference(s1.c_str(), s2.c_str());
}

