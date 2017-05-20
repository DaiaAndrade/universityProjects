#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

chave_t geraIndice(chave_t valor);

hash_t * ht_init(unsigned long int tam){
	hash_t *hash;
	hash = (hash_t *)malloc (sizeof(hash_t)*tam);
	hash->numero_elementos = tam;
	hash->armazenamento = (entrada_hash_t *)malloc (sizeof(entrada_hash_t)*tam);
	unsigned long int i;
	if (hash->armazenamento == NULL)
	{
		perror ("Erro de alocação.");
		return NULL;
	}
	for (i = 0; i < hash->numero_elementos; i++)
	{
		hash->armazenamento[i].chave = i;
		hash->armazenamento[i].conteudo = NULL;
		hash->armazenamento[i].proximo = NULL;
	}
	return hash;

} 
void ht_remove(hash_t * ht){
	unsigned long int i;
	for (i=0; i < ht->numero_elementos; i++)
	{
		if (ht->armazenamento[i].proximo != NULL)
		{
			entrada_hash_t * aux = ht->armazenamento[i].proximo;
			while(aux != NULL){
				ht->armazenamento[i].proximo = ht->armazenamento[i].proximo->proximo;
				free(aux);
				aux = ht->armazenamento[i].proximo;
			}
		}
	}
	free(ht->armazenamento);
	free(ht);
}

void ht_lista_elementos(hash_t * ht){
	entrada_hash_t * aux = ht->armazenamento;
	entrada_hash_t * aux2;
	unsigned long int i;
	for (i = 0; i < ht->numero_elementos; i++)
	{
		if (aux[i].proximo == NULL)
		{
			printf("Chave: %lu. Conteudo: %lu.\n", aux[i].chave,aux[i].conteudo);
		}
		else{
			printf("Chave: %lu. Conteudo: %lu.\n", aux[i].chave,aux[i].conteudo);
			entrada_hash_t * aux2 = aux[i].proximo;
			while(aux2 != NULL){
				printf(" Conteudo: %lu.\n", aux2->conteudo);
				aux2 = aux2->proximo;
			}
		}
	}
}

elemento_lista_t * ht_lista(hash_t * ht){
	elemento_lista_t *lista = (elemento_lista_t *)malloc (sizeof(elemento_lista_t)* ht->numero_elementos);
	entrada_hash_t *aux = ht->armazenamento;
	lista->elemento = ht->armazenamento;
	lista->proximo = (elemento_lista_t *)ht->armazenamento->proximo;
	elemento_lista_t *aux2 = lista->proximo;
	do{
		aux = aux->proximo;
		aux2 = aux2->proximo;
	}while(aux!=NULL);
	printf("Chave: %lu. Conteudo: %lu\n", lista->elemento->chave, lista->elemento->conteudo);
	return lista;
}

int ht_insere_conteudo(hash_t * ht, conteudo_t * conteudo){
	chave_t index = geraIndice(conteudo)%ht->numero_elementos;
	if(ht->armazenamento[index].conteudo == NULL){
		ht->armazenamento[index].conteudo = conteudo;
		return 1;
	}
	else if(ht->armazenamento[index].conteudo != NULL){
		if (ht->armazenamento[index].proximo == NULL)
		{
			entrada_hash_t * newEntry = malloc(sizeof(entrada_hash_t));
			newEntry->chave = index;
			newEntry->conteudo = conteudo;
			newEntry->proximo = NULL;
			ht->armazenamento[index].proximo = newEntry;
			return 1;
		}
		else{
			entrada_hash_t *start;
			start = ht->armazenamento[index].proximo;
			entrada_hash_t * newEntry = malloc(sizeof(entrada_hash_t));
			newEntry->chave = index;
			newEntry->conteudo = conteudo;
			newEntry->proximo = start;
			ht->armazenamento[index].proximo = newEntry;
			return 1;
		}
	}
	else{
		printf("Não foi possível inserir");
		return 0;
	}
}

entrada_hash_t * ht_busca_chave(hash_t * ht, chave_t chave){
	entrada_hash_t *aux = &ht->armazenamento[chave];
	if (chave < ht->numero_elementos)
	{
		return aux;
	}
	else{
		printf("Chave não encontrada.\n");
		return NULL;
	}
}

entrada_hash_t * ht_busca_conteudo(hash_t * ht, conteudo_t * conteudo){
	entrada_hash_t * aux = ht->armazenamento;
	unsigned long int i = geraIndice(conteudo)%ht->numero_elementos;
	if(aux[i].conteudo == conteudo){
			entrada_hash_t * returner = &aux[i];
			return returner;
	}
	else if(aux[i].proximo != NULL){
		entrada_hash_t * aux2 = aux[i].proximo;
		while(aux2 != NULL){
			if (aux2->conteudo == conteudo){
				return aux2;
			}
			aux2 = aux2->proximo;
		}
	}
	else{
		printf("Conteúdo não encontrado.\n");
		return NULL;
	}
}

int ht_remove_elemento(hash_t * ht, entrada_hash_t * entrada){
	entrada_hash_t * aux = ht->armazenamento;
	chave_t chave = entrada->chave;
	conteudo_t * conteudo = entrada->conteudo;
	struct entrada_hash * proximo;
	//printf("Chave: %lu. Conteúdo: %lu\n", chave,conteudo);
	if(aux[chave].chave == chave && aux[chave].conteudo == conteudo){
		if (aux[chave].proximo == NULL)
		{
			aux[chave].conteudo = NULL;
			return 1;
		}
		else if (aux[chave].proximo != NULL){
			entrada_hash_t * anterior = aux[chave].proximo;
			aux[chave].conteudo = anterior->conteudo;
			aux[chave].proximo = anterior->proximo;
			free(anterior);
			return 1;
		}
		else{
			printf("Elemento não pode ser removido.\n");
			return 0;
		}
	}
	else if(aux[chave].conteudo != conteudo && aux[chave].chave == chave){
		if (aux[chave].proximo == NULL){
			printf("Elemento não pode ser removido.\n");
			return 0;
		}
		else{
			entrada_hash_t * anterior = aux[chave].proximo;
			entrada_hash_t * proximo = aux[chave].proximo->proximo;
			if (anterior->conteudo == conteudo){
				aux[chave].proximo = proximo;
				free(anterior);
				return 1;
			}
			else{
				do{
					anterior = anterior->proximo;
					proximo = proximo->proximo;
					if(proximo == NULL && proximo != entrada){
						perror("Elemento não pode ser removido.\n");
						return 0;
					}
				}while(proximo != entrada);
				anterior->proximo = proximo->proximo;
				proximo->proximo = &proximo+1;
				free(proximo);
				return 1;
			}
		}
	}
	else{
		printf("Elemento não pode ser removido.\n");
		return 0;
	}
}

chave_t geraIndice(chave_t valor){
	chave_t final;
	final = valor*31;
	return final;
}
