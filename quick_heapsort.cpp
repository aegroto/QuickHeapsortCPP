#ifndef QUICK_HEAPSORT_IN
#define QUICK_HEAPSORT_IN

unsigned int choosePivotIndex(int* A, int l, int r) {
    return (l+r) / 2;
}

unsigned int reversePartition(int* A, int pivotIndex, int l, int r) {
    int i = l;
    int j = r - 1;

    int pivot = A[pivotIndex];

    swap(A[pivotIndex], A[r]);

    while(i < j) {
        while(A[i] > pivot && i < r - 1) 
            i++;
        while(A[j] < pivot && j > i)
            j--;

        if(i < j) {
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

void quickHeapsort(int* A, int n) {
    if(n > 5) {
        int pivotIndex = choosePivotIndex(A, 0, n - 1);

        cout << "\nSorting subarray: ";
        for(int i = 0; i < n; ++i)
            cout << A[i] << " ";
        cout << "|| ";

        int m = reversePartition(A, pivotIndex, 0, n - 1);

        for(int i = 0; i < n; ++i)
            cout << A[i] << " ";
        cout << "With m = " << m << " (" << A[m] << ") and n = " << n << endl;

        if(m <= (n+1) / 2) {
            qhsExternalMaxHeapsort(A, A + (n - m), m);
            swap(A[m], A[n - m - 1]);

            cout << "Sorted subarray: ";
            for(int i = 0; i < n; ++i)
                cout << A[i] << " ";
            cout << "(m <= n/2)" << endl;

            quickHeapsort(A, n - m - 1);
        } else {
            qhsExternalMinHeapsort(A + m + 1, A, n - m - 1);
            swap(A[m], A[n - m - 1]);

            cout << "Sorted subarray: ";
            for(int i = 0; i < n; ++i)
                cout << A[i] << " ";
            cout << "(m > n/2)" << endl;

            quickHeapsort(A + n - m, m);
        }
    } else {
        // TODO: implement a better sorting algorithm for a fixed number of elements (precisely 2,3,4 and 5)
        for(int i = 1; i < 5; ++i) {
            int key = A[i];
            int j = i-1;

            while(j >= 0 && key < A[j]) {
                A[j+1] = A[j];
                --j;
            }    

            A[j+1] = key;
        }
    }
}

/********************/
/** TEST FUNCTIONS **/
/********************/

void quickHeapsortTest(int testArraySize, int tests) {
    int currentTests = 0;
    
    cout << "Launching a QuickHeapsort test on " << tests << " random arrays..." << endl;

    int* array = new int[testArraySize];
    int* sortedArray = new int[testArraySize];

    while(currentTests < tests) {
        array[0] = 53; array[1] = 13; array[2] = 5;
        array[3] = 40;  array[4] = 67; array[5] = 76;
        array[6] = 79;  array[7] = 63; array[8] = 68;
        array[9] = 10;  array[10] = 68; array[11] = 30;
        array[12] = 28;  array[13] = 37; array[14] = 61; 

        for(int i = 0; i < testArraySize; ++i) {
            //array[i] = rand() % 100;
            sortedArray[i] = array[i];
        }
        /*for(int i = 0; i < testArraySize; ++i) {
            cout << array[i] << " ";
        }  
        cout << endl; */

        quickHeapsort(sortedArray, testArraySize);
        
        bool sortCorrectness = verifySort(sortedArray, testArraySize);
        
        if(!sortCorrectness) {
            cout << endl << "QuickHeapsort correctness: " <<  sortCorrectness << endl;

            cout << "Original array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << array[i] << " ";
            }   
            
            cout << "\nQHSorted array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << sortedArray[i] << " ";
            }  

            cout << endl;
        }

        ++currentTests;

        delete[] array;
        delete[] sortedArray;
    }

    cout << "Done." << endl;
}

bool verifyReversePartition(int* A, int pivotIndex, int l, int r) {
    int pivot = A[pivotIndex];

    for(int i = l; i <= r; ++i) {
        if(i < pivotIndex && A[i] < pivot || i > pivotIndex && A[i] > pivot)
            return false;
    }

    return true;
}

void reversePartitionTest(int testArraySize, int tests) {
    int currentTests = 0;
    
    cout << "Launching a reverse partition test on " << tests << " random arrays..." << endl;

    int* array = new int[testArraySize];
    int* partitionedArray = new int[testArraySize];

    while(currentTests < tests) {
        for(int i = 0; i < testArraySize; ++i) {
            array[i] = rand() % 100;
            partitionedArray[i] = array[i];
        }

        int pivotIndex = choosePivotIndex(array, 0, testArraySize - 1);
        int reversedPivotIndex = reversePartition(partitionedArray, pivotIndex, 0, testArraySize - 1);
        
        bool reversePartitionCorrectness = verifyReversePartition(partitionedArray, reversedPivotIndex, 0, testArraySize - 1);
        
        if(!reversePartitionCorrectness) {
            cout << endl << "Reverse partition correctness: " <<  reversePartitionCorrectness << endl;

            cout << "Original pivot: " << array[pivotIndex] << endl;
            cout << "Original array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << array[i] << " ";
            }   
            
            cout << "\nPartitioned array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << partitionedArray[i] << " ";
            }  

            cout << endl;
        }

        ++currentTests;

        delete[] array;
        delete[] partitionedArray;
    }

    cout << "Done." << endl;
}
#endif