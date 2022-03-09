#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//heavily based on the code that I used in asgn3 which was originally inspired by Eugene's that he provided in his lab section
typedef struct Stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocates memory for the stack
    if (s) {
        //initializes variables
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) malloc(capacity * sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s); //frees the allocated memory
        *s = NULL; //sets the stack to null
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top; //returns the top index, which is equal to the size of the stack
}

bool stack_empty(Stack *s) {
    if (s->top == 0) { //if the top index is 0, then the stack is empty
        return true;
    } else { //otherwise it isn't
        return false;
    }
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) { //if the top index equals the capacity, then the stack is full
        return true;
    } else {
        return false;
    }
}

bool stack_push(Stack *s, uint32_t x) {
    if (s->top == s->capacity) { //if the stack is full, then no element can be pushed
        return false;
    }
    s->items[s->top] = x; //sets the new element onto the stack
    s->top += 1; //increments the top index
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (s->top == 0) { //if the stack is empty, then there is nothing to pop
        return false;
    }
    s->top -= 1; //decrements the top index
    *x = s->items[s->top]; //removes the top element
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (s->top == 0) { //if the stack is empty, then there is nothing to peek at
        return false;
    }
    *x = s->items[s->top - 1]; //sets the topmost element to x
    return true;
}

bool stack_copy(Stack *dst, Stack *src) {
    dst->capacity = src->capacity; //sets the destination capacity equal to the source capacity
    for (uint32_t i = 0; i < stack_size(src); i++) {
        dst->items[i]
            = src->items[i]; //sets each item from the source stack equal to the destination stack
    }
    dst->top = src->top; //sets the top index from the source equal to the destination
    if (dst->top == src->top) { //checks if the stack was successfully copied
        return true;
    } else {
        return false;
    }
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) { //increments through the stack
        fprintf(outfile, "%s", cities[s->items[i]]); //prints out each element of the stack
        if (i + 1 != s->top) {
            fprintf(outfile, " -> "); //prints an arrow in between each city that leads to another
        }
    }
    fprintf(outfile, "\n");
}
