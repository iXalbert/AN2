#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

int cost[MAX][MAX], visited[MAX], n;

void prim() {
    int total = 0;
    visited[0] = 1;

    for (int k = 1; k < n; k++) {
        int min = INF, x = -1, y = -1;
        for (int i = 0; i < n; i++)
            if (visited[i])
                for (int j = 0; j < n; j++)
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        x = i; y = j;
                    }
        visited[y] = 1;
        total += min;
        printf("Muchie: %d - %d (cost: %d)\n", x, y, min);
    }

    printf("Cost total: %d\n", total);
}

int main() {
    int m, u, v, w;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = INF;

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        cost[u][v] = cost[v][u] = w;
    }

    prim();
    return 0;
}
