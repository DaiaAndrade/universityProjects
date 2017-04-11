#ifndef _BIBFS_H_
#define _BIBFS_H_
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct tabelaALocacao{
    int primPosLivre;    // primeira posição livre // -1 se nenhuma
    int * ponteiroArquivo;    // -1 se vazio
} tabelaAlocacao_t;

tabelaAlocacao_t * initFAT(tabelaAlocacao_t * fileAlocTable);
int initIndices(FILE * arquivo);
void printFAT();
int descritorLivre ();
int existe(char * nome);
int aberto(arquivo_aberto_t * arquivos, char * nome, int acesso, char deslocamento);
int abertoLivre(arquivo_aberto_t * abertos);
int atualizarFAT(int blocoOcupado);
int findLivre();
FILE * buscaFileHandler(FILE *host, int bloco);
void decripta(char deslocamento, char * bufferEntrada, char * bufferSaida);
void encripta(char deslocamento, char * bufferEntrada, char * bufferSaida);
#endif
