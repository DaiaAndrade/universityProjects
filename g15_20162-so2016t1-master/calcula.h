#ifndef CALCULA_H_
#define CALCULA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct buffer{
	char string[256];
} buffer_t;

/*
    arquivo: nome do arquivo com path
    substring: substring a ser procurada
    numthreads: numero de threads que são consumidoras
*/
unsigned int ocorrencias(char * arquivo, char * substring, int numthreads);



#endif
