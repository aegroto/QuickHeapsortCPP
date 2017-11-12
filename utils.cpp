#ifndef UTILS_IN
#define UTILS_IN

/*****************/
/** VERIFY SORT **/
/*****************/

bool verifySort(int* A, int n) {
    for(int i = 1; i < n; ++i)
        if(A[i] < A[i-1])
            return false;
    return true;        
}

#endif