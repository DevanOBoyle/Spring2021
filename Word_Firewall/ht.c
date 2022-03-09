#include "ll.h"
#include "node.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
} HashTable;

//based on pseudocode provided by Sahiti during her lab section
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable)); //allocates memory for the hash table
    if (ht) {
        //Leviathan
        ht->salt[0] = 0x9846e4f157fe8840; //sets the salts
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(
            size, sizeof(LinkedList *)); //allocates memory for the list of linked lists
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            if ((*ht)->lists[i] != NULL) {
                ll_delete(&(*ht)->lists[i]); //deletes each linked list
            }
        }
        free((*ht)->lists); //frees the list of linked lists
        (*ht)->lists = NULL;
        free(*ht); //frees the hash table
        *ht = NULL;
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size; //gets the index using the hash
    if (ht->lists[index] == NULL) { //if no linked list with the index exists
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak); //otherwise lookup the oldspeak in the linked list
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == NULL) { //if no linked list exists at the index
        ht->lists[index] = ll_create(ht->mtf); //create a new linked list
    }
    ll_insert(ht->lists[index], oldspeak,
        newspeak); //insert the oldspeak and newspeak into the linked list
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) { //if a linked list exists at the index
            count += 1; //increment the count
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            ll_print(ht->lists[i]); //prints out each linked list in the hash table
        }
    }
}
