#include "crypfs.h"

int main(){
	cry_desc_t * descritor;
	indice_arquivo_t indice;
	initfs("arquivao", 5);
	descritor = cry_openfs("arquivao");
	indice = cry_open(descritor,"bunda",ESCRITA,'n');
	uint32_t tamanho;
	char *buffer = "vai se foder";
	char buffer2[8];
	cry_write(indice,sizeof(buffer),buffer);
	tamanho = cry_read(indice,8,buffer2);
	cry_close(indice);
	cry_delete(indice);
	return 0;
}
