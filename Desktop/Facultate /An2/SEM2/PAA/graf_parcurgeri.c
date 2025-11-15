#include <stdio.h>

#define N 100
#define INF 1000000

int graf[N][N]; // matrice de adiacență
int cost[N][N]; // cost[i][j] = costul muchiei de la i la j (INF dacă nu există)
int dist[N];
int dist2[N][N];
int reach[N][N];
int viz[N];
int n;

void dfs(int nod) {
    viz[nod] = 1;
    printf("%d ", nod);
    for (int i = 0; i < n; i++) {
        if (graf[nod][i] && !viz[i]) {
            dfs(i);
        }
    }
}

void bfs(int start) {
    int coada[N], st = 0, dr = 0;
    coada[dr++] = start;
    viz[start] = 1;

    while (st < dr) {
        int nod = coada[st++];
        printf("%d ", nod);

        for (int i = 0; i < n; i++) {
            if (graf[nod][i] && !viz[i]) {
                viz[i] = 1;
                coada[dr++] = i;
            }
        }
    }
}

void componente_conexe() {
    for (int i = 0; i < n; i++) {
        if (!viz[i]) {
            printf("Componenta: ");
            dfs(i);  // sau bfs(i);
            printf("\n");
        }
    }
}

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        viz[i] = 0;
    }
    dist[start] = 0;

    for (int k = 0; k < n; k++) {
        int u = -1, min = INF;
        for (int i = 0; i < n; i++)
            if (!viz[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        if (u == -1) break;
        viz[u] = 1;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] != INF && dist[u] + cost[u][v] < dist[v])
                dist[v] = dist[u] + cost[u][v];
        }
    }

    printf("Distantele minime de la %d:\n", start);
    for (int i = 0; i < n; i++)
        printf("-> %d: %d\n", i, dist[i]);
}

void prim() {
    int parent[N], key[N];
    int inMST[N] = {0};

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        parent[i] = -1;
    }
    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1, min = INF;
        for (int i = 0; i < n; i++)
            if (!inMST[i] && key[i] < min) {
                min = key[i];
                u = i;
            }

        inMST[u] = 1;

        for (int v = 0; v < n; v++)
            if (cost[u][v] && !inMST[v] && cost[u][v] < key[v]) {
                key[v] = cost[u][v];
                parent[v] = u;
            }
    }

    printf("Muchii în MST:\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d : %d\n", parent[i], i, cost[i][parent[i]]);
}

typedef struct {
    int u, v, cost;
} Muchie;

int t[N]; // părintele din DSU

int gaseste(int x) {
    if (t[x] != x)
        t[x] = gaseste(t[x]);
    return t[x];
}

void uneste(int x, int y) {
    t[gaseste(x)] = gaseste(y);
}

int cmp(const void* a, const void* b) {
    return ((Muchie*)a)->cost - ((Muchie*)b)->cost;
}

void kruskal(Muchie muchii[], int n, int m) {
    for (int i = 0; i < n; i++)
        t[i] = i;

    qsort(muchii, m, sizeof(Muchie), cmp);

    int total = 0;
    printf("Muchii in arborele de acoperire minim:\n");
    for (int i = 0; i < m; i++) {
        int u = muchii[i].u;
        int v = muchii[i].v;
        if (gaseste(u) != gaseste(v)) {
            uneste(u, v);
            total += muchii[i].cost;
            printf("%d - %d (cost %d)\n", u, v, muchii[i].cost);
        }
    }
    printf("Cost total: %d\n", total);
}

void floyd_warshall() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist2[i][k] + dist2[k][j] < dist2[i][j])
                    dist2[i][j] = dist2[i][k] + dist2[k][j];
}

void print_dist() {
    printf("Matricea distantelor minime:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist2[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist2[i][j]);
        }
        printf("\n");
    }
}

void warshall() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
}

void print_warshall() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", reach[i][j]);
        printf("\n");
    }
}