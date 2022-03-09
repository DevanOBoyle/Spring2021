//Devan O'Boyle
//April 18, 2021
//Assignment 2: A Small Numberical Library

#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

int main(int argc, char **argv) {
    int opt = 0;
    //booleans to make sure each function only prints once
    bool case_all = false;
    bool case_s = false;
    bool case_c = false;
    bool case_t = false;
    bool case_l = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            //checks if case a hasn't already been called
            if (case_all == true) {
                break;
            }
            //checks if case s hasn't already been called
            if (case_s == false) {
                printf("  x            arcSin           Library        Difference\n");
                printf("  -            ------           -------        ----------\n");
                //iterates through values of range -1 to 1
                //prints each value of the arcSin function and the math library's asin function as well as the difference between the two
                for (double x = -1.0; x <= 1.0; x += 0.1) {
                    printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcSin(x), asin(x),
                        asin(x) - arcSin(x));
                }
            }
            //checks if case c hasn't already been called
            if (case_c == false) {
                printf("  x            arcCos           Library        Difference\n");
                printf("  -            ------           -------        ----------\n");
                for (double x = -1.0; x <= 1.0; x += 0.1) {
                    printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcCos(x), acos(x),
                        acos(x) - arcCos(x));
                }
            }
            //checks if case t hasn't already been called
            if (case_t == false) {
                printf("  x            arcTan           Library        Difference\n");
                printf("  -            ------           -------        ----------\n");
                for (double x = 1.0; x <= 10.0; x += 0.1) {
                    printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcTan(x), atan(x),
                        atan(x) - arcTan(x));
                }
            }
            //checks if case l hasn't already been called
            if (case_l == false) {
                printf("  x            Log              Library        Difference\n");
                printf("  -            ---              -------        ----------\n");
                for (double x = 1.0; x <= 10.0; x += 0.1) {
                    printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Log(x), log(x),
                        log(x) - Log(x));
                }
            }
            case_all = true;
            break;
        case 's':
            //checks if case all and case s haven't been called already
            if (case_all == true || case_s == true) {
                break;
            }
            printf("  x            arcSin           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = -1.0; x <= 1.0; x += 0.1) {
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcSin(x), asin(x),
                    asin(x) - arcSin(x));
            }
            case_s = true;
            break;
        case 'c':
            //checks if case all and case c haven't been called already
            if (case_all == true || case_c == true) {
                break;
            }
            printf("  x            arcCos           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = -1.0; x <= 1.0; x += 0.1) {
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcCos(x), acos(x),
                    acos(x) - arcCos(x));
            }
            case_c = true;
            break;
        case 't':
            //checks if case all and case t haven't been called already
            if (case_all == true || case_t == true) {
                break;
            }
            printf("  x            arcTan           Library        Difference\n");
            printf("  -            ------           -------        ----------\n");
            for (double x = 1.0; x <= 10.0; x += 0.1) {
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcTan(x), atan(x),
                    atan(x) - arcTan(x));
            }
            case_t = true;
            break;
        case 'l':
            //checks if case all and case l haven't been called already
            if (case_all == true || case_l == true) {
                break;
            }
            printf("  x            Log              Library        Difference\n");
            printf("  -            ---              -------        ----------\n");
            for (double x = 1.0; x <= 10.0; x += 0.1) {
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, Log(x), log(x), log(x) - Log(x));
            }
            case_l = true;
            break;
        }
    }
    return 0;
}
