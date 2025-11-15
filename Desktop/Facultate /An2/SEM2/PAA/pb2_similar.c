/*Context:
Un sistem expert de diagnostic trebuie să determine minimul de întrebări necesare pentru a stabili un diagnostic, folosind o relație de dependență între simptome.

Fișierul de intrare conține:

Prima linie: N întrebări (simptome) și M relații de dependență.
Următoarele M linii conțin perechi (a, b), ceea ce înseamnă că pentru a pune întrebarea b, trebuie ca întrebarea a să fie validată.
Ultima linie conține o listă de simptome considerate „diagnostic final”.
Obiectiv:

Calculați, folosind sortare topologică (BFS), minimul de întrebări necesare pentru a ajunge la un diagnostic.
Afișați un ordin valid de adresare a întrebărilor.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N, M;
int graf[MAX][MAX];
int in_deg[MAX] = {0};
int coada[MAX], front = 0, back = 0;

void topologic_sort() {
    for (int i = 0; i < N; i++) {
        if (in_deg[i] == 0)
            coada[back++] = i;
    }

    while (front < back) {
        int nod = coada[front++];
        printf("%d ", nod);
        for (int i = 0; i < N; i++) {
            if (graf[nod][i]) {
                in_deg[i]--;
                if (in_deg[i] == 0)
                    coada[back++] = i;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graf[a][b] = 1;
        in_deg[b]++;
    }

    printf("Ordine posibila a întrebarilor:\n");
    topologic_sort();

    return 0;
}
