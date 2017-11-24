#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"
#include "qhsort.h"
#include "testutils.h"


int main(int argc, char** argv)
{
	int tstArraySz = 200000;
	int tstCnt = 100;
	if (argc == 2)
	{
		tstArraySz = atoi(argv[1]);
	}
	else if (argc == 3)
	{
		tstArraySz = atoi(argv[1]);
		tstCnt = atoi(argv[2]);
	}
	else 
	{
		printf("Invalid Parameters.\nUsage: ./qhsort testArraySize testsNumber\n");
		return 0;
	}
	srand(time(NULL));
	
	HeapTester t; 
	t.VerifyHeapsortIntegrity(tstCnt, tstArraySz, tstArraySz);
	t.VerifyExternalHeapSortIntegrity(tstCnt, tstArraySz, tstArraySz);
	/*t.VerifyEverything(tstCnt, tstArraySz, tstArraySz);
	printf("\n");
	t.BenchmarkEverything(tstCnt, tstArraySz, tstArraySz); */
}
