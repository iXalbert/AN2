#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], visited[MAX], recStack[MAX], n;

int hasCycle(int u) {
    visited[u] = recStack[u] = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (!visited[v] && hasCycle(v))
                return 1;
            else if (recStack[v])
                return 1;
        }
    }
    recStack[u] = 0;
    return 0;
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && hasCycle(i)) {
            printf("Graful are ciclu\n");
            return 0;
        }
    }

    printf("Graful NU are ciclu\n");
    return 0;
}
