#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct multime{
    int valoare[10000];
    int numar_elem;
    float medie;
    char numem[20];

}multime;


void generare(multime* Multime, const char* nume, int n,int p)
{
    Multime->numar_elem = n;
    strcpy(Multime->numem,nume);
    Multime->medie=0;
    int suma=0;
    for(int i=0; i<n ; i++)
    {
        int elem = rand() % p + 1;

        Multime->valoare[i] = elem;
        suma = suma + elem;
    }

    Multime->medie = (float)suma / n;
}

void afisare(multime* Multime)
{
    printf("Multimea ");
    printf("\n");
    printf("Are numele %s", Multime->numem);
    printf("\n");
    printf("Are %d elemente ", Multime->numar_elem);
    for(int i=0;i<Multime->numar_elem;i++)
    {
        printf("%d ", Multime->valoare[i]);
    }
    printf("\n");
    printf("Si are media = %f ", Multime->medie);
}

int main(void)
{
    multime M1,M2,Minter;
    int n1,n2;
    printf("Introduceti numarul de elemente din prima multime");
    scanf("%d",&n1);
    printf("Introduceti numarul de elemente din a doua multime");
    scanf("%d",&n2);
    srand(time(NULL));
    int p;
    printf("Sa se genereze numere in intervalul 0 -> p pentru prima multime ");
    printf("Introduceti pe p");
    scanf("%d",&p);

    generare(&M1,"Multime1",n1,p);
    generare(&M2,"Multime2",n2,p);

    afisare(&M1);
    afisare(&M2);
    return 0;  
}