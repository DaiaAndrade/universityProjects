# Trabalho 1 - Sistemas Operacionais

## Descrição

Neste trabalho, os alunos irão desenvolver um programa em C usando POSIX Threads para resolver o problema de contagem de substrings em um texto.

Uma thread deve receber um arquivo como entrada e ler o mesmo para um buffer compartilhado. As demais threads (uma por processador) devem retirar linhas deste buffer, contar o número de ocorrências. No fim, uma das threads (ou outra thread) deve receber os valores, somá-los e retornar o valor.

A assinatura da função é:

  unsigned int ocorrencias(char * arquivo, char * substring, int numthreads);

O primeiro argumento é o nome do arquivo (com path), o segundo argumento é a substring a ser buscada (ISO-8859-1) e o último é o número de threads pra contar o número de ocorrências.

O código deve estar contido em um arquivo chamado *calcula.c* para versão sequencial, *calculat.c* para a versão paralela e a função deve também estar declarada em um arquivo chamado *calcula.h*.

O trabalho deve ser compilável e executável em plataforma Ubuntu Linux 12.04, GCC 4.6.4, usando o Makefile do repositório.


## Testes

Cada grupo deverá fornecer pelo menos quatro exemplos de teste em um arquivo chamado *teste.c* usando a biblioteca Simpletest.  Se os alunos quiserem, podem aumentar o número de testes seguindo este padrão de nomenclatura. Uma função *main()* deverá chamar as funções de teste. Os grupos poderão usar um diretório *docs* no repositório para armazenar arquivos para os testes, que não deverão exceder 1 MB no total.

## Avaliação de desempenho

Os testes devem ter uma análise de desempenho com o speedup da versão sequencial sobre a versão com *n* threads, onde *n* é o número de *cores* no computador onde foi testado o programa.

A avaliação de desempenho deverá ser realizada de acordo com princípios de reproducibilidade e com validade estatística. Prestem especial atenção ao _número de repetições_.

Speedup é definido como a razão do tempo de execução entre a versão sequencial e a versão paralela.

O relatório final deve ser submetido como um PDF no formato de artigo da Sociedade Brasileira de Computação (SBC) com o nome *relatorio.pdf* .


## Produtos

* Implementação (*calcula.h*, *calcula.c*, *calculat.c*)
* Casos de teste documentados (*teste.c*)
* Análise de desempenho, comparando a versão sequencial com a versão multithread (*relatorio.pdf*)
  * Metodologia de teste
  * Tempo de execução
  * Speedup

## Cronograma

* 14/09/2016 - haverá tempo em aula para os alunos tirarem eventuais dúvidas sobre o trabalho
* 21/09/2016 - versão sequencial (2,0 pontos)
* 03/10/2016 - entrega da versão final (6,0 pontos) e relatório (2,0 pontos) -- a nota referente ao relatório é condicionada à versão final ser funcional

## Referências

* [Tutorial sobre POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/)
* [Formato de artigo da SBC](http://www.sbc.org.br/documentos-da-sbc/summary/169-templates-para-artigos-e-capitulos-de-livros/878-modelosparapublicaodeartigos)
