CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode error entropy

encode: encode.o bv.o bm.o hamming.o
	$(CC) -o encode encode.o bv.o bm.o hamming.o

decode: decode.o bv.o bm.o hamming.o
	$(CC) -o decode decode.o bv.o bm.o hamming.o

error: error.o
	$(CC) -o error error.o

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

format:
	clang-format -i -style=file *c *h 

clean:
	rm *.o encode decode error entropy

scan-build: clean
	scan-build make
