#include "bm.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum HAM_STATUS { HAM_OK = -3, HAM_ERR = -2, HAM_CORRECT = -1 } HAM_STATUS;

//code based of pseudocode provided by Sahiti in her lab section
uint8_t encode(BitMatrix *G, uint8_t msg) {
    uint8_t c = 0;
    BitMatrix *m = bm_from_data(msg, 4); //takes the message and turns it into a bit matrix
    BitMatrix *code = bm_multiply(
        m, G); //encodes the message by multiplying its bit matrix by the generator matrix
    c = bm_to_data(code);
    bm_delete(&m);
    bm_delete(&code);
    return c; //returns the code
}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, 8); //takes in the code and turns it into a bit matrix
    BitMatrix *error
        = bm_multiply(c, Ht); //gets the error code by multiplying the code by the checker matrix
    //checks to see if the error code is 0000
    bool ok = false;
    for (uint32_t i = 0; i < 4; i++) {
        if (bm_get_bit(error, 1, i) == 0) {
            ok = true;
        } else {
            ok = false;
            break;
        }
    }
    if (ok == true) { //if so, then return ham_ok to indicate that there were no errors
        *msg = bm_to_data(c);
        bm_delete(&c);
        bm_delete(&error);
        return HAM_OK;
    } //otherwise check the table for the errors
    bool match
        = false; //will be true if all of the error bits match a line of bits in the look up table
    uint32_t index = 0;
    //increments through the look up table
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (bm_get_bit(Ht, i, j) == bm_get_bit(error, 1, j)) {
                match = true;
            } else {
                match = false;
            }
        }
        if (match == true) {
            index = i;
            break;
        }
    }
    if (match == true) { //if the error code is in the look up table
        //flip the bit
        if (bm_get_bit(c, 1, index) == 1) {
            bm_clr_bit(c, 1, index);
        } else {
            bm_set_bit(c, 1, index);
        }
        *msg = bm_to_data(c);
        bm_delete(&error);
        bm_delete(&c);
        return HAM_CORRECT; //return indicates that there was an error and it was corrected
    }
    //if the error code isn't in the look up table, then there must be more than one
    *msg = bm_to_data(c);
    bm_delete(&error);
    bm_delete(&c);
    return HAM_ERR; //since the errors can't be corrected, returns ham_err
}
