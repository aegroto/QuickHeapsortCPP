#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

#include "utils.cpp"
#include "heap_utils.cpp"
#include "ext_heapsort.cpp"
#include "quick_heapsort.cpp"

int main() {
    srand(time(0));

    //externalHeapsortTest(2, 100);
    quickHeapsortTest(15, 1);
}