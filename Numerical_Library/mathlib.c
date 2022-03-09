//Devan O'Boyle
//Assignment 2: A simple numerical library
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define EPSILON 1E-10
#define PI_2    M_PI_2

//Absolute Value Function
//Takes in a double value
//Returns the absolute value of it
double Abs(double x) {
    if (x < 0) { // checks if the number is less than 0
        x *= -1; // if so, makes it positive
    }
    return x;
}

//Square Root Function
//Takes in a double value
//Returns the square root approximation of that value
//Code inspired from sqrt.c on Piazza by Professor Long
double Sqrt(double x) {
    double y = 1;
    //uses Newton's method to compute an approximation for sqrt
    for (
        double guess = 0.0; Abs(y - guess) > EPSILON;
        y
        = (y + x / y)
          / 2.0) { //exits once the difference between the current guess and the previous guess is less than the value of epsilon
        guess = y;
    }
    return y;
}

//Exponent Function
//Takes in a double value
//Returns the exponent approximation (e^x) of that value
//Code inspired from exp.c on Piazza by Professor Long
double Exp(double x) {
    double term = 1.0;
    double sum = 1.0;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

//Arcsin function
//Takes in a double value
//Returns the arcsin of that value
double arcSin(double x) {
    double sum = 0.0; // taylor approximation that is returned at the end
    double k = 0.0; // k value
    double term = 1.0; // current term
    double prev = 1.0; // previous term
    bool extrema = false;
    double new_x = x;
    if (x < -0.707
        || x > 0.707) { //checks if input is within the range to use arccos function instead
        new_x = Sqrt(1 - (x * x)); //if so, creates a new value of x to go in the arccos function
        extrema = true; //lets the program know later to perform the arccos computation
    }
    //taylor series approximation
    while (
        prev > EPSILON) { //if the last term is equal to or less than epsilon the loop should exit
        for (double n = 1.0; n <= k;
             n += 1) { //computes the factorial by multiplying each divided term
            term *= ((2 * n - 1) / (2 * n));
        }
        double p = 2 * k + 1; // a value to store 2*k+1
        term /= p;
        for (double n = 1.0; n <= p; n += 1) { //computes x^(2k+1)
            term *= Abs(new_x); //multiplies x to the term to keep the value from getting too big
        }
        k += 1;
        sum += term; //adds the term to the sum
        prev = term; //sets the previous term
        term = 1.0; //resets the current term
    }
    if (extrema == true) { //if computer arccos computation
        sum = (PI_2) -sum; //then subtract sum from pi/2
    }
    if (x < 0) { //if x is negative
        sum = -sum; //the arcsin should be a negative value
    }
    return sum;
}

//Arccos function
//Takes in a double value
//Returns the arccos of that value
double arcCos(double x) {
    return (PI_2) -arcSin(x); //uses trig identity to call arcsin to compute arccos
}

//Arctan function
//Takes in a double value
//Returns the arctan of that value
double arcTan(double x) {
    //uses trig identity to call arcsin
    double i = x * x + 1; // creates a variable i that can be plugged into arcsin to return arctan
    i = Sqrt(i);
    i = x / i;
    return arcSin(i);
}

//Log function
//Takes in a double value
//Returns the log of that value
double Log(double x) {
    double y = 1.0; //initial guess
    double t = 0.0; //intial computational term
    double prev = Exp(y); //initializes the previous term
    while (
        Abs(prev - x)
        > EPSILON) { // continues while the difference between the previous term and the input x are greater than epsilon
        t = ((x - prev) / prev);
        y += t;
        prev = Exp(y); //resets the previous term
    }
    return y;
}
