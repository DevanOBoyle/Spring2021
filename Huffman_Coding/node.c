#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    uint8_t symbol;
    uint64_t frequency;
} Node;

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node)); //allocates memory for the node
    if (n) {
        //initializes variables
        n->left = NULL;
        n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n); //frees the node
        *n = NULL; //deletes the node
    }
}

Node *node_join(Node *left, Node *right) {
    Node *n = node_create('$', left->frequency + right->frequency); //creates a new node
    n->left = left; //sets the left as the left child node
    n->right = right; //sets the right as the right child node
    return n;
}

void node_print(Node *n) {
    printf("%c %lu ", n->symbol, n->frequency); //prints the node for debugging
}
