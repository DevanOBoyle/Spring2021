Devan O'Boyle
doboyle
Spring 2021
Assignment 5: Hamming Codes

Description: This assignment consists of multiple programs that encode and decode
messages by implementing the Hamming(8,4) code to encrypt and decrypt files. There
are also error and entropy programs used to measure the entropy and error correctability
of the decoder.

Instructions: To build the encoder, type 'make encode'. To build the decoder type 'make decode'.
To build the error program, type 'make error'. To build the entropy program, type 'make entropy'.
To build all of these programs mentioned, type 'make' or 'make all'. Type 'make clean' to remove
all compiler generated files, and type 'make format' to format all of the .c and .h files. To run
the encoder, type './encode'. To run the decoder, type './decode'. Both the encoder and the decoder
have the following command line options: '-i' to specify an input file for the program to read from
(defaults to stdin), '-o' to specify an output file for the program to write to (defaults to stdout),
and '-h' to display the help message. The decoder program also has the added option, '-v', which
prints out the statistics of the decoder such as the total bytes processed, the number of uncorrected
errors, the number of corrected errors, and the ratio of uncorrected errors to total bytes processed.
