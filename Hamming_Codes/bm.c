#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//code based off of Sahiti's pseudocode provided in her lab section
typedef struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
} BitMatrix;

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix)); //allocates memory for the bit matrix
    if (m) {
        //initializes variables
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows * cols);
        if (!m->rows || !m->cols) {
            free(m);
            m = NULL;
        }
    }
    return m;
}

void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector); //deletes the bit vector
        free(*m); //frees the allocated memory
        *m = NULL; //deletes the matrix by setting it to null
    }
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows; //returns the number of rows in the matrix
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols; //returns the nubmer of columns in the matrix
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c); //sets the corresponding bit to 1
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c); //sets the corresponding bit to 0
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(
        m->vector, r * m->cols + c); //returns the value of the corresponding bit, either 0 or 1
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *m = bm_create(1, length); //creates a new bit matrix to store the data
    for (uint32_t i = 0; i < length; i++) {
        if (byte & 1 << i) {
            bv_set_bit(m->vector, i); //if the ith bit of byte is 1, set the matrix to 1
        } else {
            bv_clr_bit(m->vector, i); //clears the matrix at the ith bit of the byte
        }
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t byte = 0;
    for (uint32_t i = 0; i < m->cols; i++) {
        byte += bv_get_bit(m->vector, i) << i;
    }
    return byte;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *m = bm_create(A->rows, B->cols); //creates a new matrix to store the product
    //multiplies matrices A and B
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < B->cols; j++) {
            uint32_t sum = 0;
            for (uint32_t k = 0; k < A->cols; k++) {
                sum = sum
                      ^ (bm_get_bit(A, i, k)
                          & bm_get_bit(B, k, j)); //xors the and of A(i,k) and B(k,j) with the sum
            }
            if (sum % 2 == 1) { //if the binary of sum is 1, set the corresponding bit to 1
                bm_set_bit(m, i, j);
            } else { //otherwise, set the corresponding bit to 0
                bm_clr_bit(m, i, j);
            }
        }
    }
    return m;
}

void bm_print(BitMatrix *m) {
    //iterates through the bit matrix
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            printf("%d", bm_get_bit(m, i, j)); //prints out each element in the bit matrix
        }
        printf("\n");
    }
}
