#include <stddef.h>
#include <time.h>
#include <limits.h>

class HeapTester
{
	void randFillIntArray(int* p, size_t n, int lowLimit=INT_MIN, int upLimit=INT_MAX);
	void randFillFloatArray(float* p, size_t n, float lowLimit=0.0f, float upLimit=100.0f);
	bool sortCheck(int* p, size_t n);
	bool revpartitionCheck(int* p, size_t n, size_t pivot);
	
public:
	HeapTester();
	~HeapTester();
	
	void VerifyHeapsortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize);
	void VerifyQuickHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize);
	void VerifyExternalHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize);
	void VerifyExternalSwapHeapSortIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize);
	void VerifyReversePartitionIntegrity(size_t testsNumber, size_t minArraySize, size_t maxArraySize);
	
	double BenchmarkDataStructureHS(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	double BenchmarkHeapsort(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	double BenchmarkQuickHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	double BenchmarkExternalHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	double BenchmarkExternalSwapHeapSort(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	double BenchmarkReversePartition(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	
	void VerifyEverything(size_t testNumber, size_t minArraySize, size_t maxArraySize);
	void BenchmarkEverything(size_t testNumber, size_t minArraySize, size_t maxArraySize);
};