//Devan O'Boyle
//Assignment 4: Hamming Codes
//Encoder

#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BLOCK   4096
#define OPTIONS "hi:o:"

//functions provided in the assignment doc by Professor Long
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    FILE *infile = stdin; //sets the input file to stardard input
    FILE *outfile = stdout; //sets the output file to standard output
    struct stat statbuf; //used for file permissions
    int8_t byte = 0; //used to store a byte of data read from the input
    uint8_t low = 0;
    uint8_t code_low = 0;
    uint8_t code_up = 0;
    uint8_t up = 0;
    uint8_t generator[4][8] = { { 1, 0, 0, 0, 0, 1, 1, 1 }, { 0, 1, 0, 0, 1, 0, 1, 1 },
        { 0, 0, 1, 0, 1, 1, 0, 1 }, { 0, 0, 0, 1, 1, 1, 1, 0 } }; //generator matrix uses to encode
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints the help message
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code generator.\n\n");
            printf("USAGE\n");
            printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input data to encode.\n");
            printf("  -o outfile     Output of encoded data.\n");
            return 1;
            break;
        case 'i':
            //takes in an input file
            infile = fopen(optarg, "r"); //opens the input file to read
            if (infile == NULL) {
                fprintf(stderr, "failed to open %s\n",
                    optarg); //prints an error if the input file is null
                return 1;
            }
            fstat(fileno(infile), &statbuf);
            break;
        case 'o':
            //takes in the output file
            outfile = fopen(optarg, "w"); //opens the output file to write
            if (outfile == NULL) {
                fprintf(stderr, "failed to open %s\n",
                    optarg); //prints an error if the output file is null
                return 1;
            }
            fchmod(fileno(outfile), statbuf.st_mode);
            break;
        }
    }
    BitMatrix *G = bm_create(4, 8); //creates the generator matrix
    for (uint32_t i = 0; i < bm_rows(G); i++) {
        for (uint32_t j = 0; j < bm_cols(G); j++) {
            if (generator[i][j] == 1) {
                bm_set_bit(
                    G, i, j); //sets each element of the generator 2d array to the generator matrix
            }
        }
    }
    while ((byte = fgetc(infile)) != EOF) { //reads in each byte from the input
        low = lower_nibble(byte); //gets the lower nibble of the byte
        up = upper_nibble(byte); //gets the upper nibble of the byte
        code_low = encode(G, low); //encodes the lower nibble
        fputc(code_low, outfile); //prints the encoded lower nibble to the outfile
        code_up = encode(G, up); //encodes the upper nibble
        fputc(code_up, outfile); //prints the decoded upper nibble to the outfile
    }
    bm_delete(&G); //deletes the generator matrix
    fclose(infile); //closes the input file
    fclose(outfile); //closes the output file
    return 0;
}
