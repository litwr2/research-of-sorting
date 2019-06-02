template <class T>
int cmpfunc(const void *a, const void *b) {
#ifndef STRINGS
   return *(T*)a - *(T*)b;
#else
   return ((string*)a)->compare(*(string*)b);  //doesn't work
#endif
}

int cmpfunc_char(const void *s1, const void *s2) {
        return strcmp(*(const char**)s1, *(const char**)s2);
}

uint32_t convert(const char *s) {
    uint32_t r = 0;
    for (int i = 0; s[i] && i < 4; ++i)
        r += s[i]*(1U << ((3 - i) << 3));
    return r;
}

uint32_t operator-(const string &s1, const string &s2) {
    return convert(s1.c_str()) - convert(s2.c_str());
}

