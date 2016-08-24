#include "crypfs.h"

/*
test4 verifica as permissoes do programa (leitura-escrita)
o arquivo sera aberto para LEITURA e logo acontecera
uma tentativa de escrita neste arquivo
*/

int main(){
  cry_desc_t * descritor;
  initfs("host", 30);
  descritor = cry_openfs("host");
  indice_arquivo_t indice1;
  char *buffer = "a";
  indice1 = cry_open(descritor, "arquivo", LEITURA, 'j');
  cry_write(indice1, sizeof(buffer), buffer);
  cry_close(indice1);
  cry_delete(indice1);
  return 0;
}
