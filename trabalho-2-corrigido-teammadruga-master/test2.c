#include "crypfs.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
/*
test2 cria um arquivo host com 8 blocos
e 2 arquivos
*/
void main(int argc, char *argv[]){
  cry_desc_t * descritor;
  indice_arquivo_t indice1;
  indice_arquivo_t indice2;
  initfs("host", 30);
  descritor = cry_openfs("host");
  char buffer[] = "babaca";
  char buffer2[] = "z";
  indice1 = cry_open(descritor,"arquivo1", ESCRITA, 'y');
  indice2 = cry_open(descritor,"arquivo2", ESCRITA, 'q');
  cry_write(indice1, sizeof(buffer), buffer);
  cry_write(indice2, sizeof(buffer2), buffer2);
  int del,del1;
  del = cry_close(indice1);
  del1 = cry_close(indice2);
  del =  cry_delete(indice1);
  del1 = cry_delete(indice2);
}
