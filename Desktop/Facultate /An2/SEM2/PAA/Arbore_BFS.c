#include <stdio.h>

#define MAX 100

int adj[MAX][MAX], parent[MAX], visited[MAX], n;

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;
    parent[start] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    int m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    bfs(0);

    printf("Arbore de parcurgere (parinti):\n");
    for (int i = 0; i < n; i++)
        printf("Nod %d: Parinte %d\n", i, parent[i]);

    return 0;
}
