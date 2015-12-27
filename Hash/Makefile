main:	main.o tabelaHash.o
		g++ -o main main.o tabelaHash.o

tabelaHash.o:	tabelaHash.cpp
		g++ -c tabelaHash.cpp

main.o:	main.cpp hashtable.h
		g++ -c main.cpp hashtable.h

clean:
		rm *.o *h.gch main
