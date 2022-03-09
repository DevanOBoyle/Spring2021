// Devan O'Boyle
// April 11, 2021
// Contains the source code for the game Left, Right, and Center

#include "philos.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Code from assignment PDF

// Obtains the position of the player to the left of the current player
// position: the unsigned integer that gives the position of the current player
// players: the unsigned integer that gives the total amount of players
// Returns the position to the left of the current player
static inline uint8_t get_left(uint8_t position, uint8_t players) {
    return ((position + players - 1) % players);
}

// Obtains the position of the player to the right of the current player
// position: the unsigned integer that gives the position of the current player
// players: the unsigned integer that gives the total amount of players
// Returns the position to the left of the current player
static inline uint8_t get_right(uint8_t position, uint8_t players) {
    return ((position + 1) % players);
}

int main(void) {
    int32_t total_players; // total number of players
    int64_t seed; // signed integer to set the seed for the randomizer

    // Code inspired by the vampire code
    // Takes input for the random seed
    // If the input isn't valid then it prints out an invalid statement
    printf("Random Seed: ");
    if (scanf("%ld", &seed) < 1 || seed < 0) {
        printf("Invalid random seed.\n");
        return 1;
    }

    // Asks for the amount of players
    // If the input isn't within the range 1 to 14, or if it isn't a number
    // then an invalid statement is printed
    printf("How many players? ");
    if (scanf("%d", &total_players) < 1 || total_players < 1 || total_players > 14) {
        fprintf(stderr, "Invalid number of players.\n");
        return 1;
    }

    uint32_t t_players = total_players;
    srandom(seed); // sets the seed

    uint32_t current_players
        = t_players; // initializes the current players in the game to the total amount of players
    char *list_players
        [t_players]; // declares a char * list of players with the size of the total amount of players
    bool current_list_players[t_players]; // keeps track of which players are still in the game
    uint32_t list_money[t_players]; // keeps track of how much money each player has

    // iterates through the total amount of players
    for (uint32_t i = 0; i < t_players; i = i + 1) {
        list_players[i] = philosophers[i]; // adds a philosopher to the list of players
        list_money[i] = 3; // gives every player $3 to start out with
        current_list_players[i] = true; // initializes each player as being in the game
    }

    uint32_t center
        = 0; // initializes the unsigned int to keep track of the money in the center pot

    // Code from assignement PDF
    // initializes the different faces of the die to be rolled
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

    // infinite loop that ends when there is only one person left in the game
    while (current_players > 1) {
        // iterates through each player
        for (uint32_t index = 0; index < t_players; index = index + 1) {
            //checks to see if the player was brought back into the game
            if (list_money[index] > 0) {
                if (current_list_players[index] == false) {
                    current_list_players[index] = true; // puts that player back into the game
                    current_players
                        = current_players + 1; // adds 1 back to the number of current players
                }
                printf("%s rolls...", list_players[index]);
                uint32_t current_money
                    = list_money[index]; // saves the player's current amount of money
                for (uint32_t i = 1; i <= current_money && i <= 3; i = i + 1) {
                    uint32_t rolled_value
                        = random() % 6; // gets the next pseudorandom number for the dice roll
                    // checks if the die rolled the left face
                    if (die[rolled_value] == LEFT) {
                        list_money[index]
                            = list_money[index] - 1; // subtracts $1 from current player
                        list_money[get_left(index, t_players)]
                            = list_money[get_left(index, t_players)]
                              + 1; // adds $1 to the player to the left
                        printf(" gives $1 to %s", list_players[get_left(index, t_players)]);
                        // checks if the die rolled the right face
                    } else if (die[rolled_value] == RIGHT) {
                        list_money[index]
                            = list_money[index] - 1; // subtracts $1 from the current player
                        list_money[get_right(
                            index, t_players)] // adds $1 to the player to the right
                            = list_money[get_right(index, t_players)] + 1;
                        printf(" gives $1 to %s", list_players[get_right(index, t_players)]);
                        // checks if the die rolled the center face
                    } else if (die[rolled_value] == CENTER) {
                        list_money[index]
                            = list_money[index] - 1; // subtracts $1 from the current player
                        center = center + 1; // adds $1 to the center pot
                        printf(" puts $1 in the pot");
                        // checks if the die rolled a pass
                    } else if (die[rolled_value] == PASS) {
                        printf(" gets a pass");
                    }
                    // if the player runs out of money, then they are no longer playing and the loop breaks
                    if (list_money[index] == 0) {
                        current_list_players[index] = false;
                        current_players = current_players - 1;
                        break;
                    }
                }

                printf("\n");
                // checks if the player has no money, but has not yet been declared out of the game yet
            } else if (current_list_players[index] == true) {
                current_players = current_players - 1;
                current_list_players[index] = false;
            }
            // checks if there is only 1 player left
            if (current_players == 1) {
                // if so, checks to see if there wasn't another player that wasn't recently added back in
                for (uint32_t t = 0; t < t_players; t = t + 1) {
                    if (list_money[t] > 0 && t != index && current_list_players[t] == false) {
                        current_players = current_players + 1;
                        current_list_players[t] = true;
                    }
                }
                if (current_players == 1) {
                    break;
                }
            }
        }
    }

    uint32_t winner_index; // initialized unsigned integer to hold the index of the winner
    // loops through the find the index of the winner
    for (uint32_t e = 0; e < t_players; e = e + 1) {
        if (current_list_players[e] == true) {
            winner_index = e;
        }
    }
    // prints the winner, the money in the pot they won, and the amount of money they still have
    printf("%s wins the $%u pot with $%u left in the bank!\n", list_players[winner_index], center,
        list_money[winner_index]);
    return 0;
}
