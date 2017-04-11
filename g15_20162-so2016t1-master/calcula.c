#include "calcula.h"

#define SIZE 20

buffer_t buffer[SIZE];

void produtor(FILE *fp, buffer_t * buffer);
int getLivre(buffer_t * buffer);
unsigned int consumidor(buffer_t * buffer, char * substring, unsigned int soma);

unsigned int ocorrencias(char * arquivo, char * substring, int numthreads){
    unsigned int n_ocorrencias;
    n_ocorrencias = 0;
    FILE *fp;
    fp = fopen(arquivo,"r");
    if(!fp){
        printf("FALHA AO ABRIR O ARQUIVO\n");
        return 0;
    }
    while (!feof(fp)){
        produtor(fp,buffer);
        n_ocorrencias=consumidor(buffer,substring,n_ocorrencias);
    }
    fclose(fp);
    return n_ocorrencias;
}


void produtor(FILE *fp, buffer_t * buffer){
    int i;
    for (i = 0; i < SIZE; i++) {
        if (fgets(buffer[i].string,256,fp) == NULL){
            //printf("FIM DE ARQUIVO\n");
            break;
        }
    }
}

unsigned int consumidor(buffer_t * buffer, char * substring, unsigned int soma){
    int i=0,j=0,k=0;
    size_t tamSub = strlen(substring);
    for (i = 0; i < SIZE; i++) {
        size_t tamBuf = strlen(buffer[i].string);
        while (j < tamBuf) {
            if (buffer[i].string[j] == substring[k]) {
                if (k == tamSub-1) {
                    soma = soma+1;
                    k = 0;
                }
                else{
                    j++;
                    k++;
                }
            }
            else{
                j++;
                k = 0;
            }
        }
        j = 0;
        memset(buffer[i].string,0,tamBuf);
    }
    return soma;
}
