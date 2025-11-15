/*A social media platform wants to analyze user connections to understand community formation. 
Given friendship data between users, the platform needs to:

Identify isolated groups of friends who have no connections to other groups
Determine the size of the largest friend circle
Find users who could serve as bridges between different communities
Calculate how many separate social clusters exist in the network
You are provided with a dataset of user friendships where each friendship is bidirectional. 
Design an algorithm to analyze these social connections and answer queries about community structure.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int n, m; // utilizatori și prietenii
int adj[MAX][MAX]; // matrice de adiacență
int visited[MAX];
int articulation[MAX];
int low[MAX], disc[MAX], parent[MAX];
int timeDFS = 0;

// ------------------ DFS pentru componente -----------------
int dfs_component(int u) {
    visited[u] = 1;
    int size = 1;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v])
            size += dfs_component(v);
    }
    return size;
}

// ---------------- DFS pentru puncte de articulație ---------------
void dfs_articulation(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeDFS;
    int children = 0;

    for (int v = 0; v < n; v++) {
        if (!adj[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfs_articulation(v);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (parent[u] == -1 && children > 1)
                articulation[u] = 1;
            if (parent[u] != -1 && low[v] >= disc[u])
                articulation[u] = 1;
        } else if (v != parent[u]) {
            if (low[u] > disc[v])
                low[u] = disc[v];
        }
    }
}

int main() {
    printf("📥 Introdu nr. de utilizatori și prietenii (ex: 7 6):\n");
    scanf("%d %d", &n, &m);

    printf("🔗 Introdu perechi de prieteni (ex: 0 1):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    int components = 0;
    int maxGroupSize = 0;

    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int size = dfs_component(i);
            if (size > maxGroupSize)
                maxGroupSize = size;
            components++;
        }
    }

    printf("\n🔍 Nr. de grupuri sociale izolate: %d\n", components);
    printf("👥 Dimensiunea celei mai mari comunități: %d\n", maxGroupSize);

    memset(visited, 0, sizeof(visited));
    memset(articulation, 0, sizeof(articulation));
    memset(parent, -1, sizeof(parent));
    timeDFS = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs_articulation(i);
    }

    printf("🧩 Utilizatori care sunt punți între comunități:\n");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (articulation[i]) {
            printf(" - User %d\n", i);
            found = 1;
        }
    }
    if (!found)
        printf(" (Niciunul)\n");

    return 0;
}
