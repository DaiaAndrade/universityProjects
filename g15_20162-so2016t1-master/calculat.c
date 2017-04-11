#include "calcula.h"

#define SIZE 20

buffer_t buffer[SIZE];
int entrada, saida;

pthread_mutex_t mutex_buffer, contaOcorrencia;
pthread_cond_t cheio;
unsigned int n_ocorrencias;

void inicializaBuffer();
void * produtor(void * file);
void * consumidor(void *ss);
void consumir(buffer_t buffer, char * substring);

unsigned int ocorrencias(char * arquivo, char * substring, int numthreads){
    pthread_t prod;


    pthread_create(&prod,NULL,produtor, (void *) arquivo);

    int i;
    pthread_t cons[numthreads-1];

    inicializaBuffer();

    for (i = 0; i < numthreads-1; i++) {
        pthread_create(&cons[i],NULL,consumidor, (void *) substring);
    }

    pthread_join(prod,NULL);

    for (i = 0; i < numthreads-1; i++) {
        pthread_join(cons[i],NULL);

    }

    return n_ocorrencias;
}

void inicializaBuffer(){
    int i;
    for(i=0;i<SIZE;i++){
        memset(buffer[saida].string,'\0',strlen(buffer[saida].string));
    }
    entrada = 0;
    saida = 0;
    n_ocorrencias = 0;
}


void * produtor(void * file){
    char * arquivo;
    arquivo = (char *) file;
    FILE *fp;
    fp = fopen(arquivo,"r");
    if(!fp){
        printf("FALHA AO ABRIR O ARQUIVO\n");
        fclose(fp);
        return NULL;
    }
    while (!feof(fp)){
        //pega o lock pro buffer;
        pthread_mutex_lock(&mutex_buffer);
        while( ((entrada + 1)%SIZE) == saida ){
            //se a próxima posição a ser preenchida é igual a que deve ser consumida, buffer cheio
            if(pthread_cond_wait(&cheio,&mutex_buffer)){
                exit(-1);
            }
        }
        //pega a linha e joga pro buffer (isso é produzir)
        if(fgets(buffer[entrada].string,256,fp) != NULL){
            //printf("Produzido %s",buffer[entrada].string);
        }
        //seta a proxima posição pra ser preenchida
        entrada = (entrada + 1) % SIZE;
        pthread_mutex_unlock(&mutex_buffer);
        //sinaliza os consumidores que o buffer n tá mais vazio
        pthread_cond_signal(&cheio);
    }
    fclose(fp);
    return NULL;
}

void * consumidor(void *ss) {
    char * substring;
    substring = (char *) ss;
    //problema: nunca sai desse while, só deus sabe o motivo
    while(1){
        //pega o lock
        pthread_mutex_lock(&mutex_buffer);
        while (saida == entrada) {
            //se a posição a ser consumida é a mesma que a que vai ser produzida, então buffer tá vazio
            if(pthread_cond_wait(&cheio,&mutex_buffer)){
                exit(-1);
            }
        }
        // se o conteúdo da string for nulo, é porque não há mais o que consumir
        if(strcmp(buffer[saida].string,"") == 0){
            //printf("entrei aqui\n");
            pthread_cond_signal(&cheio);
            pthread_mutex_unlock(&mutex_buffer);
            pthread_exit(NULL);
        }
        // conta as ocorrencias na posição do buffer e atualiza n_ocorrencias
        consumir(buffer[saida],substring);
        // limpa a posição do buffer
        memset(buffer[saida].string,'\0',strlen(buffer[saida].string));
        //printf("Consumido %s\n",buffer[saida].string);
        if (((entrada + 1) % SIZE) == saida) {
            //sinaliza que já consumiu ao menos um elemento para o produtor
            pthread_cond_signal(&cheio);
        }
        // seta próxima posição
        saida = (saida + 1) % SIZE;
        pthread_mutex_unlock(&mutex_buffer);
    }
    return NULL;
}

void consumir(buffer_t buffer, char * substring){
    int j=0,k=0;
    size_t tamSub = strlen(substring);
    size_t tamBuf = strlen(buffer.string);
    while (j < tamBuf) {
        if (buffer.string[j] == substring[k]) {
            if (k == tamSub-1) {
                pthread_mutex_lock(&contaOcorrencia);
                n_ocorrencias = n_ocorrencias+1;
                pthread_mutex_unlock(&contaOcorrencia);
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
}
