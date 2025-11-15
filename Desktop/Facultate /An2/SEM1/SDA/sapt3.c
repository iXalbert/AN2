/*1. Sa se evalueze din punct de vedere al timpului de executie algoritmii de sortare bubblesort si shakersort, 
 * folosind functiie din timer.h/timer.c si sa se compare performantele acestora pentru acelasi set de date 
 * (ex. N1=10 000, N2= 20 000, ... N10=100 000). \
 * Sa se scrie timpii de executie intr-un fisier txt in urmatorul format, pe cate o linie separata:
    Algoritm, N1, timp_executie
    Algoritm, N2, timp_executie 
....
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

int exista(int v[], int n, int nr)
{
    for(int i=0;i<n;i++)
        if(v[i] == nr)
        return 1;
    return 0;
}

void generare_numere(int v[], int n)
{
    for(int i=0;i<n;i++){
        int nr = rand() % n + 1;
        while(exista(v,n,nr))
        {
            nr = rand() % n + 1;
        }
    }
}

void bubble_sort(int v[], int n)
{
    int aux;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(v[i] > v[j]){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

int main(void)
{
    float timp;
    int *v = NULL;
    int n=10000;
    for(int i=0;i<10;i++){
        if( ( v = malloc( n * sizeof(int))) == NULL ){
            printf("Eroare la alocare\n");
            exit(-1);
        }
        generare_numere(v,n);
        starton();
        bubble_sort(v,n);   
        timp = startoff();
        printf("%f",timp);
        n = n + 10000;
    }
}

