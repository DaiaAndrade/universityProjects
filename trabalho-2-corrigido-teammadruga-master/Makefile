CC=gcc

#CFLAGS=-O2 -lm

CFLAGS=-O0 -g -lm # para debug

crypfs_salvo.o: crypfs.h crypfs.c
	$(CC) $(CFLAGS) crypfs.c -c

test1: test1.c crypfs.o
	$(CC) test1.c crypfs.o -o test1 $(CFLAGS)
	./test1
	rm *.o test1 host

test2: test2.c crypfs.o
	$(CC) test2.c crypfs.o -o test2 $(CFLAGS)
	./test2
	rm *.o test2 host

test3: test3.c crypfs.o
	$(CC) test3.c crypfs.o -o test3 $(CFLAGS)
	./test3
	rm *.o test3 host

test4: test4.c crypfs.o
	$(CC) test4.c crypfs.o -o test4 $(CFLAGS)
	./test4
	rm *.o test4 host

pilla: tests3.c crypfs.o
	$(CC) tests3.c crypfs.o -o pilla $(CFLAGS)
	./pilla
	make mauricio


##PARA EXECUÇÕES INICIAIS
main: main.c crypfs.o
	$(CC) main.c crypfs.o -o main $(CFLAGS)
	./main
	rm *.o main

all: main

mauricio:
	rm a* *.o pilla
