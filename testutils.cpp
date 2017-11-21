#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "testutils.h"
#include "heap.h"
#include "qhsort.h"
#include "escape_sequences.h"

void HeapTester::randFillIntArray(int* p, size_t n, int lowLimit, int upLimit)
{
	upLimit++;
	for (size_t i = 0; i < n; i++)
		p[i] = rand()%(upLimit) + lowLimit;
}

void HeapTester::randFillFloatArray(float* p, size_t n, float lowLimit, float upLimit)
{
	for (size_t i = 0; i < n; i++)
		p[i] = ((float)rand()/RAND_MAX) * (upLimit-lowLimit) + lowLimit;
}

bool HeapTester::revpartitionCheck(int* p, size_t n, size_t pivot)
{
	for (size_t i = 0; i < n; i++) 
		if ((i < pivot && p[i]<p[pivot]) || (i > pivot && p[i]>p[pivot])) return false; 
	return true;
}

bool HeapTester::sortCheck(int* p, size_t n)
{ 
	for (size_t i = 0; i < n-1; i++) if (p[i] > p[i+1]) return false; 
	return true;
}

HeapTester::HeapTester()
{
}

HeapTester::~HeapTester()
{
}

void HeapTester::VerifyHeapsortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize)
{
	int currentTests = 0;
    printf("Launching an heapsort test on %d random arrays...  ", testsNumber);

	int* array = new int[maxArraySize];
	int* originalArray = new int[maxArraySize];

	while(currentTests < testsNumber) 
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz, 0, 99);
		for(int i = 0; i < sz; ++i) originalArray[i]=array[i];
        
		Heapsort(array, sz);

		if(!sortCheck(array, sz)) 
		{
			printf(RED "\nSort Check Failed :(\n"RESET);
            
			printf("Original array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", originalArray[i]); printf("\n");
            
			printf("Output array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", array[i]); printf("\n");
			
			break;
		}
		
		currentTests++;
	}
	
	delete[] array;
	delete[] originalArray;
	printf("Done\n");
}

void HeapTester::VerifyQuickHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize)
{
	size_t currentTests = 0;
    	printf("Launching a QuickHeapsort test on %d random arrays...  ", testsNumber);

	int* array = new int[maxArraySize];
	int* originalArray = new int[maxArraySize];
	
	while(currentTests < testsNumber) 
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz, 0, 99);
		for(int i = 0; i < sz; ++i) originalArray[i]=array[i];
		
		QuickHeapsort(array, sz);

		if(!sortCheck(array, sz)) 
		{
			printf(RED "\nSort Check Failed :(\n"RESET);
            
			printf("Original array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", originalArray[i]); printf("\n");
            
			printf("Output array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", array[i]); printf("\n");
			
			break;
		}
		
		currentTests++;
	}
	
	delete[] array;
	delete[] originalArray;
	printf("Done\n");
}

void HeapTester::VerifyExternalHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize)
{
	int currentTests = 0;
    printf("Launching an external max heapsort test on %d random arrays...  ", testsNumber);

	int* array = new int[maxArraySize];
	int* originalArray = new int[maxArraySize];

	while(currentTests < testsNumber) 
	{		
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz, 0, 99);
		for(int i = 0; i < sz; ++i) originalArray[i]=array[i];
        
		int* extArray = new int[sz];
		ExternalHeapsort(array, extArray, sz, INT_MIN);

		if(!sortCheck(extArray, sz)) 
		{
			printf(RED "\nSort Check Failed :(\n"RESET);
            
			printf("Original array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", originalArray[i]); printf("\n");
            
			printf("Output array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", extArray[i]); printf("\n");
			
			delete[] extArray;
			break;
		}
		delete[] extArray;
		currentTests++;
	}
	
	delete[] array;
	delete[] originalArray;
	printf("Done\n");
}

void HeapTester::VerifyExternalSwapHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize)
{
	int currentTests = 0;
    printf("Launching an external (swap) max heapsort test on %d random arrays...  ", testsNumber);

	int* array = new int[maxArraySize];
	int* originalArray = new int[maxArraySize];

	while(currentTests < testsNumber) 
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz, 0, 99);
		for(int i = 0; i < sz; ++i) originalArray[i]=array[i];
        
		int* extArray = new int[sz];
		
		for (int i = 0; i < sz; i++) extArray[i] = -1;
		ExternalSwapMaxHeapsort(array, extArray, sz);
		if(!sortCheck(extArray, sz)) 
		{
			printf(RED "\nSort Check Failed (External Max Heapsort) :(\n"RESET);
            
			printf("Original array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", originalArray[i]); printf("\n");
            
			printf("Output array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", extArray[i]); printf("\n");
			
			delete[] extArray;
			break;
		}
		
		for (int i = 0; i < sz; i++) extArray[i] = 100;
		ExternalSwapMinHeapsort(array, extArray, sz);
		if(!sortCheck(extArray, sz)) 
		{
			printf(RED "\nSort Check Failed (External Min Heapsort) :(\n"RESET);
            
			printf("Original array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", array[i]); printf("\n");
            
			printf("Output array: ");
			for(int i = 0; i < sz; ++i) printf("%2d ", extArray[i]); printf("\n");
			
			delete[] extArray;
			break;
		}
		delete[] extArray;
		currentTests++;
	}
	
	delete[] array;
	delete[] originalArray;
	printf("Done\n");
}

void HeapTester::VerifyReversePartitionIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize)
{
	int currentTests = 0;
    
	printf("Launching a reverse partition test on %d random arrays...", testsNumber);

	int* array = new int[maxArraySize];
	int* originalArray = new int[maxArraySize];

    while(currentTests < testsNumber) 
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz, 0, 99);
		for(int i = 0; i < sz; ++i) originalArray[i]=array[i];

        size_t reversedPivotIndex = ReversePartition(array, 0, sz-1);
        if(!revpartitionCheck(array, sz, reversedPivotIndex))
		{
            printf(RED "\nPartition Test Failed :(\n"RESET);
            
			printf("Original array: ");
			for(size_t i = 0; i < sz; ++i) printf("%2d ", originalArray[i]); printf("\n");
            
			printf("Output array: ");
			for(size_t i = 0; i < sz; ++i) 
				if (i == reversedPivotIndex) printf(RED "%2d " RESET, array[i]);
				else printf("%2d ", array[i]); printf("\n");
			
			break;
        }

        ++currentTests;
    }
	
	delete[] array;
	delete[] originalArray;
	printf("Done\n");
}

double HeapTester::BenchmarkDataStructureHS(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		heap<int> h(array, sz);
		clock_t start = clock();
		h.Heapsort();
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

double HeapTester::BenchmarkHeapsort(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		clock_t start = clock();
		Heapsort(array, sz);
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

double HeapTester::BenchmarkQuickHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		clock_t start = clock();
		QuickHeapsort(array, sz);
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

double HeapTester::BenchmarkExternalHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	int* extArray = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		clock_t start = clock();
		ExternalHeapsort(array, extArray, sz, INT_MIN);
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	delete[] extArray;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

double HeapTester::BenchmarkExternalSwapHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	int* extArray = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		clock_t start = clock();
		ExternalSwapMaxHeapsort(array, extArray, sz);
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	delete[] extArray;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

double HeapTester::BenchmarkReversePartition(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	clock_t totalClock = 0;
	int* array = new int[maxArraySize];
	for (size_t currentTests = 0; currentTests<testNumber; currentTests++)
	{
		size_t sz = rand()%(maxArraySize+1-minArraySize) + minArraySize;
		randFillIntArray(array, sz);
		clock_t start = clock();
		ReversePartition(array, 0, sz-1);
		clock_t end = clock();
		totalClock += end-start;
	}
	delete[] array;
	double totalMs = (double)totalClock * 1000.0 / CLOCKS_PER_SEC;
	return totalMs / testNumber;
}

void HeapTester::VerifyEverything(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	VerifyHeapsortIntegrity(testNumber, minArraySize, maxArraySize);
	VerifyExternalHeapSortIntegrity(testNumber, minArraySize, maxArraySize);
	VerifyExternalSwapHeapSortIntegrity(testNumber, minArraySize, maxArraySize);
	VerifyQuickHeapSortIntegrity(testNumber, minArraySize, maxArraySize);
	VerifyReversePartitionIntegrity(testNumber, minArraySize, maxArraySize);
}

void HeapTester::BenchmarkEverything(size_t testNumber, size_t minArraySize, size_t maxArraySize)
{
	const int algorithmsCount = 4;
	char algorithmsNames[algorithmsCount][30] = { "HeapSort", "DSHeapSort", "ExternalHeapSort", "QuickHeapSort" };
	double executionTimes[algorithmsCount];
	
	double revPartitionTime = BenchmarkReversePartition(testNumber, minArraySize, maxArraySize);
	executionTimes[0] = BenchmarkHeapsort(testNumber, minArraySize, maxArraySize);
	executionTimes[1] = BenchmarkDataStructureHS(testNumber, minArraySize, maxArraySize);
	executionTimes[2] = BenchmarkExternalHeapSort(testNumber, minArraySize, maxArraySize);
	executionTimes[3] = BenchmarkQuickHeapSort(testNumber, minArraySize, maxArraySize);
	
	printf("Reverse partition took an average of %.2lfms \n", revPartitionTime);
	for (size_t i = 0; i < algorithmsCount; i++) printf("%s took an average of %.2lfms \n", algorithmsNames[i],  executionTimes[i]);
	
	printf("\nComparation table\n|%30s|", " ");
	for (size_t i = 0; i < algorithmsCount; i++) printf("%-30s|", algorithmsNames[i]);
	printf("\n");
	for (size_t i = 0; i < algorithmsCount; i++)
	{
		printf("|%-30s|", algorithmsNames[i]);
		for (size_t j = 0; j < algorithmsCount; j++)
		{
			char buf[30]; memset(buf, 0, 30);
			double deltaTime = executionTimes[j]-executionTimes[i];
			if (j != i)
				sprintf(buf, "%.2lf (%.2lf%%)", deltaTime, (executionTimes[j]/executionTimes[i])*100.0-100.0);
			int bufLen = strlen(buf);
			int spacing = (30-bufLen)/2;
			
			char finalBuf[30]; memset(finalBuf, 0, 30);
			for (int i = 0; i < 30; i++)
			{
				if (i<spacing) finalBuf[i] = ' ';
				else finalBuf[i] = buf[i-spacing];
			}
			
			if (deltaTime > 0)
				printf(GREEN "%-30s" RESET "|", finalBuf);
			else printf(RED "%-30s" RESET "|", finalBuf);
		}
		printf("\n");
	}
	
	
}


