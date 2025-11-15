#include <stdio.h>


int putere(int baza, int exponent){
    int i=0;
    int nr=1;
    while(i<exponent){
        nr = nr * baza;
        i++;
    }

    return nr;
}

int main(void){

    int baza=0;
    int exponent=0;
    printf("Baza are valoarea : ");
    scanf("%d", &baza);
    printf("Baza are valoarea : ");
    scanf("%d", &exponent);

    int nrnou = 0;
    nrnou = putere(baza,exponent);

    printf("%d la puterea %d este egal cu %d ",baza,exponent,nrnou);
    return 0;
}