#if !defined(CSTRINGS) && !defined(CSTRINGS_SHORT) && !defined(CSTRINGS_LONG)
#include "opt/SortAlgo/SortAlgo-m.cpp"  //sources are taken from https://github.com/chromi/sound-of-sorting/tree/master/src
                                        //they were modified a bit - all hooks for visualisation are removed

//shellsorts are still not added
template<class T>
void insertionsort_sa(vector<T> &a) {  //no in nsort
    SortArray1<T> a1(a);
    InsertionSort(a1);
}

template<class T>
void insertionsort2_sa(vector<T> &a) {  //no in nsort
    SortArray1<T> a1(a);
    InsertionSort2(a1);
}

template<class T>
void bininsertionsort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BinaryInsertionSort(a1);
}

template<class T>
void mergesort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    MergeSort(a1);
}

template<class T>
void mergesort_iter_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    MergeSortIterative(a1);
}

template<class T>
void mergesortInPlace_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    MergeSortInPlace(a1);
}

template<class T>
void mergesortSemiInPlace_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    MergeSortSemiInPlace(a1);
}

template<class T>
void cataMergesort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    CataMergeSort(a1);
}

template<class T>
void cataMergesortStable_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    CataMergeSortStable(a1);
}

template<class T>
void quicksort_lr_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    QuickSortLR(a1);
}

template<class T>
void quicksort_ll_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    QuickSortLL(a1);
}

template<class T>
void quicksort_3lr_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    QuickSortTernaryLR(a1);
}

template<class T>
void quicksort_3ll_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    QuickSortTernaryLL(a1);
}

template<class T>
void quicksort_2p_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    QuickSortDualPivot(a1);
}

template<class T>
void introsort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    IntroSort(a1);
}

template<class T>
void introsort2_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    IntroSortDual(a1);
}

template<class T>
void introsort2_stb_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    IntroSortDualStable(a1);
}

template<class T>
void septenaryquick_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SeptenaryQuickSort(a1);
}

template<class T>
void septenaryquick_stb_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SeptenaryStableQuickSort(a1);
}

template<class T>
void cocktailshaker_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    CocktailShakerSort(a1);
}

template<class T>
void gnome_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    GnomeSort(a1);
}

template<class T>
void comb_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    CombSort(a1);
}

template<class T>
void oddeven_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    OddEvenSort(a1);
}

template<class T>
void heap_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    HeapSort(a1);
}

#if defined(INT32) || defined(INT64) || defined(INT128)
template<class T>
void radix_msd_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    RadixSortMSD(a1);
}

template<class T>
void radix_lsd_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    RadixSortLSD(a1);
}
#endif

template<class T>
void bogo_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BogoSort(a1);
}

template<class T>
void bozo_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BozoSort(a1);
}

template<class T>
void stooge_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    StoogeSort(a1);
}

template<class T>
void slowsort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SlowSort(a1);
}

template<class T>
void cyclesort_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    CycleSort(a1);
}

template<class T>
void bitonic_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BitonicSort(a1);
}

template<class T>
void bitonic_nw_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BitonicSortNetwork(a1);
}

template<class T>
void batcher_nw_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    BatcherSortNetwork(a1);
}

template<class T>
void smooth_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SmoothSort(a1);
}

template<class T>
void splay_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SplaySort(a1);
}

template<class T>
void splayshake_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SplayShakeSort(a1);
}

template<class T>
void splaymerge_sa(vector<T> &a) {
    SortArray1<T> a1(a);
    SplayMergeSort(a1);
}
#endif

