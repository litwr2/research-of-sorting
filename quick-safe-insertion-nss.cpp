#define MEDIAN3
namespace SafeQuicksortWithInsertionSortNoSystemStack {
    int stack_sz, sp;
    void** stack, *gLBound, *gUBound;

    template <class T>
    void qsort_safe(T *pLBound, T *pUBound) {  //modified Hoare quicksort
        T *pi, *pj;
        T x;
loop:
        if (pUBound - pLBound <= 16) { // insertion sort on tiny array
            for (T *pi = pLBound + 1; pi <= pUBound; pi++)
                for (T *pj = pi; pj > pLBound && *pj < *(pj - 1); pj--)
                    swap(*(pj - 1), *pj);
            goto cont;
        }
loop2:
        if (sp == 0) {
           pLBound = (T*)gLBound;
           pUBound = (T*)gUBound;
           sp = stack_sz;
        }
        pi = pLBound;
        pj = pUBound;
        x = *(T*)(((size_t)pi + (size_t)pj)/2 & ~(sizeof(T*) - 1));
#ifdef MEDIAN3
        if (*pi < x) {  //median of 3
            if (x >= *pj)
                x = *pi < *pj ? *pj : *pi;
        } else
            if (x <= *pj)
                x = *pi < *pj ? *pi : *pj;
#endif
        do {
           while (*pi < x) ++pi;
           while (x < *pj) --pj;
           if (pi <= pj) {
              if (pi != pj) swap(*pi, *pj);
              ++pi;
              --pj;
           }
        }
        while (pi <= pj);
        if (pLBound < pj) {
            stack[--sp] = pUBound;
            stack[--sp] = pi;
            pUBound = pj;
            goto loop;
        }
        if (pi < pUBound) {
            stack[--sp] = pj;
            stack[--sp] = pLBound;
            pLBound = pi;
            goto loop;
        }
cont:
        if (sp != stack_sz) {
            pLBound = (T*)stack[sp++];
            pUBound = (T*)stack[sp++];
            goto loop;
        }
    }
    template <>
    void qsort_safe(const char **pLBound, const char **pUBound) {  //modified Hoare quicksort
        const char **pi, **pj;
        const char *x;
loop:
        if (pUBound - pLBound <= 16) { // insertion sort on tiny array
            for (const char **pi = pLBound + 1; pi <= pUBound; pi++)
                for (const char **pj = pi; pj > pLBound && strcmp(*pj, *(pj - 1)) < 0; pj--)
                    swap(*(pj - 1), *pj);
            goto cont;
        }
loop2:
        if (sp == 0) {
           pLBound = (const char**)gLBound;
           pUBound = (const char**)gUBound;
           sp = stack_sz;
        }
        pi = pLBound, pj = pUBound;
        x = *(const char**)(((size_t)pi + (size_t)pj)/2 & ~(sizeof(const char**) - 1));
#ifdef MEDIAN3
        if (strcmp(*pi, x) < 0) {  //median of 3
            if (strcmp(x, *pj) >= 0)
                x = strcmp(*pi, *pj) < 0 ? *pj : *pi;
        } else 
            if (strcmp(x, *pj) <= 0)
                x = strcmp(*pi, *pj) < 0 ? *pi : *pj;
#endif
        do {
           while (strcmp(*pi, x) < 0) ++pi;
           while (strcmp(x, *pj) < 0) --pj;
           if (pi <= pj) {
              if (pi != pj) swap(*pi, *pj);
              ++pi;
              --pj;
           }
        }
        while (pi <= pj);
        if (pLBound < pj) {
            stack[--sp] = pUBound;
            stack[--sp] = pi;
            pUBound = pj;
            goto loop;
        }
        if (pi < pUBound) {
            stack[--sp] = pj;
            stack[--sp] = pLBound;
            pLBound = pi;
            goto loop;
        }
cont:
        if (sp != stack_sz) {
            pLBound = (const char**)stack[sp++];
            pUBound = (const char**)stack[sp++];
            goto loop;
        }
    }

}
template <class T>
void qsort_safe_nss(vector<T> &a, int LBound, int UBound) {
    using namespace SafeQuicksortWithInsertionSortNoSystemStack;
    stack_sz = 2*(int)(log(UBound - LBound)/log(2) + 1);
    //stack_sz = 8*(int)(log(UBound - LBound));
    T *lbub[stack_sz];
    stack = (void**)lbub;
    sp = stack_sz;
    gLBound = &a[LBound];
    gUBound = &a[UBound];
    qsort_safe((T*)gLBound, (T*)gUBound);
}

