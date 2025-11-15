#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

int cost[MAX][MAX], dist[MAX], visited[MAX], n;

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = cost[start][i];
        visited[i] = 0;
    }
    dist[start] = 0;
    visited[start] = 1;

    for (int count = 1; count < n; count++) {
        int min = INF, u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        visited[u] = 1;

        for (int i = 0; i < n; i++)
            if (!visited[i] && cost[u][i] + dist[u] < dist[i])
                dist[i] = cost[u][i] + dist[u];
    }

    for (int i = 0; i < n; i++)
        printf("Distanta la %d: %d\n", i, dist[i]);
}

int main() {
    int m, u, v, w;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        cost[u][v] = w;
    }

    dijkstra(0);
    return 0;
}
