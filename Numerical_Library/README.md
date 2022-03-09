Devan O'Boyle
doboyle
Spring 2021
Assignment 2: A Simple Numerical Library

Description: This program implements the functions arcSin, arcCos, arcTan, and Log, and compares them to
each of their corresponding functions in the math.h library by printing out their corresponding values for
each value of x over a given range. The difference between the two functions are also printed out to analyze
why their outputs are different.

Instructions: To build the program, run the Makefile by typing 'make' or 'make all' into the command line.
To run the program type './mathlib-test' and then type one of the following on that same command line: '-a', '-s',
'-c', '-t', '-l', to indicate which function's output you want to run. Type '-a' to run all of the outputs. 
Type '-s' to run only the arcSin function's output. Type '-c' to run arcCos. Type '-t' to run arcTan, and type 
'-l' to run Log. Note that only one of each function's output will run. For instance, typing './mathlib-test -a -s'
won't result in arcSin being printed twice.
