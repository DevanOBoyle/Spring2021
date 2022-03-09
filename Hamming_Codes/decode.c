//Devan O'Boyle
//Assignment 4: Hamming Codes
//Decoder

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
#define OPTIONS "hi:o:v"

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
    FILE *infile = stdin; //input file defaults as standard input
    FILE *outfile = stdout; //output file defaults as standard output
    struct stat statbuf; //used to specify file permissions
    int8_t byte1 = 0;
    int8_t byte2 = 0;
    uint8_t message_low = 0;
    uint8_t message_up = 0;
    HAM_STATUS up;
    HAM_STATUS low;
    uint8_t uncorrectable = 0; //keeps track of how many uncorrectable errors there are
    uint8_t corrected = 0; //keeps track of how many corrected errors there are
    uint8_t total_bytes = 0; //keeps track of the amount of bytes read
    uint8_t message = 0;
    bool stats = false; //tells whether or not the program should print extra statistics
    uint8_t checker[8][4]
        = { { 0, 1, 1, 1 }, { 1, 0, 1, 1 }, { 1, 1, 0, 1 }, { 1, 1, 1, 0 }, { 1, 0, 0, 0 },
              { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }; //used to decode the bytes later
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints out the help message
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code generator.\n\n");
            printf("USAGE\n");
            printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print statistics of decoding to stderr.\n");
            printf("  -i infile      Input data to encode.\n");
            printf("  -o outfile     Output of encoded data.\n");
            return 1;
            break;
        case 'i':
            //takes in the input file
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "failed to open %s\n", optarg);
                return 1;
            }
            fstat(fileno(infile), &statbuf);
            break;
        case 'o':
            //takes in the output file
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "failed to open %s\n", optarg);
                return 1;
            }
            fchmod(fileno(outfile), statbuf.st_mode);
            break;
        case 'v':
            stats = true; //sets it so that the program will print statistics later on
            break;
        }
    }
    BitMatrix *C = bm_create(8, 4);
    for (uint32_t i = 0; i < bm_rows(C); i++) {
        for (uint32_t j = 0; j < bm_cols(C); j++) {
            if (checker[i][j] == 1) {
                bm_set_bit(C, i, j);
            }
        }
    }
    while ((byte1 = fgetc(infile)) != EOF) {
        if ((byte2 = fgetc(infile)) == EOF) { //if there isn't a second byte, break
            break;
        }
        total_bytes += 2;
        low = decode(C, byte1, &message_low);
        up = decode(C, byte2, &message_up);
        if (low == -2) { //if there was an uncorrected error
            uncorrectable += 1; //increment the number of uncorrected errors
        } else if (low == -1) { //if there was an error that was corrected
            corrected += 1; //increment the number of corrected errors
        }
        if (up == -2) { //if there was an uncorrected error
            uncorrectable += 1; //increment the number of uncorrected errors
        } else if (up == -1) { //if there was an error that was corrected
            corrected += 1; //increment the number of corrected errors
        }
        message = pack_byte(message_up, message_low); //packs the two parts of the message together
        fputc(message, outfile); //outputs the decoded message
    }
    if (stats == true) {
        //prints out the various statistics
        float error_rate = uncorrectable / total_bytes;
        fprintf(stderr, "Total bytes processed: %u\n", total_bytes);
        fprintf(stderr, "Uncorrected errors: %u\n", uncorrectable);
        fprintf(stderr, "Corrected errors: %u\n", corrected);
        fprintf(stderr, "Error rate: %lf\n", error_rate);
    }
    bm_delete(&C); //deletes the checker matrix
    fclose(infile); //closes the input file
    fclose(outfile); //closes the output file
    return 0;
}
