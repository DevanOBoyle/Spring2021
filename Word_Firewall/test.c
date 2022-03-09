#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *word = "hello";
    char *word2 = "hello2";
    //Node *n = node_create(word, NULL);
    bool mtf = false;
    LinkedList *ll = ll_create(mtf);
    ll_insert(ll, word, word2);
    ll_print(ll);
    //node_print(n);
    ll_delete(&ll);
    return 0;
}
