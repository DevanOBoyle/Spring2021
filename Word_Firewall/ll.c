#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks;
uint64_t links;

typedef struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
} LinkedList;

//based on pseudocode provided by Sahiti during her lab section
LinkedList *ll_create(bool mtf) {
    LinkedList *ll
        = (LinkedList *) malloc(sizeof(LinkedList)); //allocates memory for the bit vector
    if (ll) {
        //initializes variables
        ll->mtf = mtf;
        ll->length = 0;
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
    }
    return ll;
}

void ll_delete(LinkedList **ll) {
    while ((*ll)->head != NULL) {
        Node *n = (*ll)->head->next;
        node_delete(&(*ll)->head); //deletes each node
        (*ll)->head = n; //goes to the next node
    }
    free(*ll); //frees the linked list
    *ll = NULL; //deletes the linked list
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks += 1; //increments the number of seeks for each lookup performed
    for (Node *current = ll->head->next; current->oldspeak != NULL;
         current = current->next) { //increments through all of the nodes
        if (strcmp(current->oldspeak, oldspeak)
            == 0) { //if the oldspeak in the current node matches the word, then the oldspeak contains the word
            if (ll->mtf == true) { //if move to front is on
                //then the current node is moved to the front of the linked list
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current->next = ll->head->next;
                current->prev = ll->head;
                ll->head->next->prev = current;
                ll->head->next = current;
            }
            return current; //returns the node where the matching oldspeak word was found
        }
        links += 1; //increments the number of links for each iteration of the lookup
    }
    return NULL; //if it wasn't found, returns NULL
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) { //if a node with the oldspeak doesn't already exist
        //then insert a node with the oldspeak and newspeak into the linked list
        Node *n = node_create(oldspeak, newspeak);
        n->prev = ll->head;
        n->next = ll->head->next;
        ll->head->next->prev = n;
        ll->head->next = n;
        ll->length += 1;
    }
}

void ll_print(LinkedList *ll) {
    for (Node *current = ll->head->next; current->oldspeak != NULL; current = current->next) {
        node_print(current); //prints each node in the linked list
    }
}
