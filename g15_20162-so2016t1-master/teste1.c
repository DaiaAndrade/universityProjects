#include "calcula.h"
#include "simpletest.h"

void test1();
void test2();
void test3();
void test4();

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test1(){
    DESCRIBE("SEQUENCIAL - 50 lines");
    WHEN("TEST1");
    IF("teste1.txt");
    THEN("the result should be 100");
    //clock_t begin = clock();
    isEqual(ocorrencias("teste1.txt","ll", 1),100);
    /*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
void test2(){
    DESCRIBE("SEQUENCIAL - 5.000 lines");
    WHEN("TEST2");
    IF("teste2.txt");
    THEN("the result should be 10.000");
    //clock_t begin = clock();
    isEqual(ocorrencias("teste2.txt","ll", 1),10000);
    /*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
void test3(){
    DESCRIBE("SEQUENCIAL - 25.000 lines");
    WHEN("TEST3");
    IF("teste3.txt");
    THEN("the result should be 50.000");
    //clock_t begin = clock();
    isEqual(ocorrencias("teste3.txt","ll", 1),50000);
    /*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
void test4(){
    DESCRIBE("SEQUENCIAL - 50.000 lines");
    WHEN("TEST4");
    IF("teste4.txt");
    THEN("the result should be 100.000");
    //clock_t begin = clock();
    isEqual(ocorrencias("teste4.txt","ll", 1),100000);
    /*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
