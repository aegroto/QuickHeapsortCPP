#ifndef EXT_HEAPSORT_IN
#define EXT_HEAPSORT_IN

unsigned int maxSpecialLeaf(int* A, unsigned int n) {
    int i = 1;

    while(i < n - 1) {
        if(A[i] <= A[i+1]) 
            ++i;
        
        swap(A[parent(i)], A[i]);

        i = leftChild(i);
    }

    if(i == n - 1) {
        swap(A[parent(i)], A[i]);

        i = leftChild(i);
    }

    return i/2;
}

unsigned int minSpecialLeaf(int* A, unsigned int n) {
    int i = 1;

    while(i < n - 1) {
        if(A[i] > A[i+1]) 
            ++i;
        
        swap(A[parent(i)], A[i]);

        i = leftChild(i);
    }

    if(i == n - 1) {
        swap(A[parent(i)], A[i]);

        i = leftChild(i);
    }

    return i/2;
}

/********************************/
/** VANILLA EXTERNAL HEAPSORT **/
/********************************/

void externalMaxHeapsort(int* A, int* EXT, unsigned int n) {
    buildMaxHeap(A, n);

    for(int j = n - 1; j > -1; --j) {
        EXT[j] = A[0];
        int l = maxSpecialLeaf(A, n);
        A[l] = INT_MIN;
    }
}

void externalMinHeapsort(int* A, int* EXT, unsigned int n) {
    buildMinHeap(A, n);

    for(int j = 0; j < n; ++j) {
        EXT[j] = A[0];
        int l = minSpecialLeaf(A, n);
        A[l] = INT_MAX;
    }
}

/******************************/
/** QUICK HEAPSORT EXTENSION **/
/******************************/

void qhsExternalMaxHeapsort(int* A, int* EXT, unsigned int n) {
    buildMaxHeap(A, n);

    for(int j = n - 1; j > -1; --j) {
        int temp = EXT[j];
        EXT[j] = A[0];
        int l = maxSpecialLeaf(A, n);
        A[l] = temp;
    }
}

void qhsExternalMinHeapsort(int* A, int* EXT, unsigned int n) {
    buildMinHeap(A, n);

    for(int j = 0; j < n; ++j) {
        int temp = EXT[j];
        EXT[j] = A[0];
        int l = minSpecialLeaf(A, n);
        A[l] = temp;
    }
}

/********************/
/** TEST FUNCTIONS **/
/********************/

void externalHeapsortTest(int testArraySize, int tests) {
    int currentTests = 0;
    
    cout << "Launching an external heapsort test on " << tests << " random arrays..." << endl;

    int* array = new int[testArraySize];
    int* originalArray = new int[testArraySize];

    while(currentTests < tests) {
        for(int i = 0; i < testArraySize; ++i) {
            array[i] = rand() % 100;
            originalArray[i] = array[i];
        }     
        
        int* extArray = new int[testArraySize];
        externalMinHeapsort(array, extArray, testArraySize);

        bool sortCorrectness = verifySort(extArray, testArraySize);

        if(!sortCorrectness) {
            cout << endl << "Sort correctness: " <<  sortCorrectness << endl;
            
            cout << "Original array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << originalArray[i] << " ";
            }   
            
            cout << "\nSorted array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << extArray[i] << " ";
            }  

            cout << endl;
        }

        currentTests++;
    }

    cout << "Done." << endl;
}

#endif