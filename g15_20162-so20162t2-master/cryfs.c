#include "cryfs.h"
#include "bibfs.h"
#include <math.h>

#define MAXBLOCO 4299262281

cry_desc_t * descritor;
tabelaAlocacao_t * tabelaDeAlocacao;
FILE * journal;
int totalBlocos = 0;
int * blocoDeIndices;
char cifras[256];
int primeiroBlocoArquivo[256];

int initfs(char * arquivo, int blocos){
    int i,j;
    // tamanho total pra descritor: 18 - do 0 ao 17
    // primeiro bloco após é pro bloco de índices (ou seja, 18)
    // tamanho total pra metadados: 19
    // se tiver 20 ja rola
    if (blocos < 20){
        //printf("Blocos Insuficientes\n");
        return FALHA;
    }
    if (blocos > MAXBLOCO){
        return FALHA;
    }
    //conseguiu acesso? se sim, já existe, então falha
    if (!access(arquivo, F_OK)){
        return FALHA;
    }

    /*if(!access("journal", F_OK)){
        return FALHA;
    }*/

    FILE *fp;
    fp = fopen(arquivo, "w+b");

    if (!fp) {
        //printf("Falha ao abrir\n");
        return FALHA;
    }
    journal = fopen("journal", "w+b");
    if (!journal) {
        //printf("Falha ao abrir\n");
        return FALHA;
    }
    totalBlocos = blocos;
    //inicializa bloco de indices
    blocoDeIndices = malloc(sizeof(int) * totalBlocos); //deve ser escrito no arquivo
    if(initIndices(fp) == FALHA){
        return FALHA;
    }
    //inicializa tabela de alocação de arquivos
    tabelaDeAlocacao = malloc(sizeof(tabelaAlocacao_t));
    tabelaDeAlocacao = initFAT(tabelaDeAlocacao);

    descritor = malloc(sizeof(cry_desc_t));

    descritor->arquivo_host = fp;
    for(i = 0; i < 256; i++){
        for(j = 0; j < 256; j++){
            descritor->descritores[i].nome[j] = '\0';
        }
        descritor->abertos[i].arquivo = NULL;
        descritor->abertos[i].acesso = -1;
        descritor->abertos[i].posicao = 0;
        primeiroBlocoArquivo[i] = -1;
        cifras[i] = '\0';
    }

    char bloco_zero[BLOCO];
	for (i = 0; i < BLOCO; i++) {
		bloco_zero[i] = '\0';
	}
	for (i = 0; i < totalBlocos; i++) {
		if (fwrite(bloco_zero, BLOCO, 1, fp) != 1) {
			//printf("ERRO DE ESCRITA\n");
			return FALHA;
		}
	}
    if (fseek(fp,0L,SEEK_SET) != 0 ) {
        //printf("ERRO NO ARQUIVO\n");
    }

    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
    fclose(journal);

    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);

    fclose(fp);

    return SUCESSO;

}

/*
    Função que inicializa FAT
*/
tabelaAlocacao_t * initFAT(tabelaAlocacao_t * fileAlocTable){
    int i;
    fileAlocTable->primPosLivre = 19;
    fileAlocTable->ponteiroArquivo = malloc(sizeof(int) * totalBlocos);

    for (i = 0; i < totalBlocos; i++) {
        if (i<18){
            fileAlocTable->ponteiroArquivo[i] = i+1;
            //printf("%i: %i\n",i,fileAlocTable.ponteiroArquivo[i]);
        }
        else if(i==18){
            fileAlocTable->ponteiroArquivo[i] = 0;
            //printf("%i: %i\n",i,fileAlocTable.ponteiroArquivo[i]);
        }
        else{
            fileAlocTable->ponteiroArquivo[i] = -1;
            //printf("%i: %i\n",i,fileAlocTable.ponteiroArquivo[i]);
        }
    }
    return fileAlocTable;
}

/*
    Função que inicializa o bloco de indices
*/
int initIndices(FILE * arquivo) {
    FILE *fp = arquivo;
    if (fseek(fp,0L,SEEK_SET) != 0) {
        printf("ERRO\n");
        return FALHA;
    }
    int i = 0;
    int j = 0;
    for (i = 0; i < totalBlocos; i++) {
        if (fseek(fp,BLOCO,SEEK_SET) == 0){
            if (i<19) {
                blocoDeIndices[i] = j;
                primeiroBlocoArquivo[i] = j;
            }
            else{
                blocoDeIndices[i] = i;
            }
        }
        else{
            //printf("ERRO AO INICILIZAR INDICES\n");
            return FALHA;
        }
    }
    return SUCESSO;
}

void printFAT(){
    int i;
    for (i = 0; i < totalBlocos; i++) {
        printf("posição %i: %i\n",i,tabelaDeAlocacao->ponteiroArquivo[i]);
    }
}

cry_desc_t * cry_openfs(char * arquivo){
    FILE *fp;

    if (access(arquivo, F_OK)){
        return FALHA;
    }

    fp = fopen(arquivo, "r+b");
    if (!fp) {
        return FALHA;
    }
    if (access("journal", F_OK)){
        return FALHA;
    }

    journal = fopen("journal", "r+b");
    if (!journal) {
        return FALHA;
    }

    descritor->arquivo_host = fp;

    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
    fclose(journal);


    fread(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
    fread(descritor->descritores,sizeof(descritor->descritores),1,fp);
    fread(descritor->abertos,sizeof(descritor->abertos),1,fp);
    fread(blocoDeIndices,sizeof(blocoDeIndices),1,fp);

    if (fseek(fp,0L,SEEK_SET) != 0) {
        return FALHA;
    }
    else{
        return descritor;
    }
}

indice_arquivo_t cry_open(cry_desc_t *cry_desc, char * nome,  int acesso, char deslocamento){
    if(cry_desc == 0){
        //printf("DESCRITOR INVÁLIDO\n");
        return FALHA;
    }
    if (cry_desc == NULL){
        return FALHA;
    }
    descritor = cry_desc;
    int indiceLivre;
    FILE *fp;
    fp = descritor->arquivo_host;
    if (fp == NULL) {
        return FALHA;
    }

    if (fseek(fp,0L,SEEK_SET) != 0) {
        return FALHA;
    }

    int blocoLivre = tabelaDeAlocacao->primPosLivre;
    indiceLivre = descritorLivre();
    if(existe(nome) != -1){
        if(aberto(descritor->abertos,nome,acesso,deslocamento) != -1){
            int indice = aberto(descritor->abertos,nome,acesso,deslocamento);
            return indice+1;
        }
        else{
            int indice = existe(nome);
            int livre = abertoLivre(descritor->abertos);
			if (livre == -1) {
				//printf("NÃO HÁ ESPAÇO NA TABELA DE ARQUIVOS ABERTOS\n");
				return FALHA;
			}
            descritor->abertos[livre].arquivo = &descritor->descritores[indice];
			descritor->abertos[livre].acesso = acesso;
            descritor->abertos[livre].posicao = 0;
            descritor->descritores[indice].ultimo_acesso = time(NULL);
            cifras[livre] = deslocamento;

            //atualiza o journal
            journal = fopen("journal", "r+b");
            fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
            fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
            fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
            fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
            fclose(journal);

            //atualiza o descritor de arquivos no arquivo
            fseek(descritor->arquivo_host,0L,SEEK_SET);
            fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,descritor->arquivo_host);
            fwrite(descritor->descritores,sizeof(descritor->descritores),1,descritor->arquivo_host);
            fwrite(descritor->abertos, sizeof(descritor->abertos),1,descritor->arquivo_host);
            fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, descritor->arquivo_host);
            fseek(descritor->arquivo_host,0L,SEEK_SET);

			return livre+1;
		}
	}
	else if (existe(nome) == -1) {
        if(blocoLivre == -1){
            return FALHA;
        }
        if(acesso == LEITURA){
            //printf("ACESSO INVÁLIDO\n");
            return FALHA;
        }
		if (indiceLivre == -1) {
			//printf("NÃO HÁ DESCRITOR LIVRE PARA ALOCAÇÃO\n");
			return FALHA;
		}
		int livre = abertoLivre(descritor->abertos);
		if (livre == -1) {
			//printf("NÃO HÁ ESPAÇO NA TABELA DE ARQUIVOS ABERTOS\n");
			return FALHA;
		}
		strcpy(descritor->descritores[indiceLivre].nome,nome);
		descritor->descritores[indiceLivre].criacao = time(NULL);
		descritor->descritores[indiceLivre].modificacao = time(NULL);
		descritor->descritores[indiceLivre].ultimo_acesso = time(NULL);
        descritor->descritores[indiceLivre].tamanho = 0;
        primeiroBlocoArquivo[indiceLivre] = blocoLivre;
		descritor->abertos[livre].arquivo = &descritor->descritores[indiceLivre];
		descritor->abertos[livre].acesso = acesso;
        descritor->abertos[livre].posicao = 0;
        cifras[livre] = deslocamento;
        //salvar deslocamento
		blocoDeIndices[blocoLivre] = blocoLivre;
		//atualizar FAT
        atualizarFAT(blocoLivre);
        //atualiza o journal
        journal = fopen("journal", "r+b");
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
        fclose(journal);
        //atualiza o descritor de arquivos no arquivo
        fseek(descritor->arquivo_host,0L,SEEK_SET);
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,descritor->arquivo_host);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,descritor->arquivo_host);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,descritor->arquivo_host);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, descritor->arquivo_host);
        fseek(descritor->arquivo_host,0L,SEEK_SET);

        return livre+1;
	}
	else{
		return FALHA;
	}
}

/*
    função para retornar o índice do primeiro descritor livre
    retorna -1 caso não tenha nenhum descritor livre
*/
int descritorLivre (){
    int i;
    char vazia[256];
    for (i = 0; i < 256; i++) {
        vazia[i] = '\0';
    }
    for (i = 0;i < 256; i++){
        if(strcmp(descritor->descritores[i].nome,vazia) == 0){
            return i;
        }
    }
    return -1;
}

/*
    função que verifica se o arquivo existe nos descritores
    retorna -1 caso não exista
*/
int existe(char * nome){
    int i;
    for(i = 0; i<256; i++){
        if (strcmp(descritor->descritores[i].nome,nome) == 0) {
            return i;
        }
    }
    return -1;
}

/*
    função que verifica se o arquivo do descritor está aberto
    retorna -1 caso não esteja
*/
int aberto(arquivo_aberto_t * arquivos, char * nome, int acesso, char deslocamento){
    int i;
    for(i = 0; i < 256; i++){
        if(arquivos[i].arquivo != NULL){
            if(strcmp(arquivos[i].arquivo->nome,nome) == 0){
                if(arquivos[i].acesso == acesso){
                    if (cifras[i] == deslocamento) {
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

/*
    Verifica na tabela de arquivos abertos se ainda contem posicoes livres
    retorna -1 caso não haja
*/
int abertoLivre(arquivo_aberto_t * abertos){
	int i;
	for (i = 0; i < 256; i++) {
		if (abertos[i].arquivo == NULL){
			return i;
		}
	}
	return -1;
}

/*
    função que atualiza blocos livre
*/
int atualizarFAT(int blocoOcupado){
    int i;
    if (tabelaDeAlocacao->primPosLivre == blocoOcupado) {
        tabelaDeAlocacao->ponteiroArquivo[blocoOcupado] = blocoOcupado;
        int livre = findLivre();
        if (livre == -1){
            //printf("NÃO HÁ MAIS BLOCOS LIVRES\n");
            tabelaDeAlocacao->primPosLivre = -1;
            return -1;

        }
        tabelaDeAlocacao->primPosLivre = livre;
    }
    else{
        for (i=0;i < totalBlocos;i++) {
            if (tabelaDeAlocacao->ponteiroArquivo[i] == blocoOcupado) {
                if (tabelaDeAlocacao->ponteiroArquivo[i] == blocoOcupado || tabelaDeAlocacao->ponteiroArquivo[i] == -1) {
                    tabelaDeAlocacao->ponteiroArquivo[i] = blocoOcupado;
                    return 0;
                }
                else{
                    i = blocoOcupado;
                }
            }
        }
    }
    return 0;
}

/*
    função que procura blocos livres
    -1 se n houver
*/
int findLivre(){
    int i;
    for (i = 0; i < totalBlocos; i++) {
        if(tabelaDeAlocacao->ponteiroArquivo[i] == -1)
            return i;
    }
    return -1;
}

int cry_close(indice_arquivo_t arquivo){
	arquivo = arquivo-1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
	if (descritor->abertos[arquivo].arquivo == NULL) {
		//printf("ARQUIVO NÃO ENCONTRADO\n");
		return FALHA;
	}
    descritor->abertos[arquivo].arquivo = NULL;
	descritor->abertos[arquivo].acesso = -1;
	descritor->abertos[arquivo].posicao = 0;
    cifras[arquivo] = '\0';
    FILE * fp = descritor->arquivo_host;
    //atualiza o journal
    journal = fopen("journal", "r+b");
    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
    fclose(journal);
    if (fseek(fp,0L,SEEK_SET) != 0 ) {
        //printf("ERRO NO ARQUIVO\n");
    }
    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
    //printf("FECHADO\n");
	return SUCESSO;
}

uint32_t cry_read(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer){
    arquivo = arquivo-1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    if(descritor->abertos[arquivo].acesso == ESCRITA){
        //printf("ACESSO INVÁLIDO\n");
        return FALHA;
    }
    if (descritor->abertos[arquivo].arquivo == NULL) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    if (tamanho > descritor->abertos[arquivo].arquivo->tamanho) {
        //printf("TAMANHO INVÁLIDO DE LEITURA\n");
        return FALHA;
    }
    FILE *fp;
	fp = descritor->arquivo_host;
	uint32_t bytesLidos = 0;
	if (fp == NULL) {
		//printf("ARQUIVO NÃO ENCONTRADO\n");
		return FALHA;
	}
    int blocospraler = ceil(tamanho/BLOCO)+1;
    int indice = existe(descritor->abertos[arquivo].arquivo->nome);
	int atual = primeiroBlocoArquivo[indice];
	char aux[tamanho];
    int blocoDoSeek = ceil(descritor->abertos[arquivo].posicao/BLOCO)+1;
    int auxSeek = 0;
    auxSeek = tabelaDeAlocacao->ponteiroArquivo[atual];
    while (blocoDoSeek != 0) {
        auxSeek = tabelaDeAlocacao->ponteiroArquivo[auxSeek];
        blocoDoSeek--;
    }
    int quantoFoideslocado = descritor->abertos[arquivo].posicao%BLOCO;
    fseek(fp,(quantoFoideslocado+((atual-1)*BLOCO)),SEEK_SET);

    if(tamanho > BLOCO){
        int ler = BLOCO - quantoFoideslocado;
        if(ler != BLOCO){
            if (fread(buffer,ler,1,fp) != 1){
                //printf("ERRO AO LER ARQUIVO\n");
                return FALHA;
            }
            blocospraler--;
            strcat(aux,buffer);
        }
        int i;
        for (i = 0; i < blocospraler -1; i++) {
            if (fread(buffer,BLOCO,1,fp) != 1){
                //printf("ERRO AO LER ARQUIVO\n");
                return FALHA;
            }
            strcat(aux,buffer);
            atual = blocoDeIndices[atual];
            fp = buscaFileHandler(fp,atual-1);
            bytesLidos+=BLOCO;
            tamanho-=BLOCO;

        }
        if (fread(buffer,tamanho,1,fp) != 1){
            //printf("ERRO AO LER ARQUIVO\n");
            return FALHA;
        }
        bytesLidos+=tamanho;
		strcat(aux,buffer);
        decripta(cifras[arquivo],aux,buffer);
        descritor->abertos[arquivo].posicao = bytesLidos;
        descritor->descritores[indice].ultimo_acesso = time(NULL);

        //atualiza o journal
        journal = fopen("journal", "r+b");
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
        fclose(journal);

        if (fseek(fp,0L,SEEK_SET) != 0 ) {
            //printf("ERRO NO ARQUIVO\n");
        }
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
		return bytesLidos;
	}
    else{
		if (fread(buffer,tamanho,1,fp) != 1){
			//printf("ERRO AO LER ARQUIVO\n");
			return FALHA;
		}
		decripta(cifras[arquivo],buffer,buffer);
		bytesLidos+=tamanho;
        descritor->abertos[arquivo].posicao = bytesLidos;
        descritor->descritores[indice].ultimo_acesso = time(NULL);

        //atualiza o journal
        journal = fopen("journal", "r+b");
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
        fclose(journal);

        if (fseek(fp,0L,SEEK_SET) != 0 ) {
            //printf("ERRO NO ARQUIVO\n");
        }
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
		return bytesLidos;
	}
    return FALHA;
}

/*
    função para setar o file handler do arquivo no bloco desejado
*/

FILE * buscaFileHandler(FILE *host, int bloco){
    FILE *fp = host;
	if (fseek(fp,0L,SEEK_SET) != 0 ) {
		//printf("ERRO DE SEEK PARA O INÍCIO DO ARQUIVO\n");
		return NULL;
	}
    size_t teste = fseek(fp,(BLOCO*bloco),SEEK_SET);
	if (teste != 0 ) {
		//printf("ERRO DE SEEK PARA O BLOCO\n");
		return NULL;
	}
	return fp;
}

/*
    Função para decriptar uma dada chave
*/
void decripta(char deslocamento, char * bufferEntrada, char * bufferSaida){
	int tamanho = strlen(bufferEntrada);
	uint32_t valor = (uint32_t)deslocamento;
	int i;
	for(i = 0; i< tamanho; i++){
		if (bufferEntrada[i] == '\0') {
			bufferSaida[i] = '\0';
		}
		else{
			bufferSaida[i] = (bufferEntrada[i]-valor)%256;
		}
	}
}

int cry_write(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer){
    FILE *fp;
	fp = descritor->arquivo_host;
	if (fp == NULL) {
		//printf("ARQUIVO NÃO ENCONTRADO\n");
		return FALHA;
    }
    arquivo = arquivo-1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
	if (descritor->abertos[arquivo].acesso == LEITURA) {
		//printf("PERMISSÃO NEGADA\n");
		return FALHA;
	}
    if (tamanho == 0) {
        //printf("NÃO HÃ O QUE ESCREVER\n");
        return FALHA;
    }
	int tamanhoBuffer = strlen(buffer);
    if (tamanhoBuffer == 0) {
        //printf("BUFFER EM BRANCO\n");
        return FALHA;
    }
    /*if (tamanho > tamanhoBuffer) {
        //printf("TAMANHO A SER ESCRITO INVÁLIDO");
        return FALHA;
    }*/
    if (tamanhoBuffer > tamanho) {
        tamanhoBuffer = tamanho;
    }
	char buffer2[tamanhoBuffer];
    encripta(cifras[arquivo],buffer,buffer2);
    int indice = existe(descritor->abertos[arquivo].arquivo->nome);
	int blocoAtual = primeiroBlocoArquivo[indice];
	if (blocoAtual == tabelaDeAlocacao->ponteiroArquivo[blocoAtual]){
		fp = buscaFileHandler(fp,blocoAtual-1);
	}
    else{
        while(blocoAtual != tabelaDeAlocacao->ponteiroArquivo[blocoAtual]){
            blocoAtual = tabelaDeAlocacao->ponteiroArquivo[tabelaDeAlocacao->ponteiroArquivo[blocoAtual]];
        }
        fp = buscaFileHandler(fp,blocoAtual-1);
    }
    int quantoFoiEscrito = descritor->abertos[arquivo].arquivo->tamanho%BLOCO;
    fseek(fp,(quantoFoiEscrito+((blocoAtual-1)*BLOCO)),SEEK_SET);
    if (tamanho+quantoFoiEscrito > BLOCO) {
        int escrever = BLOCO - quantoFoiEscrito;
        int i;
        if (escrever != BLOCO) {
            char bufferauxiliar[escrever];
            if(fread(bufferauxiliar,escrever,1,fp)){
                //printf("FALHA AO LER DO ARQUIVO");
                return FALHA;
            }
            while (i > escrever) {
                bufferauxiliar[i] = buffer2[i];
                i++;
            }
            fseek(fp,(quantoFoiEscrito+((blocoAtual-1)*BLOCO)),SEEK_SET);
            fwrite(bufferauxiliar,escrever,1,fp);
            descritor->abertos[arquivo].arquivo->tamanho+=escrever;
            descritor->descritores[indice].tamanho+=escrever;
            descritor->descritores[indice].modificacao = time(NULL);
            descritor->descritores[indice].ultimo_acesso = time(NULL);
            tamanho-=escrever;
        }
        else{
            while (tamanho > BLOCO){
                int blocoLivre = tabelaDeAlocacao->primPosLivre;
                if (blocoLivre == -1) {
                    //printf("NÃO HÁ BLOCOS LIVRES PARA ALOCAÇÃO\n");
                    return FALHA;
                }
                atualizarFAT(blocoLivre);
                tabelaDeAlocacao->ponteiroArquivo[blocoAtual] = blocoLivre;
                tabelaDeAlocacao->ponteiroArquivo[blocoLivre] = blocoLivre;
                blocoDeIndices[blocoAtual] = blocoLivre;
                blocoDeIndices[blocoLivre] = blocoLivre;
                blocoAtual = blocoLivre;
                fp = buscaFileHandler(fp,blocoAtual-1);
                char aux[BLOCO];
                for (i = 0; i < BLOCO; i++) {
                    aux[i] = buffer2[escrever];
                    escrever++;
                }
                fwrite(aux,BLOCO,1,fp);
                descritor->abertos[arquivo].arquivo->tamanho+=BLOCO;
                descritor->descritores[indice].tamanho+=BLOCO;
                descritor->descritores[indice].modificacao = time(NULL);
                descritor->descritores[indice].ultimo_acesso = time(NULL);
                tamanho-=BLOCO;
            }
            char aux3[tamanho];
            for (i = 0; i < tamanho; i++) {
                aux3[i] = buffer2[escrever];
                escrever++;
            }
            fwrite(aux3,tamanho,1,fp);
            descritor->abertos[arquivo].arquivo->tamanho+=tamanho;
            descritor->descritores[indice].tamanho+=tamanho;
            descritor->descritores[indice].modificacao = time(NULL);
            descritor->descritores[indice].ultimo_acesso = time(NULL);

            journal = fopen("journal", "r+b");
            fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
            fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
            fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
            fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
            fclose(journal);

            if (fseek(fp,0L,SEEK_SET) != 0 ) {
                //printf("ERRO NO ARQUIVO\n");
                return FALHA;
            }
            fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
            fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
            fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
            fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
            return SUCESSO;
        }
    }
    else{
        if (quantoFoiEscrito == 0 && descritor->descritores[indice].tamanho%BLOCO == 0) {
            int blocoLivre = tabelaDeAlocacao->primPosLivre;
            if (blocoLivre == -1) {
                //printf("NÃO HÁ BLOCOS LIVRES PARA ALOCAÇÃO\n");
                return FALHA;
            }
            atualizarFAT(blocoLivre);
            tabelaDeAlocacao->ponteiroArquivo[blocoAtual] = blocoLivre;
            tabelaDeAlocacao->ponteiroArquivo[blocoLivre] = blocoLivre;
            blocoDeIndices[blocoAtual] = blocoLivre;
            blocoDeIndices[blocoLivre] = blocoLivre;
            blocoAtual = blocoLivre;
            fp = buscaFileHandler(fp,blocoAtual-1);
        }
        fwrite(buffer2,tamanho,1,fp);
        descritor->abertos[arquivo].arquivo->tamanho+=tamanho;
        descritor->descritores[indice].tamanho+=tamanho;
        descritor->descritores[indice].modificacao = time(NULL);
        descritor->descritores[indice].ultimo_acesso = time(NULL);
        journal = fopen("journal", "r+b");
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
        fclose(journal);

        if (fseek(fp,0L,SEEK_SET) != 0 ) {
            //printf("ERRO NO ARQUIVO\n");
            return FALHA;
        }
        fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
        fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
        fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
        fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
        return SUCESSO;
    }
    return FALHA;
}
/*
    Encripta dada uma chave
*/
void encripta(char deslocamento, char * bufferEntrada, char * bufferSaida){
    int i;
    uint32_t valor = (uint32_t)deslocamento;
    for(i=0; i<strlen(bufferSaida);i++){
        bufferSaida[i] = (bufferEntrada[i]+valor)%256;
    }
}

int cry_delete(indice_arquivo_t arquivo){
    FILE *fp;
	fp = descritor->arquivo_host;
	arquivo = arquivo -1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
	if(descritor->abertos[arquivo].arquivo == NULL){
		//printf("INDICE INVÁLIDO, NÃO HÁ ARQUIVO ABERTO\n");
		return FALHA;
	}
	int indice = existe(descritor->abertos[arquivo].arquivo->nome);
    int primeiroBloco = primeiroBlocoArquivo[indice];
    int i,j;
	char bloco_zero[BLOCO];
	for (i = 0; i < BLOCO; i++) {
		bloco_zero[i] = '\0';
	}
	if (primeiroBloco == primeiroBloco) {
		fp = buscaFileHandler(fp,primeiroBloco-1);
		if (fwrite(bloco_zero, BLOCO, 1, fp) != 1) {
			//printf("ERRO DE ESCRITA\n");
			return FALHA;
		}
		blocoDeIndices[primeiroBloco] = primeiroBloco;
        tabelaDeAlocacao->ponteiroArquivo[primeiroBloco] = -1;
	}
	else{
		while (primeiroBloco != blocoDeIndices[primeiroBloco]) {
			primeiroBloco = blocoDeIndices[primeiroBloco];
			fp = buscaFileHandler(fp,primeiroBloco-1);
			if (fwrite(bloco_zero, BLOCO, 1, fp) != 1) {
				//printf("ERRO DE ESCRITA\n");
				return FALHA;
            }
            int aux = blocoDeIndices[primeiroBloco];
            blocoDeIndices[primeiroBloco] = primeiroBloco;
            tabelaDeAlocacao->ponteiroArquivo[primeiroBloco] = -1;
            primeiroBloco = aux;
		}
	}
	for (j = 0; j < 256; j++) {
		descritor->descritores[indice].nome[j] = '\0';
	}
    for (j = 0; j < 256; j++) {
        descritor->abertos[arquivo].arquivo->nome[j] = '\0';
    }
    descritor->abertos[arquivo].arquivo = NULL;
    descritor->abertos[arquivo].acesso = -1;
    cifras[arquivo] = '\0';
    primeiroBlocoArquivo[indice] = -1;
    descritor->descritores[indice].criacao = 0;
    descritor->descritores[indice].modificacao = 0;
    descritor->descritores[indice].ultimo_acesso = 0;
    descritor->descritores[indice].tamanho = 0;
	//printf("DELETOU E FECHOU\n");

    //atualiza o journal
    journal = fopen("journal", "r+b");
    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,journal);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,journal);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,journal);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, journal);
    fclose(journal);

    if (fseek(fp,0L,SEEK_SET) != 0 ) {
        //printf("ERRO NO ARQUIVO\n");
    }
    fwrite(descritor->arquivo_host,sizeof(descritor->arquivo_host),1,fp);
    fwrite(descritor->descritores,sizeof(descritor->descritores),1,fp);
    fwrite(descritor->abertos, sizeof(descritor->abertos),1,fp);
    fwrite(blocoDeIndices, sizeof(blocoDeIndices),1, fp);
	return SUCESSO;
}

int cry_seek(indice_arquivo_t arquivo, uint32_t seek){
    arquivo = arquivo -1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    else if(descritor->abertos[arquivo].arquivo == NULL){
        //printf("ARQUIVO INVÁLIDO\n");
        return FALHA;
    }
    else if(descritor->abertos[arquivo].arquivo->tamanho > seek){
        descritor->abertos[arquivo].posicao = seek;
        return SUCESSO;
    }
    else{
        return FALHA;
    }
}

time_t cry_creation(indice_arquivo_t arquivo){
    arquivo = arquivo -1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    if(descritor->abertos[arquivo].arquivo == NULL){
        //printf("ARQUIVO INVÁLIDO\n");
        return FALHA;
    }
    return descritor->abertos[arquivo].arquivo->criacao;
}

time_t cry_last_modified(indice_arquivo_t arquivo){
    arquivo = arquivo -1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    if(descritor->abertos[arquivo].arquivo == NULL){
        //printf("ARQUIVO INVÁLIDO\n");
        return FALHA;
    }
    return descritor->abertos[arquivo].arquivo->modificacao;
}

time_t cry_accessed(indice_arquivo_t arquivo){
    arquivo = arquivo -1;
    if (arquivo < 0 || arquivo > 255) {
        //printf("ÍNDICE INVÁLIDO\n");
        return FALHA;
    }
    if(descritor->abertos[arquivo].arquivo == NULL){
        //printf("ARQUIVO INVÁLIDO\n");
        return FALHA;
    }
    return descritor->abertos[arquivo].arquivo->ultimo_acesso;
}
