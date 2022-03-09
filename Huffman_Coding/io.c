#include "io.h"

#include "code.h"
#include "defines.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint64_t bytes_read;
uint64_t bytes_written;
static uint64_t bit_index = 0;
static uint8_t buffer[BLOCK] = { 0 };

//based on pseudocode provided by Brian Zhao during his lab section
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes = 1; //used to keep track of how many bytes are read with each read call
    int total = 0; //keeps track of the total in this current function call
    while (bytes > 0 && total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        bytes_read += bytes; //adds bytes to the total number of bytes read by the file
        total += bytes; //adds bytes to the total number of bytes
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes = 1; //used to keep track of how many bytes are written with each write call
    int total = 0; //keeps track of the total in this current function call
    while (bytes > 0 && total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        bytes_written += bytes; //adds bytes to the total number of bytes written to the file
        total += bytes; //adds bytes to the total number of bytes
    }
    return total;
}

//inspired by pseudocode provide by Sahiti Vallamreddy during her lab section
bool read_bit(int infile, uint8_t *bit) {
    static uint32_t index = 0;
    static uint8_t bit_buf[BLOCK];
    uint32_t EOB = 0; //keeps track of the end of the buffer
    if (index != 0) {
        uint32_t bytes = read_bytes(infile, bit_buf, BLOCK);
        if (bytes != BLOCK) {
            EOB = bytes * 8;
        }
    }
    *bit = (bit_buf[index / 8] & (1 << (index % 8))) >> (index % 8);
    index = (index + 1) % (BLOCK * 8);
    if (index >= EOB) { //if bit index is greater than the end of the buffer
        return false; //then there are no more bits to read
    }
    return true;
}

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (((c->bits[i / 8] >> (i % 8)) & 0x1) == 1) { //if the bit is 1
            buffer[bit_index / 8] |= (0x1 << (bit_index % 8)); //sets the bit to 1
        } else if (((c->bits[i / 8] >> (i % 8)) & 0x1) == 0) { //if the bit is 0
            buffer[bit_index / 8] &= ~(0x1 << (bit_index % 8)); //sets the bit to 0
        }
        bit_index += 1;
        if (bit_index == 8 * BLOCK) {
            write_bytes(outfile, buffer, BLOCK);
            for (uint32_t e = 0; e < BLOCK; e++) {
                buffer[e] = 0;
            }
            bit_index = 0;
        }
    }
}

void flush_codes(int outfile) {
    uint32_t bits = 0;
    if (bit_index > 0) {
        if (bit_index % 8 == 0) {
            bits += bit_index / 8;
        } else {
            bits += (bit_index / 8) + 1;
        }
        write_bytes(outfile, buffer, bits);
    }
}
