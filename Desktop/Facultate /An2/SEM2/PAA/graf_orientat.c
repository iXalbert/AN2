#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* adj[MAX];

void addEdge(int u, int v) {
    Node* node = malloc(sizeof(Node));
    node->val = v;
    node->next = adj[u];
    adj[u] = node;
}

void printGraph(int n) {
    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        for (Node* p = adj[i]; p != NULL; p = p->next)
            printf("%d ", p->val);
        printf("\n");
    }
}

int main() {
    int n, m, u, v;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    printGraph(n);
    return 0;
}
