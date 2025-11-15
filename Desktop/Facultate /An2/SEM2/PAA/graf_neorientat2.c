#include <stdio.h>

#define MAX 100

int main() {
    int n, m, u, v;
    int a[MAX][MAX] = {0};

    printf("Numar noduri: ");
    scanf("%d", &n);
    printf("Numar muchii: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        a[u][v] = 1;
        a[v][u] = 1;
    }

    printf("\nMatrice de adiacenta:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    return 0;
}
