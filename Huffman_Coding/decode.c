//Devan O'Boyle
//Assignment 6: Huffman Coding
//Decoder

#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    int infile = 0; //initializes the input file descriptor to sdin
    int outfile = 1; //initializes the output file descriptor to stdout
    bool stats = false; //keeps track of whether statistics should be printed or not
    uint8_t bit = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints the help message
            printf("SYNOPSIS\n");
            printf("A Huffman encoder.\n");
            printf("Decompresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n");
            printf("./decode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input file to compress.\n");
            printf("  -o outfile     Output of compressed data.\n");
            break;
        case 'i':
            //takes in an input file
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
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header)); //reads in the header
    if (h.magic != MAGIC) { //if magic numbers don't match
        fprintf(stderr, "Invalid magic number\n"); //complain and quit
        return 1;
    }
    fchmod(outfile, h.permissions);
    uint8_t tree_dump[h.tree_size];
    read_bytes(infile, tree_dump, h.tree_size);
    Node *tree_root = rebuild_tree(h.tree_size, tree_dump); //reconstructs the tree
    Node *n = tree_root;
    uint64_t written = 0;
    bool added = false;
    while (h.file_size > written) {
        added = false;
        if (n->left == NULL && n->right == NULL) {
            uint8_t buf[1];
            buf[0] = n->symbol;
            write_bytes(outfile, buf, 1);
            written += 1;
            n = tree_root;
            added = true;
        }
        if (added == false) {
            read_bit(infile, &bit);
            if (bit == 0) {
                n = n->left;
            } else if (bit == 1) {
                n = n->right;
            }
        }
    }
    //if requested, prints out the data compression statistics
    if (stats == true) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        double reads = bytes_read;
        double writes = bytes_written;
        double saving = 100 * (1 - (reads / writes));
        fprintf(stderr, "Space Saving: %lf%% bytes\n", saving);
    }
    delete_tree(&tree_root); //deletes the tree
    close(infile); //closes the input
    close(outfile); //closes the output
    return 0;
}
