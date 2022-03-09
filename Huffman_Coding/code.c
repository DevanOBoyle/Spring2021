#include "defines.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Code {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {
    //initializes the code
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top; //returns the size of the code stack
}

bool code_empty(Code *c) {
    if (c->top == 0) { //if the top index is zero
        return true; //then the code stack is empty
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE) { //if the top is equal to the maximum size
        return true; //then the code stack is full
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top == MAX_CODE_SIZE) { //if the code stack is full
        return false; //then you can't push another bit
    }
    if (bit == 1) {
        c->bits[c->top / 8] |= (0x1 << (c->top % 8)); //sets the bit to 1
    } else {
        c->bits[c->top / 8] &= ~(0x1 << (c->top % 8)); //sets the bit to 0
    }
    c->top += 1; //increments the top
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c->top == 0) { //if the code stack is empty
        return false; //then you can't pop a bit
    }
    c->top -= 1; //decrements the top
    *bit = (c->bits[c->top / 8] >> (c->top % 8)) & 0x1; //gets the bit
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%" PRIu8, c->bits[i]); //prints out the code for debugging
    }
    printf("\n");
}
