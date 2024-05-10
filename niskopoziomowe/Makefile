CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: main

main: main.o mylib.o
	$(CC) $(CFLAGS) -o main main.o mylib.o

main.o: main.c mylib.h
	$(CC) $(CFLAGS) -c main.c

mylib.o: mylib.c mylib.h
	$(CC) $(CFLAGS) -c mylib.c

clean:
	rm -f *.o main

