/*****************************************************************************/
/**                     QuickHeapsort implementation                        **/
/**                     Lorenzo Catania, ..(?).. 2017                       **/
/**               Algorithm specifications may be found at                  **/
/**   http://www.sciencedirect.com/science/article/pii/S0304397501002882    **/
/**       Full source code: https://github.com/aegroto/QuickHeapsortCPP     **/
/*****************************************************************************/

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

    quickHeapsortTest(20, 10000);
}