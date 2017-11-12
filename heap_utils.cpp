#ifndef HEAP_UTILS_IN
#define HEAP_UTILS_IN

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

inline unsigned int leftChild(int i) {
    return (2*i) + 1;
}

inline unsigned int rightChild(int i) {
    return (2*i) + 2;
}

inline unsigned int parent(int i) {
    return (i-1) / 2;
}

/***********************/
/** BUILDING MAX HEAP **/
/***********************/

void maxHeapify(int* A, int i, int n) {
    int l = leftChild(i),
        r = rightChild(i),
        largest = -1;

    if(l < n and A[l] > A[i])
        largest = l;
    else
        largest = i;
    
    if(r < n and A[r] > A[largest]) 
        largest = r;
    
    if(largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(A, largest, n);
    }
}

void buildMaxHeap(int* A, int n) {
    for(int i = n/2; i >= 0; --i)
        maxHeapify(A, i, n);
}

/***********************/
/** BUILDING MIN HEAP **/
/***********************/

void minHeapify(int* A, int i, int n) {
    int l = leftChild(i),
        r = rightChild(i),
        smallest = -1;

    if(l < n and A[l] < A[i])
        smallest = l;
    else
        smallest = i;
    
    if(r < n and A[r] < A[smallest]) 
        smallest = r;
    
    if(smallest != i) {
        swap(A[i], A[smallest]);
        minHeapify(A, smallest, n);
    }
}

void buildMinHeap(int* A, int n) {
    for(int i = n/2; i >= 0; --i)
        minHeapify(A, i, n);
}

/********************/
/** VERIFYING HEAP **/
/********************/

bool verifyMaxHeap(int* A, int n) {
    for(int i = 1; i < n; ++i)
        if(A[parent(i)] < A[i]) {
            return false;
        }

    return true;
}

bool verifyMinHeap(int* A, int n) {
    for(int i = 1; i < n; ++i)
        if(A[parent(i)] > A[i]) {
            return false;
        }

    return true;
}

/********************/
/** TEST FUNCTIONS **/
/********************/

void maxHeapifyTest(int testArraySize, int tests) {
    int currentTests = 0;
    
    cout << "Launching a max heapify test on " << tests << " random arrays..." << endl;

    int* array = new int[testArraySize];
    int* heapifiedArray = new int[testArraySize];

    while(currentTests < tests) {
        for(int i = 0; i < testArraySize; ++i) {
            array[i] = rand() % 100;
            heapifiedArray[i] = array[i];
        }        

        buildMaxHeap(heapifiedArray, testArraySize);

        bool heapCorrectness = verifyMaxHeap(heapifiedArray, testArraySize);
        
        if(!heapCorrectness) {
            cout << endl << "Heap correctness: " <<  heapCorrectness << endl;

            cout << "Original array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << array[i] << " ";
            }   
            
            cout << "\nHeapified array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << heapifiedArray[i] << " ";
            }  

            cout << endl;
        }

        ++currentTests;

        delete[] array;
        delete[] heapifiedArray;
    }

    cout << "Done." << endl;
}

void minHeapifyTest(int testArraySize, int tests) {
    int currentTests = 0;
    
    cout << "Launching a min heapify test on " << tests << " random arrays..." << endl;

    int* array = new int[testArraySize];
    int* heapifiedArray = new int[testArraySize];

    while(currentTests < tests) {
        for(int i = 0; i < testArraySize; ++i) {
            array[i] = rand() % 100;
            heapifiedArray[i] = array[i];
        }        

        buildMinHeap(heapifiedArray, testArraySize);

        bool heapCorrectness = verifyMinHeap(heapifiedArray, testArraySize);
        
        if(!heapCorrectness) {
            cout << endl << "Heap correctness: " <<  heapCorrectness << endl;

            cout << "Original array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << array[i] << " ";
            }   
            
            cout << "\nHeapified array: ";
            for(int i = 0; i < testArraySize; ++i) {
                cout << heapifiedArray[i] << " ";
            }  

            cout << endl;
        }

        ++currentTests;

        delete[] array;
        delete[] heapifiedArray;
    }

    cout << "Done." << endl;
}

#endif