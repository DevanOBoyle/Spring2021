#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//code inspired by Eugene Chou provided in his lab section

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocates the memory for the stack
    if (s) {
        //initializes variables
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) malloc(capacity * sizeof(int64_t));
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

bool stack_empty(Stack *s) {
    if (s->top == 0) { //if the top index is 0, then the stack is empty
        return true;
    } else { //otherwise it isn't
        return false;
    }
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) { //if the top index equals the capacity
        return true;
    } else {
        return false;
    }
}

uint32_t stack_size(Stack *s) {
    return s->top; //returns the top index which is equal to the size of the stack
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top
        == s->capacity) { //if the stack is full, then another element can't be pushed onto the stack
        return false;
    }
    s->items[s->top] = x; //sets the new element onto the stack
    s->top += 1; //increases the top index
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (s->top == 0) { //if the stack is empty, then there isn't an element to pop
        return false;
    }
    s->top -= 1; //decreases the top index
    *x = s->items[s->top]; //removes the element off the top
    return true;
}

void stack_print(Stack *s) {
    printf("[");
    for (uint32_t i = 0; i < s->top; i++) { //increments through the stack
        printf("%" PRId64, s->items[i]); //prints out each element of the stack
        if (i + 1 != s->top) {
            printf(", ");
        }
    }
    printf("]\n");
}
