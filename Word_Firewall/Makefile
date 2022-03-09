CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: banhammer

banhammer: banhammer.o node.o bv.o ll.o ht.o bf.o parser.o speck.o
	$(CC) -o banhammer banhammer.o node.o bv.o ll.o ht.o bf.o parser.o speck.o

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

format:
	clang-format -i style=file *c
	clang-format -i style=file *h
clean:
	rm *.o banhammer

scan-build: clean
	scan-build make
