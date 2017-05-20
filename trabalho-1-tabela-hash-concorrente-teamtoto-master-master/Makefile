CC=gcc

CFLAGS=-O2 -lpthread
#CFLAGS=-O0 -lpthread -g 
# para debug

hash_s.o: hash.h hash_s.c
	$(CC) $(CFLAGS) hash_s.c -c

#modificar o Makefile a partir desta linha

main: main.c hash_s.o
	$(CC) $(CFLAGS) main.c hash_s.o -o main

all: main

clean:
	rm *.o main



