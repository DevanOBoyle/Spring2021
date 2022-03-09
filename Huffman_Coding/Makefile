CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode entropy

encode: encode.o node.o pq.o stack.o code.o huffman.o io.o
	$(CC) -o encode encode.o node.o pq.o stack.o code.o huffman.o io.o

decode: decode.o node.o pq.o stack.o code.o huffman.o io.o
	$(CC) -o decode decode.o node.o pq.o stack.o code.o huffman.o io.o

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

format:
	clang-format -i -style=file *c
	clang-format -i -style=file *h

clean:
	rm *.o encode

scan-build: clean
	scan-build make
