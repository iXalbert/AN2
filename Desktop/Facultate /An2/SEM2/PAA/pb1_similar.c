/*
Context:
Serviciul de Securitate are o ierarhie de permisiuni, unde permisiunea A permite accesul la B, iar B la C etc. 
Unele permisiuni se pot activa doar dacă utilizatorul are deja o altă permisiune. Accesul este modelat ca un graf orientat.

Fișierul de intrare conține:

Pe prima linie: un număr întreg N (numărul total de permisiuni).
Următoarele N linii descriu dependențele: fiecare linie conține o listă de permisiuni (indici), separate prin spațiu, 
către care se poate ajunge din permisiunea curentă.
Ultima linie conține un indice P — permisiunea pe care o are utilizatorul.
Obiectiv:

Afișați toate permisiunile care pot fi activate pornind de la P (folosind DFS).
Afișați permisiunea cea mai „de jos” din lanțul de activare (maxim adâncime).
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graf[MAX][MAX];
int vizitat[MAX];
int N;
int adancime_maxima = 0;
int permisie_max = -1;

void dfs(int nod, int adancime) {
    vizitat[nod] = 1;
    if (adancime > adancime_maxima) {
        adancime_maxima = adancime;
        permisie_max = nod;
    }
    for (int i = 0; i < N; i++) {
        if (graf[nod][i] && !vizitat[i]) {
            dfs(i, adancime + 1);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x;
        while (scanf("%d", &x) == 1) {
            graf[i][x] = 1;
            if (getchar() == '\n') break;
        }
    }

    int start;
    scanf("%d", &start);

    dfs(start, 0);

    printf("Permisiuni accesibile din %d:\n", start);
    for (int i = 0; i < N; i++) {
        if (vizitat[i]) printf("%d ", i);
    }
    printf("\nPermisiunea cea mai adanca: %d\n", permisie_max);

    return 0;
}
