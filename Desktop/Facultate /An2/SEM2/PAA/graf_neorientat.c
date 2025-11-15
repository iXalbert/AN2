#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int n, m;
int matrice[MAX][MAX];
int distanta[MAX];
int vizitat[MAX];

int minim() {
    int min = INT_MAX, pozitie = -1;
    for (int i = 0; i < n; i++) {
        if (!vizitat[i] && distanta[i] < min) {
            min = distanta[i];
            pozitie = i;
        }
    }
    return pozitie;
}

void dijkstra(int sursa) {
    for (int i = 0; i < n; i++) {
        distanta[i] = INT_MAX;
        vizitat[i] = 0;
    }
    distanta[sursa] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = minim();
        if (u == -1) break;
        vizitat[u] = 1;

        for (int v = 0; v < n; v++) {
            if (matrice[u][v] && !vizitat[v] && distanta[u] + matrice[u][v] < distanta[v]) {
                distanta[v] = distanta[u] + matrice[u][v];
            }
        }
    }

    printf("Distante minime de la nodul %d:\n", sursa);
    for (int i = 0; i < n; i++) {
        if (distanta[i] == INT_MAX)
            printf("Nodul %d: INF\n", i);
        else
            printf("Nodul %d: %d\n", i, distanta[i]);
    }
}

int main() {
    FILE *fisier = fopen("graf.txt", "r");
    if (!fisier) {
        printf("Nu s-a putut deschide fisierul.\n");
        return 1;
    }

    fscanf(fisier, "%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y, cost;
        fscanf(fisier, "%d %d %d", &x, &y, &cost);
        matrice[x][y] = cost;
    }

    fclose(fisier);

    int sursa = 0;
    dijkstra(sursa);

    return 0;
}
