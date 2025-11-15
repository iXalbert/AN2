#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Creare nod nou
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Inserare
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Minimul în arbore (necesar la ștergere)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Ștergere
Node* deleteNode(Node* root, int key) {
    if (!root)
        return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Cazuri:
        // 1. Nod fără copii
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        // 2. Un singur copil
        else if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        // 3. Doi copii
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Traversări
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void preorder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    printf("Inordine: ");
    inorder(root);
    printf("\n");

    printf("Ștergem 20...\n");
    root = deleteNode(root, 20);
    inorder(root); printf("\n");

    printf("Ștergem 30...\n");
    root = deleteNode(root, 30);
    inorder(root); printf("\n");

    printf("Preordine: ");
    preorder(root); printf("\n");

    printf("Postordine: ");
    postorder(root); printf("\n");

    return 0;
}
