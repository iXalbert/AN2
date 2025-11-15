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
#include "timer.c"

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
        while(exista(v+i,i,nr))
        {
            nr = rand() % n + 1;
        }

        v[i] = nr;

    }
}

void bubble_sort(int v[], int n)
{
    int aux;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(v[i] > v[j]){
                aux = v[j];
                v[j] = v[j];
                v[i] = aux;
            }
        }
    }
}

int main(void)
{   
    float timp;//,sumatimp=0;
    int *v = NULL;
    int n=10000;
    srand(time(NULL));
    for(int i=0;i<10;i++){
        if( ( v = malloc( n * sizeof(int))) == NULL ){
            printf("Eroare la alocare\n");
            exit(-1);
        }
        generare_numere(v,n);
        //for(int i=0;i<50;i++)
        //printf("%d  ", v[i]);
        starton();
        bubble_sort(v,n);   
        timp = startoff();
        printf("%f\n",timp);
        //sumatimp=sumatimp+timp;
        //free(v);
        n = n + 10000;
    }

    return 0;
}

