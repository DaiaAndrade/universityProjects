#include "crypfs.h"

/*
test1 cria um arquivo host com 8 blocos
e um unico arquivo que ocupa 1/8 blocos
o que foi encontrado: esse foi o limiar do teste1
devida a memória, tivemos vários stack smashing
*/
int main(){
  cry_desc_t * descritor;
  initfs("host",19000);
  indice_arquivo_t indice1;
  descritor = cry_openfs("host");
  indice1 = cry_open(descritor,"arquivo",ESCRITA,'b');
  long int i;
  char *buffer = "a";
  /*4bytes x 255blocos = 1.044.480*/
  for(i = 0; i<512; i++){
    cry_write(indice1, sizeof(buffer),buffer);
  }
  cry_close(indice1);
  cry_delete(indice1);
  return 0;
}
