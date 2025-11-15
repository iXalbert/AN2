#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3  // Ordinul arborelui

typedef struct BTreeNode {
    int keys[2*T - 1];                  // Cheile
    struct BTreeNode* children[2*T];   // Copiii
    int n;                              // Numărul de chei
    bool leaf;                          // Este frunză?
} BTreeNode;

// Creează un nou nod B
BTreeNode* createNode(bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

// Afișează ierarhic arborele
void printTree(BTreeNode* root, int depth) {
    if (root) {
        for (int i = 0; i < depth; i++) printf("    ");
        printf("[");
        for (int i = 0; i < root->n; i++) {
            printf("%d", root->keys[i]);
            if (i < root->n - 1) printf(" ");
        }
        printf("]\n");
        if (!root->leaf) {
            for (int i = 0; i <= root->n; i++)
                printTree(root->children[i], depth + 1);
        }
    }
}

// Split la fiul plin al unui nod
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    // Mutăm ultimele chei
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    // Mutăm copiii dacă nu e frunză
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    // Mutăm copiii în parent
    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = z;

    // Mutăm cheia mediana
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = y->keys[T - 1];

    parent->n++;
}

// Inserare într-un nod neplin
void insertNonFull(BTreeNode* node, int k) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && k < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && k < node->keys[i]) i--;

        if (node->children[i + 1]->n == 2*T - 1) {
            splitChild(node, i + 1, node->children[i + 1]);
            if (k > node->keys[i + 1])
                i++;
        }
        insertNonFull(node->children[i + 1], k);
    }
}

// Inserare într-un arbore B
void insert(BTreeNode** rootRef, int k) {
    BTreeNode* root = *rootRef;

    if (root->n == 2*T - 1) {
        BTreeNode* s = createNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = (k > s->keys[0]) ? 1 : 0;
        insertNonFull(s->children[i], k);
        *rootRef = s;
    } else {
        insertNonFull(root, k);
    }
}

// Main pentru testare
int main() {
    BTreeNode* root = createNode(true);

    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < sizeof(keys)/sizeof(int); i++)
        insert(&root, keys[i]);

    printf("Structura B-arborelui:\n");
    printTree(root, 0);

    return 0;
}
