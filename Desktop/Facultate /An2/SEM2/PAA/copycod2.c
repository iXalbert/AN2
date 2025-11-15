//copiere cod arbori

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int val;
    struct Node *left;
    struct Node *right;
}Node;

//Arbore binar

Node *inserBST(Node *root, int val){

    if(!root){
        Node *node = (Node*)malloc(sizeof(Node));
        node->val = val;
        node->left=node->right = NULL;
        return node;
    }

    if(val < root->val){
        root->left = inserBST(root->left,val);
    }else{
        root->right = inserBST(root->right,val);
    }

    return root;
}

Node *minNode(Node* node){

    while(node && node->left)
        node = node->left;
    return node;
}

//Arbore AVL

typedef struct AVLnode{

    int val;
    struct AVLnode *left;
    struct AVLnode *right;
    int height;
}AVLnode;

int height(AVLnode *n){
    if(n->height)
    return n;
    else
    return 0;
}

int max(int a, int b){

    if(a > b)
    return a;
    else
    return b;
}

AVLnode *newAVLnode(int val){

    AVLnode *node = (AVLnode*)malloc(sizeof(AVLnode));
    node->val = val;
    node->left = node->right = NULL;
    node->height = 1;
}

AVLnode *rotateRight(AVLnode *y){

    AVLnode *x = y->left;
    AVLnode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    
    return x;
}

AVLnode *rotateLeft(AVLnode *x){

    AVLnode *y = x->right;
    AVLnode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),height(x->right)) + 1; 
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}

int getBalaance(AVLnode *n){

    if(height(n->left) - height(n->right))
    return n;
    else
    return 0;
}

 AVLnode *insertAVL(AVLnode *node,int val){

    if(!node)
    return newAVLnode;

    if(val < node->val)
        node->left = insertAVL(node->left,val);
    else if(val > node->val)
        node->right = insertAVL(node->right,val);
    else 
        return node;
    
    node->height = 1 + max(height(node->left),height(node->right));
    
    int balance = getBalaance(node);

    if(balance > 1 && val < node->left->val)
        return rotateRight(node);
    else if(balance < -1 && val > node->right->val)
        return rotateLeft(node);
    else if(balance > 1 && val > node->left->val){
        node->left = rotateLeft(node);
        return rotateRight(node);
    }
    else if(balance < -1 && val > node->right->val){
        node->right = rotateRight(node);
        return rotateLeft(node);
    }

    return node;
 }

 //Arbore B (de ordin 3)

 #define T 3

 typedef struct Bnode{

    int keys[2 * T - 1];
    struct Bnode* childern[2 * T];
    int n;
    int leaf;
 }Bnode;

 Bnode* createBnode(int leaf){

    Bnode* node = (Bnode*)malloc(sizeof(Bnode));
    node->n = 0;
    node->leaf = leaf;
    for(int i=0;i< 2*T;i++)
        node->childern[i] = NULL;
    return node;
 }

 void splitChild(Bnode *x, int i, Bnode* y){

    Bnode* z = createBnode(y->leaf);

    z->n = T-1;
 
    for(int j=0;j<T-1;j++)
        z->keys[j] = y->keys[j+T];

    if(!y->leaf)
        for(int j=0;j<T;j++)
            z->childern[j] = y->childern[j+T];
    
    y->n = T-1;

    for(int j = x->n;j>=1;j--)
        x->childern[j+1] = x->childern[j];

    x->childern[i+1] = z;

    for(int j = x->n;j>=i;j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[T-1];

    x->n++;

 }

 void insertNonFull(Bnode* x, int k);

 void insertB(Bnode** root, int k){

    Bnode* r = *root;
    if(r->n == 2 * T -1){

        Bnode* s = createBnode(0);
        s->childern[0] = r;
        splitChild(s,0,r);
        int i=0;
        if(s->keys[0] < k)
            i++;
        insertNonFull(s->childern[i],k);
        *root=s;
    }else{
        insertNonFull(r,k);
    }
 }

 void insertNonFull(Bnode* x, int k){

    int i = x->n-1;

    if(x->leaf){

        while(i>=0 && x->keys[i] > k){
            x->keys[i+1] = x->keys[i];
            i--;
        }

        x->keys[i+1] = k;
        x->n++;
    }else{
        while(i>=0 && x->keys[i] > k)
            i--;
        i++;
        if(x->childern[i]->n == 2*T-1){
            splitChild(x,i,x->childern[i]);
            if(x->keys[i]<k)
                i++;
        }

        insertNonFull(x->childern[i],k);
    }
 }