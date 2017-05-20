#include "hash.h"
#include <stdlib.h>
#include <assert.h>

void imprime(elemento_lista_t *lista){
  elemento_lista_t *anterior;
  while(lista){
    printf("Chave %lu -- Conteudo %lu -- Endereco %p\n",lista->elemento->chave, *lista->elemento->conteudo, (void *) lista->elemento);
    anterior = lista;
    lista = lista->proximo;
    free(anterior);
  }
}

int verifica_0_9(hash_t *ht){
  unsigned long u;
  for(u=0; u<10; u++){
    if (!ht_busca_conteudo(ht, u))
      return 0;
  }
  return 1;
}

int verifica_impares(hash_t *ht){
  unsigned long int u;
  for(u=1; u<10; u=u+2){
    if (!ht_busca_conteudo(ht, u))
      return 0;
  }
  for(u=0; u<10; u=u+2){
    if (ht_busca_conteudo(ht, u))
      return 0;
  }

  return 1;
}

int verifica_impares_colisoes(hash_t *ht){
  unsigned long int u;
  for(u=1; u<20; u=u+2){
    if (!ht_busca_conteudo(ht, u))
      return 0;
  }
  for(u=0; u<20; u=u+2){
    if (ht_busca_conteudo(ht, u))
      return 0;
  }

  return 1;
}

int main(int argc, char ** argv){
  elemento_lista_t * lista;
  int i;
  hash_t * ht = ht_init(0);
  //assert(ht==NULL);

  ht = ht_init(10);
  assert(ht);

  /* insere 10 elementos sem colisao */
  for(i=0; i<10; i++){
    conteudo_t * conteudo = (conteudo_t *) calloc(1, sizeof(conteudo_t));

    assert(conteudo);
    conteudo = i;
    ht_insere_conteudo(ht, conteudo);
  }
  printf("Teste ate 10 %s\n", verifica_0_9(ht)?"OK":"ERRO");

  //
  // printf("Lista \n");
  // /* imprime */
  // lista = ht_lista(ht);
  // assert(lista);
  //
  // imprime(lista);
  /* remove os pares */
  for(i=0; i<10; i+=2){
    conteudo_t * cont = (conteudo_t *) malloc(sizeof(conteudo_t));
    assert(cont);
    cont = i;
    entrada_hash_t * elem = ht_busca_conteudo(ht,cont);
    assert(elem);
    ht_remove_elemento(ht, elem);
    //free(elem);
  }
  // /* imprime */
  // lista = ht_lista(ht);
  // assert(lista);
  
  printf("Teste impares %s\n", verifica_impares(ht)?"OK":"ERRO");
  

  /* colisoes nos impares */
  for(i=1; i<10; i+=2){
    conteudo_t * cont = (conteudo_t *) malloc(sizeof(conteudo_t));
    assert(cont);
    cont = i;
    ht_insere_conteudo(ht,cont);
    cont = cont + 1;
    ht_insere_conteudo(ht,cont);
  }
  //ht_lista_elementos(ht);
  // printf("Lista final\n");
  //
  // imprime(ht_lista(ht));
  printf("Teste impares e colisoes %s\n", verifica_impares_colisoes(ht)?"OK":"ERRO");

  /* final cleanout */
  ht_remove(ht);

  return 0;
}
