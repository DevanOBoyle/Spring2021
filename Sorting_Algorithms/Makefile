CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o stack.o queue.o quick.o
	$(CC) -o sorting sorting.o bubble.o shell.o stack.o queue.o quick.o

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

format: 
	clang-format -i -style=file *c *h
	
clean:
	rm *.o sorting

scan-build: clean
	scan-build make
