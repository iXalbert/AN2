/*
O corporație mare dorește să instaleze o rețea de comunicații sigure între mai multe sedii. 
Fiecare conexiune între două sedii are un cost și rețeaua trebuie să fie construită astfel încât toate sediile să fie interconectate, 
iar costul total să fie minim.

Fișierul de intrare are următoarea structură:

Prima linie conține două numere n și m – numărul de sedii (noduri) și numărul de conexiuni posibile (muchii).
Următoarele m linii conțin triplete a b c, indicând o conexiune între sediul a și b, cu costul c.
Cerință:
Scrieți un program în C care să determine costul minim necesar pentru conectarea tuturor sediilor (construirea arborelui parțial de cost minim). 
Folosiți algoritmul lui Kruskal.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, cost;
} Edge;

int parent[100];
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->cost - ((Edge*)b)->cost;
}

int main() {
    int n, m, i;
    scanf("%d %d", &n, &m);
    
    Edge edges[m];
    for (i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);

    for (i = 1; i <= n; i++)
        parent[i] = i;

    qsort(edges, m, sizeof(Edge), cmp);

    int total = 0, count = 0;
    for (i = 0; i < m && count < n - 1; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            total += edges[i].cost;
            count++;
        }
    }

    printf("Cost minim: %d\n", total);
    return 0;
}
