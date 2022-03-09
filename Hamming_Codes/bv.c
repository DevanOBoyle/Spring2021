#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//code inspired by Sahiti's pseudocode provided in her lab section
typedef struct BitVector {
    uint32_t length;
    uint8_t *vector;
} BitVector;

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector)); //allocates memory for the bit vector
    if (v) {
        v->length = length;
        int value = 0;
        if (length == 0) {
            value = length / 8;
        } else {
            value = (length / 8) + 1;
        }
        v->vector = (uint8_t *) calloc(
            value, sizeof(uint8_t)); //allocates memory for the array to store the bit values
        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v); //frees the allocated memory
        *v = NULL; //deletes the bit vector by setting it to null
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    return v->length; //returns the length of the bit vector
}

void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= (0x1 << (i % 8)); //sets the ith bit in the bit vector to 1
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(0x1 << (i % 8)); //clears the ith bit in the bit vector by setting it to 0
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] >> (i % 8) & 0x1); //returns the ith bit's value, either 0 or 1
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    v->vector[i / 8] = v->vector[i / 8] ^ bit; //takes the xor of the ith bit and another given bit
}
