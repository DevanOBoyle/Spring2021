#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
} Queue;

//code inspired by Sahiti Vallamreddy from her lab section
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue)); //allocates memory for the queue
    if (q) {
        //initializes variables
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) malloc(capacity * sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q); //frees the allocated memory
        *q = NULL; //sets the queue to null
    }
}

bool queue_empty(Queue *q) {
    if (q->tail == 0) { //if the tail is zero, then the queue is empty
        return true;
    } else { //otherwise the queue isn't empty
        return false;
    }
}

bool queue_full(Queue *q) {
    if (q->size
        == q->capacity) { //if the size of the queue equals the capacity then the queue is full
        return true;
    } else { //otherwise it isn't
        return false;
    }
}

uint32_t queue_size(Queue *q) {
    return q->size; //returns the size of the queue
}

bool enqueue(Queue *q, int64_t x) {
    if (q->size == q->capacity) { //if the queue is full, then it can't enqueue another element
        return false;
    }
    q->size += 1; //increases the size of the queue
    q->items[q->tail] = x; //sets the new element
    q->tail = (q->tail + 1) % q->capacity; //allows the queue to wrap around to the beginning
    return true;
}

bool dequeue(Queue *q, int64_t *x) {
    if (q->size == 0) { //if the queue is empty, then it can't dequeue an element
        return false;
    }
    q->size -= 1; //decreases the size of the queue
    *x = q->items[q->head]; //takes out the element
    q->head = (q->head + 1) % q->capacity;
    return true;
}

void queue_print(Queue *q) {
    printf("[");
    for (uint32_t i = 0; i < q->tail; i++) { //increments through the queue
        printf("%" PRId64, q->items[i]); //prints out each element of the queue
        if (i + 1 != q->tail) {
            printf(", ");
        }
    }
    printf("]\n");
}
