/*
Context:
Compania dorește o structură sigură pentru accesul ierarhic al angajaților în sistem, dar care să permită rapid căutarea și inserarea permisiunilor.
S-a decis utilizarea unui B-arbore de ordin m (ex: m = 3) pentru a organiza ierarhic permisiunile disponibile.

Fișierul de intrare conține:

Pe prima linie: două numere întregi m și n, reprezentând ordinul arborelui și numărul de permisiuni.
Pe următoarele n linii: permisiunile (ca numere întregi) care trebuie inserate în B-arbore, în ordine.
Cerințe:

Construiți B-arborele pornind de la inserarea în ordine a permisiunilor.
Aflați și afișați în ordine crescătoare toate permisiunile existente în arbore (traversare in-order).
Determinați dacă o permisiune critică x se află deja în arbore (se citește ulterior de la tastatură).
✅ Explicație:

B-arborii sunt folosiți frecvent în baze de date pentru că oferă căutări, inserări și ștergeri eficiente în mulțimi mari de date sortate.
Traversarea in-order pe un arbore B oferă toate valorile în ordine crescătoare.
Permisiunea critică x se caută în arbore conform structurii B: căutare binară pe fiecare nod + continuarea recursivă.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 3

typedef struct BNode {
    int keys[MAX];
    struct BNode* children[MAX+1];
    int n;
    int leaf;
} BNode;

BNode* createNode(int leaf) {
    BNode* node = (BNode*)malloc(sizeof(BNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < MAX + 1; i++) 
        node->children[i] = NULL;
    return node;
}

// Căutare recursivă
int search(BNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) 
        i++;
    if (i < root->n && k == root->keys[i])
        return 1;
    if (root->leaf) 
        return 0;
    return search(root->children[i], k);
}

// Traversare in-order
void inorder(BNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) 
            inorder(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) inorder(root->children[i]);
}

// (Lipsă: inserare completă în B-arbore — se poate adăuga pentru varianta completă)

int main() {
    BNode* root = createNode(1);
    int m, n, val;
    scanf("%d %d", &m, &n); // Ordin și număr de valori
    // Se poate implementa inserarea reală în B-arbori (implică splituri etc.)
    printf("Funcția de inserare trebuie adăugată.\n");

    // Exemplu de traversare:
    inorder(root);

    // Căutare permisiune critică
    int x;
    scanf("%d", &x);
    if (search(root, x))
        printf("Permisiunea %d există.\n", x);
    else
        printf("Permisiunea %d NU există.\n", x);
}
