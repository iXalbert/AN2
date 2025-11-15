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
    dfs(0);
    return 0;
}
