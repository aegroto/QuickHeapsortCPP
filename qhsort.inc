//DO NOT INCLUDE THIS FILE. Include "qhsort.h" instead.
//holds template definitions of qhsort.h to keep the header tidy



template<class T> size_t ReversePartition(T* A, int l, int r)
{
	int i = l;
	int j = r - 1;
	T pivot = A[(l+r)/2];
	swap(A[(l+r)/2], A[r]);
    while(i < j)
	{
		while(A[i] > pivot && i < r - 1) 
			i++;
		while(A[j] < pivot && j > i)
			j--;
        if(i < j)
		{
			swap(A[i], A[j]);
			i++;
			j--;
		}
	}
	
	int k = j;
	while(k < r && A[k] > pivot)
		k++;
	swap(A[r], A[k]);
	return k;
}


template<class T> void QuickHeapsort(T* A, size_t sz)
{
	while (sz > 5)
	{
		size_t m = ReversePartition(A, 0, sz - 1);
		
		if(m <= (sz-1) / 2) 
		{
			ExternalSwapMaxHeapsort(A, A + (sz - m), m);
			swap(A[m], A[sz - m-1]);
			sz = sz - m-1;
		} 
		else 
		{
			ExternalSwapMinHeapsort(A + m +1, A, sz - m -1);
			swap(A[m], A[sz - m -1]);
			A += sz - m;
			sz = m;
		}
	}
	
	for (size_t i = 1; i < sz; i++)
	{
		for (size_t j = i; j>0 && A[j-1]>A[j]; j--)
			swap(A[j],A[j-1]);
	} 
}

template<class T> void QuickHeapsortStepByStep(T* A, size_t sz)
{
	size_t originalSz = sz;
	T* ar = A;
	int sti = 0;
	bool* ordered = new bool[originalSz]; for (size_t i = 0; i < originalSz; i++) ordered[i]=false;
	while (sz > 5)
	{
		for (size_t i = 0; i < originalSz; i++) 
			if (ordered[i]) printf(GREEN "%d " RESET, ar[i]); 
			else printf("%d ", ar[i]);
		printf("\n");
		
		size_t m = ReversePartition(A, 0, sz - 1);
		
		for (size_t i = 0; i < originalSz; i++) 
		{ 
			if (ordered[i]) printf(GREEN "%d " RESET, ar[i]); 
			else if (i == sti+m)  printf(RED "%d " RESET, ar[i]); 
			else printf("%d ", ar[i]); 
		}
		printf("   after partition\n");
		
		printf("m=%d    sti=%d    sz=%d\n", (int)m, (int)sti, (int)sz);
		
		if(m <= (sz-1) / 2) 
		{
			ExternalSwapMaxHeapsort(A, A + (sz - m), m);
			for (size_t i = sti + sz - m-1; i < sti + sz; i++) ordered[i]=true;
			printf("work  %d-%d       heap  %d-%d\n\n", (int)(sti+sz-m), (int)(sti+sz), (int)(sti), (int)(sti+m));
			swap(A[m], A[sz - m-1]);
			sz = sz - m-1;
		} 
		else 
		{
			ExternalSwapMinHeapsort(A + m +1, A, sz - m -1);
			for (size_t i = sti; i <= sti + sz - m -1; i++) ordered[i]=true;
			swap(A[m], A[sz - m -1]);
			printf("work  %d-%d       heap  %d-%d\n\n", (int)(sti+m+1), (int)(sti+sz+1), (int)(sti), (int)(sti+sz-m-1));
			sti+=sz-m;
			A += sz - m;
			sz = m;
		}
	}
	for (size_t i = 1; i < sz; i++)
	{
		for (size_t j = i; j>0 && A[j-1]>A[j]; j--)
			swap(A[j],A[j-1]);
	} 
	delete[] ordered;
}
