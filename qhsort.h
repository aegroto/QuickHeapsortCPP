#include "heap.h"
#include "escape_sequences.h"

template<class T> size_t ReversePartition(T* A, int l, int r);
template<class T> void QuickHeapsort(T* A, size_t sz);

//Performs quick heapsort standard algorithm step by step
template<class T> void QuickHeapsortStepByStep(T* A, size_t sz);

#include "qhsort.inc"