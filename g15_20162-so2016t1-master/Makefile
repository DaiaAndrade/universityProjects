CC=gcc

CFLAGS=-O2 -lpthread -Wall
#CFLAGS=-O0 -lpthread -g # para debug

calcula.o: calcula.h calcula.c
	$(CC) $(CFLAGS) calcula.c -c

calculat.o: calcula.h calculat.c
	$(CC) $(CFLAGS) calculat.c -c

teste1: calcula.o teste1.c simpletest.h
	$(CC) $(CFLAGS) calcula.o teste1.c -o teste1
	./teste1

teste1t:	calculat.o teste1t.c simpletest.h
	$(CC) $(CFLAGS) calculat.o teste1t.c -o teste1t -lpthread
	./teste1t

all: teste1 teste1t

clean:
	rm teste1t.o teste1t calcula.o teste1 teste1.o calculat.o
