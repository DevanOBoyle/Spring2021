
#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_duplicate(char *speak) {
    return strcpy(malloc(strlen(speak) + 1),
        speak); //creates a duplicate of the given string by allocating memory for a copy of it
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node)); //allocates memory for the node
    if (n) {
        if (oldspeak == NULL) { //checks if oldspeak is null
            n->oldspeak = NULL;
        } else {
            n->oldspeak
                = string_duplicate(oldspeak); //dupicates oldspeak and sets it to the node variable
        }
        if (newspeak == NULL) { //checks if newspeak is null
            n->newspeak = NULL;
        } else {
            n->newspeak
                = string_duplicate(newspeak); //duplicates newspeak and set it to the node variable
        }
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak); //frees oldspeak
        free((*n)->newspeak); //frees newspeak
        free(*n); //frees the node
        *n = NULL; //deletes the node
    }
}

void node_print(Node *n) {
    if (n->newspeak == NULL) { //if newspeak doesn't exist
        printf("%s\n", n->oldspeak); //only prints oldspeak
    } else {
        printf(
            "%s -> %s\n", n->oldspeak, n->newspeak); //otherwise prints both newspeak and oldspeak
    }
}
