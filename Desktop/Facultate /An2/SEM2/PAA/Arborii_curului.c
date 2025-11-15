#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------
// 1. ARBORE BINAR SIMPLU (Binary Search Tree - BST)
//---------------------------------------------------
typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

// Inserare în arbore binar simplu
Node* insertBST(Node* root, int val) {
    if (!root) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->val = val;
        node->left = node->right = NULL;
        return node;
    }
    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}

// Căutare minim în subarbore (necesar la ștergere)
Node* minNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Ștergere nod din arbore binar simplu
Node* deleteBST(Node* root, int val) {
    if (!root) return NULL;
    if (val < root->val)
        root->left = deleteBST(root->left, val);
    else if (val > root->val)
        root->right = deleteBST(root->right, val);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minNode(root->right);
        root->val = temp->val;
        root->right = deleteBST(root->right, temp->val);
    }
    return root;
}

//----------------------------------------
// 2. ARBORE BINAR COMPLET (MinHeap simplu)
//----------------------------------------
#define MAX_HEAP 100

typedef struct {
    int data[MAX_HEAP];
    int size;
} MinHeap;

MinHeap* createHeap() {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->size = 0;
    return h;
}

// Mutăm în sus pentru menținerea heapului
void heapifyUp(MinHeap* h, int index) {
    while (index && h->data[index] < h->data[(index - 1) / 2]) {
        int temp = h->data[index];
        h->data[index] = h->data[(index - 1) / 2];
        h->data[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Inserare în MinHeap
void insertHeap(MinHeap* h, int val) {
    if (h->size >= MAX_HEAP) return;
    h->data[h->size] = val;
    heapifyUp(h, h->size);
    h->size++;
}

// Mutăm în jos pentru menținerea heapului
void heapifyDown(MinHeap* h, int index) {
    int smallest = index, l = 2 * index + 1, r = 2 * index + 2;
    if (l < h->size && h->data[l] < h->data[smallest]) smallest = l;
    if (r < h->size && h->data[r] < h->data[smallest]) smallest = r;
    if (smallest != index) {
        int temp = h->data[index];
        h->data[index] = h->data[smallest];
        h->data[smallest] = temp;
        heapifyDown(h, smallest);
    }
}

// Eliminare minim din heap
int deleteMin(MinHeap* h) {
    if (h->size == 0) return -1;
    int root = h->data[0];
    h->data[0] = h->data[--h->size];
    heapifyDown(h, 0);
    return root;
}

//-----------------------------------
// 3. ARBORE AVL (echilibrat automat)
//-----------------------------------
typedef struct AVLNode {
    int val;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

int height(AVLNode* n) { return n ? n->height : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

AVLNode* newAVLNode(int val) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->val = val; node->left = node->right = NULL; node->height = 1;
    return node;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

// Inserare în arbore AVL
AVLNode* insertAVL(AVLNode* node, int val) {
    if (!node) return newAVLNode(val);
    if (val < node->val) node->left = insertAVL(node->left, val);
    else if (val > node->val) node->right = insertAVL(node->right, val);
    else return node; // fără duplicate
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && val < node->left->val) return rotateRight(node);
    if (balance < -1 && val > node->right->val) return rotateLeft(node);
    if (balance > 1 && val > node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

//--------------------------------------
// 4. ARBORE B (de ordine T = 3 = maxim 5 chei)
//--------------------------------------
#define T 3

typedef struct BNode {
    int keys[2 * T - 1];
    struct BNode* children[2 * T];
    int n;
    int leaf;
} BNode;

BNode* createBNode(int leaf) {
    BNode* node = (BNode*)malloc(sizeof(BNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < 2 * T; i++) node->children[i] = NULL;
    return node;
}

void splitChild(BNode* x, int i, BNode* y) {
    BNode* z = createBNode(y->leaf);
    z->n = T - 1;
    for (int j = 0; j < T - 1; j++) z->keys[j] = y->keys[j + T];
    if (!y->leaf)
        for (int j = 0; j < T; j++) z->children[j] = y->children[j + T];
    y->n = T - 1;
    for (int j = x->n; j >= i + 1; j--) x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n++;
}

void insertNonFull(BNode* x, int k);

// Inserare în arbore B
void insertB(BNode** root, int k) {
    BNode* r = *root;
    if (r->n == 2 * T - 1) {
        BNode* s = createBNode(0);
        s->children[0] = r;
        splitChild(s, 0, r);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull(s->children[i], k);
        *root = s;
    } else {
        insertNonFull(r, k);
    }
}

void insertNonFull(BNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > k) i--;
        i++;
        if (x->children[i]->n == 2 * T - 1) {
            splitChild(x, i, x->children[i]);
            if (x->keys[i] < k) i++;
        }
        insertNonFull(x->children[i], k);
    }
}

//arbore de regasire


#define N 100

typedef struct Nod {
    char val;
    int st, dr;
} Nod;

Nod arbore[N];
int n;

void inorder(int rad) {
    if (rad == -1) return;
    inorder(arbore[rad].st);
    printf("%c", arbore[rad].val);
    inorder(arbore[rad].dr);
}

void preorder(int rad) {
    if (rad == -1) return;
    printf("%c", arbore[rad].val);
    preorder(arbore[rad].st);
    preorder(arbore[rad].dr);
}

void postorder(int rad) {
    if (rad == -1) return;
    postorder(arbore[rad].st);
    postorder(arbore[rad].dr);
    printf("%c", arbore[rad].val);
}

int gaseste_radacina() {
    int este_copil[N] = {0};
    for (int i = 0; i < n; i++) {
        if (arbore[i].st != -1) este_copil[arbore[i].st] = 1;
        if (arbore[i].dr != -1) este_copil[arbore[i].dr] = 1;
    }
    for (int i = 0; i < n; i++)
        if (!este_copil[i])
            return i;
    return -1; // fallback (nu ar trebui să se întâmple)
}

int main() {
    // Exemplu de input:
    // 7
    // A -1 1
    // B 2 3
    // C -1 -1
    // D -1 -1
    // E 5 6
    // F -1 -1
    // G -1 -1

    printf("Introdu numarul de noduri: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char ch;
        int s, d;
        scanf(" %c %d %d", &ch, &s, &d);
        arbore[i].val = ch;
        arbore[i].st = s;
        arbore[i].dr = d;
    }

    int rad = gaseste_radacina();

    printf("\n🔠 Codurile secrete:\n");

    printf("Inordine:     ");
    inorder(rad);
    printf("\n");

    printf("Preordine:    ");
    preorder(rad);
    printf("\n");

    printf("Postordine:   ");
    postorder(rad);
    printf("\n");

    return 0;
}
