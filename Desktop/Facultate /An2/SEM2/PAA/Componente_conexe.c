#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], n;

void dfs(int u) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !visited[v])
            dfs(v);
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    int comp = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Componenta %d: ", ++comp);
            dfs(i);
            printf("\n");
        }
    }
    return 0;
}
