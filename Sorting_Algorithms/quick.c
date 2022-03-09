#include "queue.h"
#include "stack.h"
#include "stats.h"

#include <inttypes.h>

//code inspired by the python code provided by Professor Long on the assignment document

int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    int64_t pivot
        = A[(lo
             + ((hi - lo)
                 / 2))]; //sets the pivot value to be the midpoint between the high and low indices
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i += 1;
        compares += 1;
        while (A[i] < pivot) { //while the low value is less than the pivot value
            i += 1; //increments i
            compares += 1;
        }
        j -= 1;
        compares += 1;
        while (A[j] > pivot) { //while the high value is greater than the pivot value
            j -= 1; //decrements j
            compares += 1;
        }
        if (i < j) {
            uint32_t temp = A[i]; //sets the temp value to store the value
            moves += 1;
            A[i] = A[j];
            moves += 1;
            A[j] = temp; //swaps the values
            moves += 1;
        }
    }
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Stack *stack = stack_create(n); //creates the stack
    stack_push(stack, lo); //pushes the low index to the stack
    stack_push(stack, hi); //pushes the high index to the stack
    s_size = stack_size(stack); //sets the current maximum size of the stack
    while (stack_size(stack) != 0) {
        stack_pop(stack, &hi); //pops the high index from the stack
        stack_pop(stack, &lo); //pops the low index from the stack
        int64_t p = partition(A, lo, hi); //sets the pivot point and swaps the elements
        if (lo < p) {
            stack_push(stack, lo); //pushes the low index onto the stack
            stack_push(stack, p); //pushes the pivot point onto the stack
        }
        if (hi > p + 1) {
            stack_push(stack, p + 1); //pushes the index after the pivot point onto the stack
            stack_push(stack, hi); //pushes the high index onto the stack
        }
        if (stack_size(stack) > s_size) { //if the current stack size is greater than the max
            s_size = stack_size(stack); //sets the new max size of the stack
        }
    }
    stack_delete(&stack); //deletes the stack to avoid memory leaks
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    Queue *queue = queue_create(n); //creates the stack
    enqueue(queue, lo); //enqueues the low index to the queue
    enqueue(queue, hi); //enqueues the high index to the queue
    q_size = queue_size(queue); //sets the current maximum size of the stack
    while (queue_size(queue) != 0) {
        dequeue(queue, &lo); //dequeues the low index to the queue
        dequeue(queue, &hi); //dequeues the high index to the queue
        int64_t p = partition(A, lo, hi); //sets the pivot point and swaps the elements
        if (lo < p) {
            enqueue(queue, lo); //enqueues the low index to the queue
            enqueue(queue, p); //enqueues the pivot point to the queue
        }
        if (hi > p + 1) {
            enqueue(queue, p + 1); //enqueues the index after the pivot point to the queue
            enqueue(queue, hi); //enqueues the high index to the queue
        }
        if (queue_size(queue) > q_size) { //if the current queue size is greater than the max
            q_size = queue_size(queue); //sets the new max size of the queue
        }
    }
    queue_delete(&queue); //deletes the queue to avoid memory leaks
}
