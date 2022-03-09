#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocates memory for the stack
    if (s) {
        //initializes variables
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) malloc(capacity * sizeof(Node));
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s); //frees the stack
        *s = NULL; //deletes the stack
    }
}

bool stack_empty(Stack *s) {
    if (s->top == 0) { //if top index is zero
        return true; //then the stack is empty
    } else {
        return false;
    }
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) { //if top index is equal to the maximum capacity
        return true; //then the stack is full
    } else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    return s->top; //returns the size of the stack
}

bool stack_push(Stack *s, Node *n) {
    if (s->top == s->capacity) { //if the stack is full then you can't push a node onto the stack
        return false;
    }
    s->items[s->top] = n; //sets the node
    s->top += 1; //increments the top
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (s->top == 0) { //if the stack is empty then you can't pop a node off the stack
        return false;
    }
    s->top -= 1; //decrements the top
    *n = s->items[s->top]; //gets the popped node
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i++) {
        node_print(s->items[i]); //prints each node from the stack for debugging
    }
    printf("/n");
}
