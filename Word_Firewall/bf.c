#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
} BloomFilter;

//based on pseudocode provided by Sahiti during her lab section
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf
        = (BloomFilter *) malloc(sizeof(BloomFilter)); //allocates memory for the bloom filter
    if (bf) {
        //Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        //The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        //The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter); //deletes the bit vector
        free(*bf); //frees the bloom filter
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter); //returns the length of the bit vector
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak) % bv_length(bf->filter); //gets the index
    bv_set_bit(bf->filter, primary_index); //sets the corresponding bit at that index to 1
    //does the same for the others
    uint32_t secondary_index = hash(bf->secondary, oldspeak) % bv_length(bf->filter);
    bv_set_bit(bf->filter, secondary_index);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak) % bv_length(bf->filter);
    bv_set_bit(bf->filter, tertiary_index);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak) % bv_length(bf->filter); //gets the index
    bool prim = bv_get_bit(bf->filter, primary_index); //finds the bit at that index
    //does the same for the others
    uint32_t secondary_index = hash(bf->secondary, oldspeak) % bv_length(bf->filter);
    bool sec = bv_get_bit(bf->filter, secondary_index);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak) % bv_length(bf->filter);
    bool tert = bv_get_bit(bf->filter, tertiary_index);
    if (prim == true && sec == true && tert == true) { //if all of the bits are 1
        return true; //then the word exists in the bloom filter
    }
    return false; //otherwise the word does not exist in the bloom filter
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        count += bv_get_bit(bf->filter, i); //increments for each bit that is 1
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter); //prints the bloom filter
}
