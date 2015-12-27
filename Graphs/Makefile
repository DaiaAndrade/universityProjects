main:	main.o graphImplementation.o pairImplementation.o
		g++ -o main main.o graphImplementation.o pairImplementation.o

main.o:	main.cpp
		g++ -c main.cpp

graphImplementation.o:	graphImplementation.cpp graphHeader.h
		g++ -c graphImplementation.cpp graphHeader.h

pairImplementation.o:	pairImplementation.cpp graphHeader.h
		g++ -c pairImplementation.cpp graphHeader.h
clean:
		rm *.o *h.gch main
