CC = gcc
CFLAGS = -O3 -std=c99 -Wall

solve: solve.o
	$(CC) $(CFLAGS) solve.o -o solve

solve.o: solve.c
	$(CC) $(CFLAGS) -c solve.c
