/*
	This is an header only 'library' for heap manipulation.

*/

#ifndef HEAP_H
#define HEAP_H
#include <stddef.h>

//---------------------UTILS FUNCTIONS---------------------------------------------------------------------
//Finds the maximum between 3 variables of a generic type. Doesn't use additional stack memory. 2 Confronts.
template<class T> inline T max3(T i, T j, T k) { return i > j? (i > k? i: k): (j > k? j: k); }
//Finds the maximum between 3 variables of a generic type. Doesn't use additional stack memory. 2 Confronts.
template<class T> inline T min3(T i, T j, T k) { return i < j? (i < k? i: k): (j < k? j: k); }
//Finds the maximum between 3 elements in an array. Doesn't use additional stack memory. 2 Confronts.
template<class T> inline size_t max3_array(T* A, size_t i, size_t j, size_t k) { return A[i] > A[j]? (A[i] > A[k]? i: k): (A[j] > A[k]? j: k); }
//Finds the maximum between 3 elements in an array. Doesn't use additional stack memory. 2 Confronts.
template<class T> inline size_t min3_array(T* A, size_t i, size_t j, size_t k) { return A[i] < A[j]? (A[i] < A[k]? i: k): (A[j] < A[k]? j: k); }

//Swaps two elements in an array. Standard swap implementation. I do not use std::swap since it varies between
//c++ versions (in c++ 14 it has specific requirements).
template<class T> inline void swap(T& a, T& b) { T c = a; a = b; b = c; }

// Gets the index of the left child of the i-th node. 
inline size_t heap_left(size_t i) { return (i<<1); }
//Gets the index of the right child of the i-th node.
inline size_t heap_right(size_t i) { return (i<<1)|1; }
//Gets the index of the parent of the i-th node.
inline size_t heap_parent(size_t i) { return i>>1; }
//---------------------------------------------------------------------------------------------------------


//--------------HEAP FUNCTIONS-----------------------------------------------------------------------------
//These functions allow to build&use a heap without any data structure.
template <class T> void MaxHeapify(T* A, size_t sz, size_t i);
template <class T> void MinHeapify(T* A, size_t sz, size_t i);
template <class T> void BuildMaxHeap(T* A, size_t sz);
template <class T> void BuildMinHeap(T* A, size_t sz);
template <class T> inline T MaxHeapMaximum(T* A) { return A[0]; }
template <class T> inline T MinHeapMinimum(T* A) { return A[0]; }

template <class T> size_t ExternalMaxSpecialLeaf(T* A, size_t sz);
template <class T> size_t ExternalMinSpecialLeaf(T* A, size_t sz);
template <class T> void ExternalHeapsort(T* A, T* Ext, size_t sz, T min); 
template <class T> void ExternalSwapMaxHeapsort(T* A, T* Ext, size_t sz); 
template <class T> void ExternalSwapMinHeapsort(T* A, T* Ext, size_t sz); 

template <class T> void Heapsort(T* A, size_t sz);
//---------------------------------------------------------------------------------------------------------


//This class represents a heap. Holds size and the array in its fields to
//avoid to pass it as a parameter to the functions (saves a lot of
//stack space in recursive MaxHeapify calls) (in modern machines 16 bytes per call)
template<class T> class heap
{
	T* data;
	size_t size;
	
public:
	heap(T* p, size_t sz);
	~heap();
	
	void MaxHeapify(size_t i);
	void MinHeapify(size_t i);
	void BuildMaxHeap();
	void BuildMinHeap();
	void Heapsort();
	
	inline T* getData() { return data; }
	inline size_t getHeapSize() { return size; }
	
};

//to keep the header file tiny and clear, all template definitions are in this file.
#include "heap.inc"

#endif