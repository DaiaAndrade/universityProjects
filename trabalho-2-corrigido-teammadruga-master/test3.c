#include "crypfs.h"

/*
test3 verifica todas as funcoes implementadas do crypfs.h
*/

void main(int argc, char *argv[]){
  cry_desc_t * descritor;
  initfs("host", 256);
  descritor = cry_openfs("host");
  indice_arquivo_t indice1;
  char *buffer = "a";
  char buffer_aux[4];
  int del,del1;
  indice1 = cry_open(descritor, "arquivo", ESCRITA, 'j');
  /*for (size_t i = 0; i < 1023; i++) {
      cry_write(indice1, sizeof(buffer), buffer);
  }*/
  cry_write(indice1,4096,buffer);
  cry_read(indice1, sizeof(buffer), buffer_aux);
  del1 = cry_close(indice1);
  del = cry_delete(indice1);
}
