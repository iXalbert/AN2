#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], n;

int dfs(int u, int parent) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v]) {
                if (!dfs(v, u)) 
                    return 0;
            } else if (v != parent) {
                return 0; // ciclu
            }
        }
    }
    return 1;
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    if (dfs(0, -1)) {
        for (int i = 0; i < n; i++)
            if (!visited[i]) {
                printf("Nu este arbore\n");
                return 0;
            }
        printf("Este arbore\n");
    } else {
        printf("Nu este arbore\n");
    }

    return 0;
}
