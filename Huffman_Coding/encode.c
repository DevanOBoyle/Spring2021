//Devan O'Boyle
//Assignment 6: Huffman Coding
//Encoder

#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

uint64_t bytes_read;
uint64_t bytes_written;

bool tree_dump(Node *root, uint8_t *buf, uint32_t index, Header h, int out) {
    if (root->left == NULL && root->right == NULL) { //if the node is a child
        buf[index] = 'L'; //set L to indicate a child node
        write_bytes(out, &buf[index], 1);
        buf[index + 1] = root->symbol; //set the symbol
        write_bytes(out, &buf[index + 1], 1);
        index += 2;
        return true;
    } else { //otherwise it is a parent node
        tree_dump(root->left, buf, index, h, out); //go to the left child
        tree_dump(root->right, buf, index, h, out); //go to the right child
        buf[index] = 'I'; //set I to indicate a parent node
        write_bytes(out, &buf[index], 1);
        index += 1;
    }
    if (h.tree_size == index) {
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    int infile = 0; //descriptor for stdin
    int outfile = 1; //descriptor for stdout
    struct stat statbuf;
    uint8_t buffer[BLOCK] = { 0 }; //initializes the buffer
    uint64_t hist[ALPHABET] = { 0 }; //initializes the histogram
    uint64_t unique = 0; //keeps track of the number of unique characters
    uint8_t tdump[MAX_TREE_SIZE] = { 0 }; //array to store the tree dump
    uint32_t tree_index = 0; //keeps track of the index in the tree
    bool stats = false; //tells whether or not statistics should be printed or not
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints the help message
            printf("SYNOPSIS\n");
            printf("A Huffman encoder.\n");
            printf("Compresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to compress.\n");
            printf("  -o outfile     Output of compressed data.\n");
            break;
        case 'i':
            //takes in an input file to read
            infile = open(optarg, O_RDONLY);
            break;
        case 'o':
            //takes in the output file
            outfile
                = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600); //opens the output file to write
            break;
        case 'v': stats = true; break;
        }
    }
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);
    //ensures at least 2 elements are present
    hist[0] += 1;
    hist[255] += 1;
    uint32_t bytes = 0;
    while ((bytes = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (uint32_t i = 0; i < bytes; i++) {
            hist[buffer[i]] += 1; //increments for each corresponding ASCII character found
        }
    }
    lseek(infile, 0, SEEK_SET); //resets the input index back to the beginning of the input file
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            unique += 1; //counts the number of unique characters in the input
        }
    }
    Code code_table[ALPHABET]; //creates the code table
    Node *tree_root = build_tree(hist); //builds the tree and returns the root
    build_codes(tree_root, code_table); //builds the codes

    //sets all of the corresponding values to header
    Header h;
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = (3 * unique) - 1;
    h.file_size = statbuf.st_size;
    //writes the header to the outfile
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));

    tree_dump(tree_root, tdump, tree_index, h, outfile); //dumps the tree

    uint32_t temp = 1;
    while (temp > 0) {
        temp = read_bytes(infile, buffer, BLOCK);
        for (uint32_t i = 0; i < temp; i++) {
            write_code(outfile, &code_table[buffer[i]]); //writes the code to the output
        }
    }
    flush_codes(outfile); //flushes the remaining codes
    //if requested, prints out the data compression statistics
    if (stats == true) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        double reads = bytes_read;
        double writes = bytes_written;
        double saving = 100 * (1 - (writes / reads));
        fprintf(stderr, "Space saving: %lf%% bytes\n", saving);
    }
    delete_tree(&tree_root); //deletes the tree
    close(infile); //closes the input
    close(outfile); //closes the output
    return 0;
}
