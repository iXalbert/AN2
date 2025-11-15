#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// cele mai mari doua numere

typedef struct multime{
    int valoare[10000];
    int numar_elem;
    float medie;
    char numem[20];

}multime;

int exista(multime* Multime,int nr)
{
    for(int i=0;i<Multime->numar_elem;i++)
        if(Multime->valoare[i] == nr)
        return 1;
    return 0;
}

void generare(multime* Multime, const char* nume, int n,int p)
{
    Multime->numar_elem = n;
    strcpy(Multime->numem,nume);
    Multime->medie=0;
    int suma=0;
    for(int i=0; i<n ; i++)
    {
        int elem = rand() % p + 1;
        while(exista(Multime,elem))
        {
            elem = rand() % p + 1;
        }

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

multime intersectie(multime* Multime1, multime* Multime2)
{
    multime Mintersectie;
    Mintersectie.numar_elem=0;
    strcpy(Mintersectie.numem,"Intersectiem1m2");
    int suma =0;
    for(int i=0;i<Multime1->numar_elem;i++)
    {
        for(int j=0;j<Multime2->numar_elem;j++)
        {
            if(Multime1->valoare[i] == Multime2->valoare[j])
            {
                Mintersectie.valoare[Mintersectie.numar_elem++] = Multime1->valoare[i];
                suma = suma + Multime1->valoare[i];
            }
        }
    }
    if(Mintersectie.numar_elem > 0)
    {
        Mintersectie.medie = (float)suma / Mintersectie.numar_elem;
    }
    else
    {
        Mintersectie.medie = 0;
    }

    return Mintersectie;
}

void bignum(multime* Multime)
{
    int max1=INT_MIN;
    int max2=INT_MIN;
    for(int i=0;i<Multime->numar_elem;i++)
        {
            if(Multime->valoare[i] > max1)
                max1 = Multime->valoare[i];
        }
    for(int i=0;i<Multime->numar_elem;i++)
        {   
            if((Multime->valoare[i] > max2) && (Multime->valoare[i] != max1))
                max2 = Multime->valoare[i];
        }

    printf("Cele mai mari doua numere din multime sunt %d si %d ", max1,max2);
    printf("\n");
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

    Minter = intersectie(&M1,&M2);
    afisare(&Minter);

    bignum(&M1);
    bignum(&M2);
    return 0;  
}