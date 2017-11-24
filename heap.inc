//DO NOT INCLUDE THIS FILE. Include "head.h" instead.
//holds template definitions of head.h to keep the header tidy


//-------------------TEMPLATE DEFINITIONS--------------------------------------
//Unfortunately template definitions of global functions must stay in the header file, unless things.

template <class T> void MaxHeapify(T* A, size_t sz, size_t i)
{
	size_t largest = i;
	size_t l = heap_left(i); size_t r = l+1; 
	if (l <= sz && A[l] > A[largest]) largest=l;
	if (r <= sz && A[r] > A[largest]) largest=r;
	if (largest != i)
	{
		swap(A[i], A[largest]);
		MaxHeapify(A, sz, largest);
	}
}

template <class T> void MinHeapify(T* A, size_t sz, size_t i)
{
	size_t smallest = i;
	size_t l = heap_left(i); size_t r = l+1; 
	if (l <= sz && A[l] < A[smallest]) smallest=l;
	if (r <= sz && A[r] < A[smallest]) smallest=r;
	if (smallest != i) 
	{
		swap(A[i], A[smallest]);
		MinHeapify(A, sz, smallest);
	}
}
template <class T> void BuildMaxHeap(T* A, size_t sz)
{
	for (int i = heap_parent(sz); i > 0; i--)
		MaxHeapify(A, sz, i);
}
template <class T> void BuildMinHeap(T* A, size_t sz)
{
	for (int i = heap_parent(sz); i > 0; i--)
		MinHeapify(A, sz, i);
}

template <class T> size_t ExternalMaxSpecialLeaf(T* A, size_t sz)
{
	size_t i = 2;
	while(i < sz) 
	{
		if(A[i] <= A[i+1]) i++;
		swap(A[heap_parent(i)], A[i]);
		i = heap_left(i);
	}
	
	if(i == sz) 
	{
		swap(A[heap_parent(i)], A[i]);
		i = heap_left(i);
	}

	return i>>1;
}

template <class T> size_t ExternalMinSpecialLeaf(T* A, size_t sz)
{
	size_t i = 2;
	while(i < sz) 
	{
		if(A[i] > A[i+1]) i++;
		swap(A[heap_parent(i)], A[i]);
		i = heap_left(i);
	}
	
	if(i == sz) 
	{
		swap(A[heap_parent(i)], A[i]);
		i = heap_left(i);
	}
	return i>>1;
}

template <class T> void ExternalHeapsort(T* _A, T* Ext, size_t sz, T min)
{
	T* A = _A - 1;

	BuildMaxHeap(A, sz);
	for(int j = sz; j > 0; j--)
	{
		Ext[j] = A[1];
		A[ExternalMaxSpecialLeaf(A,sz)] = min;
	}
}


template <class T> void ExternalSwapMaxHeapsort(T* _A, T* _Ext, size_t sz)	
{
	T* A = _A - 1;
	T* Ext = _Ext - 1;

	BuildMaxHeap(A, sz);
	for(int j = sz; j > 1; j--)
	{
		T temp = Ext[j];
		Ext[j] = A[1];
		A[ExternalMaxSpecialLeaf(A,sz)] = temp;
	}
}

template <class T> void ExternalSwapMinHeapsort(T* _A, T* _Ext, size_t sz)
{
	T* A = _A - 1;
	T* Ext = _Ext - 1;

	BuildMinHeap(A, sz);
	for(size_t j = 1; j < sz; j++)
	{
		T temp = Ext[j];
		Ext[j] = A[1];
		A[ExternalMinSpecialLeaf(A,sz)] = temp;
	}
}

template <class T> void Heapsort(T* _A, size_t sz)
{
	T* A = _A - 1;

	BuildMaxHeap(A, sz);
	for (size_t i = sz; i > 1; i--)
	{
		swap(A[1], A[i]);
		sz--;
		MaxHeapify(A, sz, 1);
	}
}

//--------------------------------------------------------------------------------------

//---------------HEAP CLASS IMPLEMENTATIONS---------------------------------------------
//And also for the class

template<class T> heap<T>::heap(T* p, size_t sz)
{
	data = p - 1;
	size = sz;
}

template<class T> heap<T>::~heap()
{
}

template <class T> void heap<T>::MaxHeapify(size_t i)
{
	size_t largest = i;
	size_t l = heap_left(i); size_t r = l | 1; 
	if (l <= size && data[l] > data[largest]) largest=l;
	if (r <= size && data[r] > data[largest]) largest=r;
	if (largest != i)
	{
		swap(data[i], data[largest]);
		MaxHeapify(largest);
	}
}

template <class T> void heap<T>::MinHeapify(size_t i)
{
	size_t smallest = i;
	size_t l = heap_left(i); size_t r = l | 1; 
	if (l < size && data[l] < data[smallest]) smallest=l;
	if (r < size && data[r] < data[smallest]) smallest=r;
	if (smallest != i)
	{
		swap(data[i], data[smallest]);
		MaxHeapify(smallest);
	}
}

template <class T> void heap<T>::BuildMaxHeap()
{
	for (int i = heap_parent(size); i > 1; i--)
		MaxHeapify(i);
}

template <class T> void heap<T>::BuildMinHeap()
{
	for (int i = heap_parent(size); i > 1; i--)
		MinHeapify(i);
}

template <class T> void heap<T>::Heapsort()
{
	BuildMaxHeap();
	size_t prevSize = size;
	for (size_t i = size-1; i >= 1; i--)
	{
		swap(data[0], data[i]);
		size--;
		MaxHeapify(0);
	}
	size = prevSize;
}
//----------------------------------------------------------------------------
