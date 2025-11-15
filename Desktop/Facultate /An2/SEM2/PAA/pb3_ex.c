/* city planning department needs to connect all neighborhoods to essential utilities 
(water, electricity, gas) at minimum cost. They have cost estimates for running utility lines between different 
areas, including:

Installation costs that vary based on terrain and distance
The requirement that all neighborhoods must be connected (directly or indirectly)
Budget constraints requiring the most economical solution
The need to ensure no redundant connections that don't reduce total cost
Given the cost matrix for connecting different neighborhoods, design an algorithm to determine 
the minimum cost to connect the entire city to utilities. Compare different approaches and analyze 
which is more efficient for this specific application.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structură pentru muchie
typedef struct {
    int u, v;
    int cost;
} Edge;

int parent[MAX];
Edge edges[MAX * MAX];
int n, m; // n = nr. noduri (cartiere), m = nr. muchii

// Comparare muchii pentru sortare
int cmp(const void *a, const void *b) {
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

// Găsește reprezentantul unui set
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Unește două seturi
void unite(int x, int y) {
    parent[find(x)] = find(y);
}

void kruskal() {
    int totalCost = 0;
    int edgeCount = 0;

    qsort(edges, m, sizeof(Edge), cmp);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    printf("🌐 Conexiuni alese pentru rețea:\n");

    for (int i = 0; i < m && edgeCount < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int cost = edges[i].cost;

        if (find(u) != find(v)) {
            unite(u, v);
            totalCost += cost;
            edgeCount++;
            printf("  Cartier %d ↔ Cartier %d (cost: %d)\n", u, v, cost);
        }
    }

    printf("\n💰 Cost total minim: %d\n", totalCost);
}

int main() {
    // Exemplu: 5 cartiere, 7 posibile conexiuni
    n = 5;
    m = 7;
    edges[0] = (Edge){0, 1, 10};
    edges[1] = (Edge){0, 2, 6};
    edges[2] = (Edge){0, 3, 5};
    edges[3] = (Edge){1, 3, 15};
    edges[4] = (Edge){2, 3, 4};
    edges[5] = (Edge){1, 2, 25};
    edges[6] = (Edge){3, 4, 2};

    kruskal();
    return 0;
}
