#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX], rev[MAX][MAX], visited[MAX], stack[MAX], top = -1, n;

void dfs1(int u) {
    visited[u] = 1;
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !visited[v])
            dfs1(v);
    stack[++top] = u;
}

void dfs2(int u) {
    visited[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < n; v++)
        if (rev[u][v] && !visited[v])
            dfs2(v);
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        rev[v][u] = 1; // graful invers
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("Componente tare conexe:\n");
    while (top >= 0) {
        int u = stack[top--];
        if (!visited[u]) {
            dfs2(u);
            printf("\n");
        }
    }
    return 0;
}
