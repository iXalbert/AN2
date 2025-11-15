/*A manufacturing company tracks supplier relationships to assess supply chain risks. They need to understand:

Which suppliers can ultimately affect each product (direct and indirect dependencies)
How disruption at one supplier could cascade through the supply chain
Which supplier relationships create the most vulnerability
The complete dependency matrix for risk planning
Given supplier relationship data, design an algorithm to compute all possible supply 
chain dependencies and analyze systemic risks.*/

#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];        // graful de dependență
int reachable[MAX][MAX];    // matrice tranzitivă
int n;                      // număr total de noduri (furnizori + produse)
char labels[MAX][30];       // etichetele nodurilor

// Afișează o matrice binară etichetată
void print_matrix(int mat[MAX][MAX]) {
    printf("    ");
    for (int i = 0; i < n; ++i)
        printf("%-6s", labels[i]);
    printf("\n");

    for (int i = 0; i < n; ++i) {
        printf("%-4s", labels[i]);
        for (int j = 0; j < n; ++j) {
            printf("%-6d", mat[i][j]);
        }
        printf("\n");
    }
}

// Algoritmul Floyd-Warshall pentru toate perechile
void floyd_warshall() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            reachable[i][j] = graph[i][j];

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (reachable[i][k] && reachable[k][j])
                    reachable[i][j] = 1;
}

// Găsește nodurile cele mai vulnerabile
void analyze_risks() {
    printf("\n🔍 Risk Analysis:\n");

    // Nume noduri care afectează cele mai multe produse
    int max_out = 0, max_in = 0;
    int out_deg[MAX] = {0}, in_deg[MAX] = {0};

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (reachable[i][j]) {
                out_deg[i]++;
                in_deg[j]++;
            }

    printf("\n➡️  Most influential nodes (can affect many others):\n");
    for (int i = 0; i < n; ++i)
        if (out_deg[i] > n / 2)
            printf("  %s affects %d nodes\n", labels[i], out_deg[i]);

    printf("\n⚠️  Most vulnerable nodes (affected by many):\n");
    for (int i = 0; i < n; ++i)
        if (in_deg[i] > n / 2)
            printf("  %s is affected by %d nodes\n", labels[i], in_deg[i]);
}

int main() {
    // Exemplu: 6 noduri = 3 furnizori + 3 produse
    n = 6;
    strcpy(labels[0], "F1");
    strcpy(labels[1], "F2");
    strcpy(labels[2], "F3");
    strcpy(labels[3], "P1");
    strcpy(labels[4], "P2");
    strcpy(labels[5], "P3");

    // Definim relațiile: F1 -> F2, F2 -> F3, F3 -> P1, F1 -> P2, F2 -> P3
    graph[0][1] = 1;  // F1 → F2
    graph[1][2] = 1;  // F2 → F3
    graph[2][3] = 1;  // F3 → P1
    graph[0][4] = 1;  // F1 → P2
    graph[1][5] = 1;  // F2 → P3

    printf("🔗 Initial dependency matrix:\n");
    print_matrix(graph);

    floyd_warshall();

    printf("\n🌐 Transitive dependency matrix (direct + indirect):\n");
    print_matrix(reachable);

    analyze_risks();

    return 0;
}
