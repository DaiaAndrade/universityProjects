CC=gcc
CFLAGS=-std=c11 -Wall

cryfs.o: bibfs.h cryfs.h cryfs.c
	$(CC) $(CFLAGS) cryfs.c -c

teste: teste.c cryfs.o simpletest.h
	$(CC) $(CFLAGS) teste.c cryfs.o -lm -o teste
	./teste

silver: silver.c cryfs.o simpletest.h
	$(CC) $(CFLAGS) silver.c cryfs.o -lm -o silver
	./silver

clean:
	rm *.o teste cripto journal silver kk00test*
