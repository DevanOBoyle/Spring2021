#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET); //creats a priority queue
    for (int i = 0; i < ALPHABET; i++) { //iterates through the histogram
        if (hist[i] != 0) { //if there is a character in the histogram
            Node *n = node_create(i, hist[i]); //create a node
            enqueue(q, n); //enqueue the node to the priority queue
        }
    }
    Node *right;
    Node *left;
    Node *parent;
    while (pq_size(q) > 1) {
        dequeue(q, &left); //dequeues the left node
        dequeue(q, &right); //dequeues the right node
        parent = node_join(left, right); //creates a parent node
        enqueue(q, parent); //enqueues the parent node
    }
    Node *root;
    dequeue(q, &root); //dequeues the root node to be returned
    pq_delete(&q);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code code = { 0, { 0 } }; //initializes the code
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) { //if a child node is reached
            table[root->symbol] = code; //add the code to the code table
        } else { //otherwise traverse the left child
            code_push_bit(&code, 0);
            build_codes(root->left, table);
            uint8_t bit = 0;
            code_pop_bit(&code, &bit);

            //and then traverse the right child
            code_push_bit(&code, 1);
            build_codes(root->right, table);
            code_pop_bit(&code, &bit);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(ALPHABET); //creates a stack
    Node *root;
    for (uint32_t i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') { //if a child node is reached
            Node *n = node_create(tree[i + 1], 1); //create a node for it
            stack_push(s, n); //push it to the stack
            i += 1;
        } else if (tree[i] == 'I') { //if a parent node is reached
            Node *right;
            stack_pop(s, &right); //pop the right child
            Node *left;
            stack_pop(s, &left); //pop the left child
            Node *parent
                = node_join(left, right); //create a parent node for the left and right children
            stack_push(s, parent); //pushes the parent onto the stack
        }
    }
    stack_pop(s, &root);
    stack_delete(&s); //deletes the stack
    return root; //returns the parent node
}

void delete_tree(Node **root) {
    if (*root) {
        if ((*root)->left) { //if there is a left child
            delete_tree(&(*root)->left); //traverses the left path
        }
        if ((*root)->right) { //if there is a right child
            delete_tree(&(*root)->right); //traverses the right path
        }
        node_delete(&(*root)); //deletes the current node
    }
}
