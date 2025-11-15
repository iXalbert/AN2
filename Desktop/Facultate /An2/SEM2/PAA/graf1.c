#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX 100

/*
Sa se redacteze un program care citeste de la intrarea standard doua 
numere N -reprezentand numarul de noduri si M reprezentand numarul de arce, 
apoi citeste M perechi de valori, fiecare pereche reprezentand un arc.
Programul insereaza N noduri in graf, avand cheile de la 1 la N inclusiv. Apoi insereaza cele M arce.
Programul afiseaza in ordine crescatoare cheile care respecta urmatoarea regula:
• pornind de la aceasta cheie, atat parcugerea in adancime cat si in cuprindere a unei componente
conexe genereaza aceeasi secventa de chei
*/
int m,n;
int graf[MAX][MAX];
int vizitat[MAX];
int secventa[MAX], i_secventa = 0;

void dfs(int nod){
    vizitat[nod] = 1;
    secventa[i_secventa++] = nod;
    for(int i=1 ; i <= n ; i++){
        if(graf[nod][i])
            if(!vizitat[i]){
            dfs(i);
        }
    }
}

int compar(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int verifica_componenta(int start) {
    for (int i = 1; i <= n; i++)
        vizitat[i] = 0;
    i_secventa = 0;
    dfs(start);

    int *aux = malloc(i_secventa * sizeof(int));
    for (int i = 1; i <= i_secventa; i++) {
        aux[i] = secventa[i];
    }
    qsort(aux, i_secventa, sizeof(int), compar);
    for (int i = 1; i <= i_secventa; i++) {
        if (aux[i] != secventa[i]) {
            free(aux);
            return 0;
        }
    }
    free(aux);
    return 1;
}


int main(){
    
    //FILE *f = fopen("grafuri.txt", "r");
    FILE *f = fopen("grafuri2.txt", "r");
    if (!f) {
        printf("Eroare la deschiderea fișierului: %s\n", strerror(errno));
        return 1;
    }

/*
    fscanf(f, "%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        fscanf(f, "%d %d", &a, &b);
        graf[a][b] = graf[b][a] = 1;
    }
*/

    fscanf(f, "%d", &n);

    for(int i = 1; i <= n ; i++){
        for(int j = 1; j <= n; j++){
            fscanf(f,"%d", &graf[i][j]);
        }
    }




    for (int i = 1; i <= n; i++) {
        if (verifica_componenta(i)) {
            printf("%d ", i);
        }
    } 
    printf("\n");

    fclose(f);
    return 0;
}