#include "gaps.h"
#include "stats.h"

#include <stdbool.h>
#include <stdint.h>

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t gap = 0; gap < GAPS; gap++) { //iterates through the different gap values
        for (uint32_t i = gaps[gap]; i < n;
             i++) { //iterates through the array starting at the corresponding gap value
            uint32_t j = i;
            uint32_t temp = A[i]; //stores the current element of the array to a temp variable
            moves += 1;
            compares += 1;
            //compares the current element with another one that is gap elements away
            while (j >= gaps[gap] && temp <= A[j - gaps[gap]]) {
                compares += 1;
                A[j]
                    = A[j
                        - gaps
                            [gap]]; //sets the current element with another element that is gap elements away
                moves += 1;
                j -= gaps[gap];
            }
            //complete the swap
            A[j]
                = temp; //sets the value of the element that was gap indices away to the value of the old current element
            moves += 1;
        }
    }
}
