#include "hash.h"

int main(){
	hash_t * hash;
	elemento_lista_t * lista;
	hash = ht_init(10);
	conteudo_t * h[10];
	printf("Hash Criada\n");
	//ht_lista_elementos(hash);
	printf("\n");
	printf("Inserindo conteúdo de 0 a 9\n");
	unsigned long int i = 0;
	for (i = 0; i < 10; ++i)
	{
		h[i] = i;
		ht_insere_conteudo(hash,h[i]);
	}
	printf("\n");
	printf("Conteúdo inserido:\n");
	ht_lista_elementos(hash);
	printf("\n");
	printf("Buscando chaves pares:\n");
	for (i = 0; i < 10; i+=2)
	{
		entrada_hash_t * chave;
		//printf("Chave: %i\n", i);
		chave = ht_busca_chave(hash,i);
		printf("Chave: %lu. Conteúdo: %lu\n", chave->chave, chave->conteudo);
	}
	printf("\n");
	printf("Buscando conteúdos ímpares:\n");
	for (i = 1; i < 10; i+=2)
	{
		entrada_hash_t * conteudo;
		//printf("Conteúdo: %i\n", i);
		conteudo = ht_busca_conteudo(hash,i);
		printf("Chave: %lu. Conteúdo: %lu\n", conteudo->chave, conteudo->conteudo);
	}
	/*printf("\n");
	printf("Hash Atual:\n");
	ht_lista_elementos(hash);*/
	printf("\n");
	printf("Removendo Conteúdos pares\n");
	entrada_hash_t * entrada[5];
	for (i = 0; i < 10; i+=2)
	{
		entrada[i]= ht_busca_conteudo(hash,i);
	}
	for (i = 0; i < 10; i+=2)
	{
		ht_remove_elemento(hash,entrada[i]);
	}
	printf("\n");
	printf("Hash com conteúdo removido:\n");
	ht_lista_elementos(hash);
	printf("\n");
	printf("Inserindo conteúdo...\n");
	for (i = 1; i < 10; i+=2)
	{
		unsigned long int add = 1;
		h[i] = h[i] + add;
		printf("%lu\n", h[i]);
		ht_insere_conteudo(hash,(h[i]));
	}
	printf("\n");
	printf("Hash Atual:\n");
	ht_lista_elementos(hash);
	printf("\n");

	printf("Ponteiro para primeiro elemento da lista:\n");
	lista = ht_lista(hash);
	printf("Trabalho finalizado, excluindo hash.\n");
	ht_remove(hash);

	return 0;
}
