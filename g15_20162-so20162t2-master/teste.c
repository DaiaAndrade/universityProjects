#include "cryfs.h"
#include "bibfs.h"
#include "simpletest.h"

void test1();

int main(int argc, char const *argv[]) {
    test1();
    return 0;
}

void test1(){
    DESCRIBE("Teste 1 - Testes básicos");
    WHEN("1.1 - Criar sistema de arquivo com blocos insuficientes");
    IF("Numero de Blocos < 20");
    THEN("FALHA");
    isEqual(initfs("cripto",7),FALHA);

    WHEN("1.2 - Criar sistema de arquivo com blocos suficientes");
    IF("Numero de Blocos > 20");
    THEN("SUCESSO");
    isEqual(initfs("cripto",100),SUCESSO);

    WHEN("1.3 - Criar sistema de arquivos que já existe");
    IF("Arquivo já existe");
    THEN("FALHA");
    isEqual(initfs("cripto",22),FALHA);

    WHEN("1.4 - Abrir sistema de arquivos criado");
    IF("Sistema de Arquivos é aberto");
    THEN("SUCESSO");
    cry_desc_t * descritor;
    descritor = cry_openfs("cripto");
    isNotNull(descritor->arquivo_host);

    WHEN("1.5 - Abrir sistema de arquivos não criado");
    IF("Sistema de Arquivos não é aberto");
    THEN("FALHA");
    cry_desc_t * descritor2;
    descritor2 = cry_openfs("crito");
    isNull(descritor2);

    DESCRIBE("Fim Teste 1");
    printf("\n");

    DESCRIBE("Teste 2 - Testes de abertura e fechamento");
    WHEN("2.1 - Criar um arquivo criptografado com um descritor inválido");
    IF("Descritor Inválido");
    THEN("FALHA");
    indice_arquivo_t descritor2Indice;
    char deslocamento = 'a';
    descritor2Indice = cry_open(descritor2,"oi",ESCRITA,deslocamento);
    isEqual(descritor2Indice,FALHA);

    WHEN("2.2 - Abrir multiplos arquivo criptografados não existente");
    IF("Arquivo criado com sucesso");
    THEN("SUCESSO");
    indice_arquivo_t descritorIndice;
    descritorIndice = cry_open(descritor,"oi",ESCRITA,deslocamento);
    isNotEqual(descritorIndice,FALHA);

    IF("Arquivo criado com sucesso");
    THEN("SUCESSO");
    indice_arquivo_t descritorIndice2;
    deslocamento = 'b';
    descritorIndice2 = cry_open(descritor,"aro",LEITURAESCRITA,deslocamento);
    isNotEqual(descritorIndice2,FALHA);

    IF("Arquivo criado com sucesso");
    THEN("SUCESSO");
    indice_arquivo_t descritorIndice3;
    deslocamento = 'f';
    descritorIndice3 = cry_open(descritor,"empoderamento",LEITURAESCRITA,deslocamento);
    isNotEqual(descritorIndice3,FALHA);

    WHEN("2.3 - Abrir arquivo criptografado já aberto");
    IF("Arquivo aberto com sucesso");
    THEN("SUCESSO");
    deslocamento = 'a';
    descritorIndice = cry_open(descritor,"oi",ESCRITA,deslocamento);
    isNotEqual(descritorIndice,FALHA);

    WHEN("2.4 - Abrir arquivo criptografado já aberto com deslocamento diferente");
    IF("Arquivo aberto com sucesso");
    THEN("SUCESSO");
    indice_arquivo_t descritorIndiceIgual;
    deslocamento = 'h';
    descritorIndiceIgual = cry_open(descritor,"oi",LEITURA,deslocamento);
    isNotEqual(descritorIndiceIgual,FALHA);

    WHEN("2.5 - Abrir arquivo criptografado não existente para leitura");
    IF("Arquivo não for criado");
    THEN("FALHA");
    descritorIndice = cry_open(descritor,"oi2",LEITURA,deslocamento);
    isEqual(descritorIndice,FALHA);

    WHEN("2.6 - Fechar arquivo criptografado");
    IF("Arquivo fechado com sucesso");
    THEN("SUCESSO");
    descritorIndice = cry_open(descritor,"oi",ESCRITA,deslocamento);
    isEqual(cry_close(descritorIndice),SUCESSO);

    WHEN("2.7 - Fechar arquivo não existente");
    IF("Arquivo não existe para ser fechado");
    THEN("FALHA");
    descritorIndice = 300;
    isEqual(cry_close(descritorIndice),FALHA);


    DESCRIBE("Fim Teste 2");
    printf("\n");

    DESCRIBE("Teste 3 - Testes de leitura, escrita e deleção");
    WHEN("3.1 - Escrevendo arquivo com permissão para escrita");
    IF("Escrita 1: Escrevendo Arquivo de 70 bytes");
    THEN("SUCESSO");
    descritorIndice = cry_open(descritor,"oi",LEITURAESCRITA,deslocamento);
    char buffer[] = "Meu pintinho amarelhinho cabe aqui na minha mao quando quer comer bichinho";
    int escrito = cry_write(descritorIndice,strlen(buffer),buffer);
    isEqual(escrito,SUCESSO);

    IF("Escrita 2: Escrevendo arquivo de 300 bytes");
    THEN("SUCESSO");
    char buf[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus accumsan mi mauris, sed pellentesque sem faucibus venenatis. Maecenas aliquam aliquet magna. Quisque pellentesque faucibus sem quis bibendum. Nullam consectetur facilisis volutpat. Proin semper ligula vel vulputate laoreet. Ut blandit";
    escrito = cry_write(descritorIndice2,strlen(buf),buf);
    isEqual(escrito,SUCESSO);

    IF("Escrita 3: Escrevendo arquivo de 5 kbytes");
    THEN("SUCESSO");
    char buf2[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus accumsan mi mauris, sed pellentesque sem faucibus venenatis. Maecenas aliquam aliquet magna. Quisque pellentesque faucibus sem quis bibendum. Nullam consectetur facilisis volutpat. Proin semper ligula vel vulputate laoreet. Ut blandit enim vel neque iaculis mollis. Mauris tristique lacus eget metus ornare, sed hendrerit erat porttitor. Suspendisse potenti. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Aenean porttitor felis ac neque mattis fringilla. at commodo odio. Duis semper molestie egestas. In hac habitasse platea dictumst. Vivamus vestibulum diam a urna consectetur placerat. Maecenas et elit sem. Pellentesque pharetra leo eu metus pretium tincidunt. Ut condimentum velit id sem tincidunt pharetra. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce non pulvinar nulla. Donec quam nisl, tempus sit amet lacinia bibendum, vehicula sit amet odio. In fermentum elementum neque eu venenatis. Morbi sit amet odio tempus, gravida lectus facilisis, dignissim eros. Fusce risus ipsum, volutpat eu gravida id, pellentesque sit amet ligula. Quisque varius lorem blandit nisi porta dignissim. Sed elementum at ligula a elementum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. metus tellus, lacinia sit amet pharetra quis, vestibulum id turpis. In placerat rhoncus egestas. Duis quis urna tincidunt, tristique eros ac, porttitor lorem. Aliquam feugiat accumsan vulputate. Nunc auctor nisi erat, non dapibus risus posuere eget. Vivamus quis congue dui. Aenean scelerisque, turpis id fermentum viverra, lorem orci convallis orci, eu egestas erat ipsum nec arcu. Donec eget rutrum urna. Curabitur id enim quam. Ut ac porta mauris. In et sagittis orci. Mauris at orci quis dolor ornare volutpat id varius libero. Sed in nunc finibus, accumsan orci vel, dapibus ligula. Duis mollis, orci ac commodo euismod, elit enim sagittis justo, et vestibulum enim orci sed elit. Vestibulum at tempus libero, at dictum justo. ac euismod tellus, eu convallis turpis. Mauris sed finibus urna, eget placerat est. Vestibulum non nulla felis. Curabitur quis tortor erat. Aliquam et turpis malesuada, condimentum massa vel, faucibus neque. Quisque eget sodales ligula, a luctus lorem. Phasellus sodales mi in nulla consequat euismod. Morbi id felis nec neque lobortis finibus non quis mi. Donec ornare lobortis placerat. Nunc in quam vehicula eros ultrices iaculis. Curabitur sagittis vel augue ut feugiat. Nulla dignissim sit amet justo vel porttitor. maximus tellus a pharetra interdum. Suspendisse pharetra molestie nisl, non porta nisi pellentesque id. Donec non arcu quis lectus euismod sodales nec sed tellus. Donec non mi finibus, rhoncus quam non, tristique nulla. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Cras tincidunt cursus neque vitae tincidunt. Nullam vitae commodo mi. Nullam sed massa tortor. Ut malesuada tristique imperdiet. In rhoncus, nulla mollis aliquet sodales, ligula velit pellentesque quam, in sagittis eros massa sed dolor. venenatis fringilla tortor id dapibus. Nunc ex ipsum, condimentum ac mauris non, tempus eleifend risus. Morbi feugiat quam sed urna posuere posuere. Quisque tristique augue ac mauris consequat, eget efficitur diam congue. Vestibulum ultricies gravida lorem, ac suscipit est scelerisque nec. Donec facilisis nulla nulla, in pellentesque felis elementum eget. Aenean aliquet urna erat, ut ultrices tortor viverra quis. hac habitasse platea dictumst. Proin sit amet enim a sapien cursus dictum vel in tellus. Duis blandit nulla nec diam porta interdum. Integer eget sapien vel mauris volutpat faucibus vel sed urna. Curabitur ultrices, neque eu consequat pulvinar, tellus tortor maximus dui, vel tristique est massa nec eros. Suspendisse potenti. Mauris vestibulum ullamcorper ornare. Morbi et dolor mauris. Fusce eu rutrum quam, in maximus nunc. Integer at ipsum maximus, tempus ex sit amet, sollicitudin orci. In a vulputate dui, eu malesuada elit. ut purus eu turpis bibendum hendrerit tempus eu erat. Ut sodales porta venenatis. Phasellus ultricies id ex sed mattis. Integer vel sapien nec enim sodales lobortis. Vestibulum euismod quam a volutpat pretium. Nam arcu elit, tincidunt non massa egestas, luctus gravida dolor. Etiam non convallis neque, quis sollicitudin turpis. egestas, tortor dapibus tempor consequat, sapien erat imperdiet arcu, porttitor suscipit leo libero a mi. Morbi sem tortor, tristique non auctor sed, cursus nec erat. Nulla interdum, nisi eget ultricies commodo, justo purus ultrices risus, at dignissim ex nulla ut dolor. Curabitur consequat ipsum leo, id auctor enim molestie sit amet. Curabitur tellus mi, tincidunt quis orci eu, dapibus imperdiet nisi. Nam mattis gravida enim quis lacinia. Fusce risus sapien, pulvinar in aliquet vitae, imperdiet eget sem. Maecenas sed metus ac quam rhoncus porta sed eget mi. non bibendum lectus, sed euismod lorem. Aliquam";
    escrito = cry_write(descritorIndice3,strlen(buf2),buf2);
    isEqual(escrito,SUCESSO);

    WHEN("3.2 - Lendo itens escritos");
    IF("Leitura 1: Lendo os 70 bytes escritos");
    THEN("Tamanho do buffer escrito");
    char bufferLido[sizeof(buffer)];
    uint32_t lido = cry_read(descritorIndice,sizeof(buffer),bufferLido);
    isEqual(lido,sizeof(buffer));

    IF("Leitura 2: Lendo os 200 dos 300 bytes escritos");
    THEN("Resultado esperado: 200");
    char bufferLido2[200];
    lido = cry_read(descritorIndice2,200,bufferLido2);
    isEqual(lido,200);

    IF("Leitura 3: Lendo os 4098 bytes dos 5K bytes escritos");
    THEN("Resultado esperado: 4098");
    char bufferLido3[4098];
    lido = cry_read(descritorIndice3,4098,bufferLido3);
    isEqual(lido,4098);

    WHEN("3.3 - Deletando escritos");
    IF("Deleção 1: Deletando o arquivo de 70 bytes");
    THEN("SUCESSO");
    int deletado = cry_delete(descritorIndice);
    isEqual(deletado,SUCESSO);

    IF("Deleção 2: Deletando o arquivo de 5kbytes");
    THEN("SUCESSO");
    deletado = cry_delete(descritorIndice3);
    isEqual(deletado,SUCESSO);

    WHEN("3.4 - Retornando criação, modificação e último acesso");
    IF("Criação retornada com sucesso");
    THEN("Não zero");
    descritorIndice = cry_open(descritor,"oi",LEITURAESCRITA,deslocamento);
    time_t tempo = cry_creation(descritorIndice);
    printf("      %s\n", ctime(&tempo));
    isNotEqual(tempo,0);

    IF("Modificação retornada com sucesso");
    THEN("Não zero");
    tempo = cry_last_modified(descritorIndice);
    printf("      %s\n", ctime(&tempo));
    isNotEqual(tempo,0);

    IF("Acesso retornado com sucesso");
    THEN("Não zero");
    tempo = cry_accessed(descritorIndice);
    printf("      %s\n", ctime(&tempo));
    isNotEqual(tempo,0);

    WHEN("3.5 - Setando o Seek dentro de um arquivo existente");
    IF("Seek para 13 bytes dentro do Arquivo de 300 bytes");
    THEN("SUCESSO");
    isEqual(cry_seek(descritorIndice2,13),SUCESSO);

    IF("Lendo 14 bytes a partir do seek");
    THEN("27");
    char buffeTST[14];
    lido = cry_read(descritorIndice2,14,buffeTST);
    isEqual(lido,14);

    IF("Lendo 600 bytes a partir do seek 13");
    THEN("FALHA");
    cry_seek(descritorIndice2,13);
    char buffeTST2[600];
    lido = cry_read(descritorIndice2,600,buffeTST2);
    isEqual(lido,FALHA);

    DESCRIBE("Fim Dos Testes");
    /*
    */
}
