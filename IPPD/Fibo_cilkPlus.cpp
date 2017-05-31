#include <iostream>
#include <cilk.h>
using namespace std;

unsigned long int Fibo (unsigned long int n) {
    return (n >= 2 ? Fibo(n-1) + Fibo(n-2) : n);
}

int main(){
    int i = 0;
    unsigned long int vet[100];

    cilk_for( i = 0; i < 100 ; i++){
        vet[i] = Fibo(40);
        cout << i << endl;
    }
}
