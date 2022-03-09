#include "stats.h"

#include <stdbool.h>
#include <stdint.h>

//code inspired by python code provided by Professor Long on the assignment doc
void bubble_sort(uint32_t *A, uint32_t n) {
    bool swap = true; //keeps track if the sort needs to keep swapping elements or not
    while (swap == true) {
        swap = false;
        for (uint32_t i = 1; i < n; i++) { //iterates through each element of the array
            compares += 1;
            //compares two adjacent elements
            if (A[i]
                < A[i
                    - 1]) { //if the current element is smaller than the one before it, swap those elements
                uint32_t temp = A[i]; //creates a temp value for one of the elements
                moves += 1;
                A[i] = A
                    [i - 1]; //sets the value of the current element to the value of the previous one
                moves += 1;
                A[i - 1]
                    = temp; //sets the value of the previous element to the value of what the current one was
                moves += 1;
                swap = true; //continue checking for more values to be swapped
            }
        }
        n -= 1;
    }
}
