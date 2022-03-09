//Devan O'Boyle
//Assignment 7: The Great Firewall of Santa Cruz

#include "bf.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "parser.h"

#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORD    "([a-zA-Z0-9_])+(('|-)([a-zA-Z0-9_])+)*"
#define OPTIONS "ht:f:ms"

int main(int argc, char **argv) {
    uint32_t hash_size = 10000; //initializes the size of the hash table
    uint32_t bloom_size = 1048576; //initializes the size of the bloom filter
    bool mtf = false; //keeps track of whether or not move to front will be used
    bool stats = false; //keeps track of whether or not statistics will be printed
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints the help message
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -m           Enable move-to-front rule.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            break;
        case 't':
            //sets the hash table size
            hash_size = atoi(optarg);
            break;
        case 'f':
            //sets the bloom filter size
            bloom_size = atoi(optarg);
            break;
        case 'm':
            //move to front set to on
            mtf = true;
            break;
        case 's':
            //printing statistics set to on
            stats = true;
            break;
        }
    }

    BloomFilter *bf = bf_create(bloom_size);
    HashTable *ht = ht_create(hash_size, mtf);
    char bad[4096];
    FILE *badspeak = fopen("badspeak.txt", "r"); //opens the file
    while (fscanf(badspeak, "%s\n", bad) != EOF) { //reads in the words from badspeak
        bf_insert(bf, bad); //inserts the bad word into the bloom filter
        ht_insert(ht, bad, NULL); //inserts into the hash table
    }
    fclose(badspeak);
    char old[4096];
    char new[4096];
    FILE *newspeak = fopen("newspeak.txt", "r"); //opens the file
    while (fscanf(newspeak, "%s %s\n", old, new) != EOF) { //reads in the words from newspeak
        bf_insert(bf, old); //inserts the oldspeak word into the bloom filter
        ht_insert(ht, old, new); //inserts the oldspeak and newspeak word into the hash table
    }
    fclose(newspeak);
    LinkedList *badwords = ll_create(mtf);
    LinkedList *rightwords = ll_create(mtf);
    bool thought_crime = false;
    bool wrongthink_crime = false;
    regex_t regular_exp;
    if (regcomp(
            &regular_exp, WORD, REG_EXTENDED)) { //checks to see if the regular expression compiles
        fprintf(stderr, "Failed to compile regex. \n");
        return 1;
    }
    char *word;
    while ((word = next_word(stdin, &regular_exp))
           != NULL) { //reads in each word using the regular expression
        for (uint32_t i = 0; i < strlen(word); i++) {
            if (word[i] >= 65 && word[i] <= 90) {
                word[i] = word[i] + 32; //lowercases all uppercase letters for comparison
            }
        }
        if (bf_probe(bf, word) == true) { //checks if the word is in the bloom filter
            Node *n = ht_lookup(ht, word); //if so then it looks up the word in the hash table
            if (n != NULL) {
                if (n->newspeak == NULL) { //if there is no newspeak, then it's a bad word
                    thought_crime = true;
                    ll_insert(badwords, word, NULL); //inserts the word to a list of bad words
                } else { //otherwise it is a word with a newspeak variant
                    wrongthink_crime = true;
                    ll_insert(rightwords, word,
                        n->newspeak); //inserts the word to a list of corrected words
                }
            }
        }
    }
    clear_words();
    regfree(&regular_exp);

    if (stats == true) {
        //prints out the statistics
        double seek_length = ((double) links) / seeks;
        double hash_load = 100 * ((double) ht_count(ht)) / ht_size(ht);
        double bf_load = 100 * ((double) bf_count(bf)) / bf_size(bf);
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %lf\n", seek_length);
        printf("Hash table load: %lf%%\n", hash_load);
        printf("Bloom filter load: %lf%%\n", bf_load);
        return 1;
    }

    if (thought_crime
        && wrongthink_crime) { //if bad words and words with newspeak variants were said
        printf("%s", mixspeak_message); //then print a mixspeak message
        ll_print(badwords);
        ll_print(rightwords);
    } else if (thought_crime) { //if only bad words were said
        printf("%s", badspeak_message); //then print a badspeak message
        ll_print(badwords);
    } else if (wrongthink_crime) { //if only words with newspeak variants were said
        printf("%s", goodspeak_message); //then print a goodspeak message
        ll_print(rightwords);
    } //otherwise don't print anything at all

    //deletes all of the structs
    ll_delete(&badwords);
    ll_delete(&rightwords);
    ht_delete(&ht);
    bf_delete(&bf);
    return 0;
}
