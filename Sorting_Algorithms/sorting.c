//Devan O'Boyle
//Assignment 3: Sorting Putting Your Affairs in Order

#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absQqr:n:p:"
//variables to keep track of various statistics of each sort
uint32_t moves;
uint32_t compares;
uint32_t s_size;
uint32_t q_size;

int main(int argc, char **argv) {
    int opt = 0;
    uint64_t seed = 13371453; //value of the random seed
    uint64_t size = 100; //size of the array to be sorted
    uint64_t printed_elements = 100; //number of elements to be printed
    moves = 0; //initializes moves
    compares = 0; //initializes compares
    //booleans for each sort to keep track of which one is to be printed
    bool bubble = false;
    bool shell = false;
    bool quick_stack = false;
    bool quick_queue = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            //in case all, all sorts are set to be printed
            bubble = true;
            shell = true;
            quick_stack = true;
            quick_queue = true;
            break;
        case 'b':
            //in case bubble, bubble sort is set to be printed
            bubble = true;
            break;
        case 's':
            //in case shell, shell sort is set to be printed
            shell = true;
            break;
        case 'q':
            //in case stack, quick sort using a stack is set to be printed
            quick_stack = true;
            break;
        case 'Q':
            //in case queue, quick sort using a queue is set to be printed
            quick_queue = true;
            break;
        case 'r':
            seed = atoi(optarg); //allows the user to change the value of the random seed
            break;
        case 'n':
            size = atoi(optarg); //allows the user to change the size of the array
            break;
        case 'p':
            printed_elements
                = atoi(optarg); //allows the user to change how many elements are printed
            break;
        }
    }
    srandom(seed); //sets the seed
    //declares each array for each of the sorts
    uint32_t bubble_arr[size];
    uint32_t shell_arr[size];
    uint32_t stack_arr[size];
    uint32_t queue_arr[size];
    for (uint32_t i = 0; i < size; i++) {
        bubble_arr[i]
            = random(); //gives each element in the bubble array random values from the seed
        //copies the bubble array's values to all of the other arrays
        shell_arr[i] = bubble_arr[i];
        stack_arr[i] = bubble_arr[i];
        queue_arr[i] = bubble_arr[i];
    }
    //if bubble sort is set to be printed
    if (bubble == true) {
        bubble_sort(bubble_arr, size); //sorts the array using bubble sort
        printf("Bubble Sort\n");
        printf("%lu elements, %u moves, %u compares\n", size, moves, compares); //prints the stats
        uint32_t e = 1;
        for (uint32_t i = 0; i < size && i < printed_elements; i++) {
            printf("%13" PRIu32, bubble_arr[i]); //prints each sorted element of the array
            //ensures that the output prints in rows of five
            if (e == 5) {
                printf("\n");
                e = 1;
            } else {
                e += 1;
            }
        }
        if (e != 0) {
            printf("\n"); //ensures a newline is printed at the end
        }
        //resets the stats for the next use
        moves = 0;
        compares = 0;
    }
    //if shell sort is set to be printed
    if (shell == true) {
        shell_sort(shell_arr, size); //sorts the array using shell sort
        printf("Shell Sort\n");
        printf("%lu elements, %u moves, %u compares\n", size, moves, compares); //prints the stats
        uint32_t e = 1;
        for (uint32_t i = 0; i < size && i < printed_elements; i++) {
            printf("%13" PRIu32, shell_arr[i]); //prints each sorted element of the array
            //ensures that the output prints in rows of five
            if (e == 5) {
                printf("\n");
                e = 1;
            } else {
                e += 1;
            }
        }
        if (e != 0) {
            printf("\n"); //ensures a newline is printed at the end
        }
        //resets the stats for the next use
        moves = 0;
        compares = 0;
    }
    //if quick sort using a stack is set to be printed
    if (quick_stack == true) {
        quick_sort_stack(stack_arr, size); //sorts the array using quick sort with a stack
        printf("Quick Sort (Stack)\n");
        printf("%lu elements, %u moves, %u compares\n", size, moves, compares); //prints the stats
        printf("Max stack size: %u\n", s_size); //prints the max size of the stack
        uint32_t e = 1;
        for (uint32_t i = 0; i < size && i < printed_elements; i++) {
            printf("%13" PRIu32, stack_arr[i]); //prints each sorted element of the array
            //ensures that the output prints in rows of five
            if (e == 5) {
                printf("\n");
                e = 1;
            } else {
                e += 1;
            }
        }
        if (e != 0) {
            printf("\n"); //ensures a newline is printed at the end
        }
        //resets the stats for the next use
        moves = 0;
        compares = 0;
    }
    //if quick sort using a queue is set to be printed
    if (quick_queue == true) {
        quick_sort_queue(queue_arr, size); //sorts the array using quick sort with a queue
        printf("Quick Sort (Queue)\n");
        printf("%lu elements, %u moves, %u compares\n", size, moves, compares); //prints the stats
        printf("Max queue size: %u\n", q_size); //prints the max size of the queue
        uint32_t e = 1;
        for (uint32_t i = 0; i < size && i < printed_elements; i++) {
            printf("%13" PRIu32, queue_arr[i]); //prints each sorted element of the array
            //ensures that the output prints in rows of five
            if (e == 5) {
                printf("\n");
                e = 1;
            } else {
                e += 1;
            }
        }
        if (e != 0) {
            printf("\n"); //ensures a newline is printed at the end
        }
        //resets the stats for the next use
        moves = 0;
        compares = 0;
    }
    return 0;
}
