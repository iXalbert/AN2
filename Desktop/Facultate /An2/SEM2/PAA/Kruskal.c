#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
int parent[MAX], n, m;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    qsort(edges, m, sizeof(Edge), cmp);

    int total = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            printf("Muchie: %d - %d (cost: %d)\n", u, v, edges[i].w);
            unite(u, v);
            total += edges[i].w;
        }
    }

    printf("Cost total: %d\n", total);
    return 0;
}
