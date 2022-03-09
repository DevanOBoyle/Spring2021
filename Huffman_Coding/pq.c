#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node **items;
} PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q
        = (PriorityQueue *) malloc(sizeof(PriorityQueue)); //allocates memory for the priority queue
    if (q) {
        //initializes variables
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) malloc(capacity * sizeof(Node));
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q); //frees the allocated memory
        *q = NULL; //deletes the queue
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->tail == 0) { //if the tail is zero, then the queue is empty
        return true;
    } else { //otherwise the queue isn't empty
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size; //returns the size of the queue
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (q->tail == q->capacity) { //if the queue is full, then it can't enqueue another element
        return false;
    }
    uint32_t t = q->tail;
    while (t > q->head) {
        if (q->items[t - 1]->frequency
            > n->frequency) { //if the node before the current one has greater priority
            q->items[t] = q->items[t - 1]; //shift node at t-1 to t
            t -= 1;
        } else {
            break;
        }
    }
    q->size += 1; //increments the queue size
    q->items[t] = n; //sets the enqueued node
    q->tail = (q->tail + 1) % q->capacity; //wraps the queue
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (q->size == 0) { //if the queue is empty then you can't dequeue a node
        return false;
    }
    q->size -= 1; //decrements the queue size
    *n = q->items[q->head]; //gets the dequeued node
    q->head = (q->head + 1) % q->capacity; //wraps the queue
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i++) {
        node_print(q->items[i]); //prints each node in the queue
    }
    printf("\n");
}
