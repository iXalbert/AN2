/*

Se consideră un arbore ternar, unde fiecare nod poate avea până la trei copii: stâng, mijloc și drept.

Fiecare nod conține un număr întreg.

Cerință: Scrie un program care citește un arbore ternar (numerele nodurilor și relațiile părinte-copil) și:

Construiește arborele în memorie.
Afișează suma valorilor tuturor nodurilor.
Afișează în ordine preordine (root - stâng - mijloc - drept) toate valorile nodurilor.

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TernaryNode {
    int val;
    struct TernaryNode *left, *middle, *right;
} TernaryNode;

// Funcție pentru creare nod nou
TernaryNode* createNode(int val) {
    TernaryNode* node = (TernaryNode*) malloc(sizeof(TernaryNode));
    node->val = val;
    node->left = node->middle = node->right = NULL;
    return node;
}

// Preordine: root - left - middle - right
void preorder(TernaryNode* root) {
    if (!root) return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->middle);
    preorder(root->right);
}

// Calcul sumă valori noduri
int sumTree(TernaryNode* root) {
    if (!root) return 0;
    return root->val + sumTree(root->left) + sumTree(root->middle) + sumTree(root->right);
}

int main() {
    int N;
    scanf("%d", &N);

    // Citim datele nodurilor în vectori temporari
    int *vals = (int*) malloc(N * sizeof(int));
    int *leftIdx = (int*) malloc(N * sizeof(int));
    int *midIdx = (int*) malloc(N * sizeof(int));
    int *rightIdx = (int*) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &vals[i], &leftIdx[i], &midIdx[i], &rightIdx[i]);
    }

    // Cream toate nodurile
    TernaryNode **nodes = (TernaryNode**) malloc(N * sizeof(TernaryNode*));
    for (int i = 0; i < N; i++) {
        nodes[i] = createNode(vals[i]);
    }

    // Legam copiii
    for (int i = 0; i < N; i++) {
        if (leftIdx[i] != -1) nodes[i]->left = nodes[leftIdx[i]];
        if (midIdx[i] != -1) nodes[i]->middle = nodes[midIdx[i]];
        if (rightIdx[i] != -1) nodes[i]->right = nodes[rightIdx[i]];
    }

    // Considerăm nodul 0 ca rădăcină (de obicei)
    TernaryNode *root = nodes[0];

    // Afișăm suma valorilor
    printf("Suma nodurilor: %d\n", sumTree(root));

    // Afișăm preordine
    printf("Preordine: ");
    preorder(root);
    printf("\n");

    // Eliberare memorie (optional)
    free(vals);
    free(leftIdx);
    free(midIdx);
    free(rightIdx);
    free(nodes);

    return 0;
}
