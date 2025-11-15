#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* nou(int n, Node* urmator) {
    Node* nodNou = (Node*)malloc(sizeof(Node));
    nodNou->data = n;
    nodNou->next = urmator;
    return nodNou;
}

Node* adaugaInceput(Node* lista, int n) {
    return nou(n, lista); 
}

int NrNod(Node* lista) {
    if (lista == NULL) {
        return 0;
    }
    return 1 + NrNod(lista->next);
}

void deleteList(Node* lista) {
    Node* temp = NULL;
    while (lista != NULL) {
        temp = lista;
        lista = lista->next;
        free(temp);
    }
}

int main() {
    Node* lista = NULL;  

    lista = adaugaInceput(lista, 0);
    lista = adaugaInceput(lista, 1);
    lista = adaugaInceput(lista, 2);
    lista = adaugaInceput(lista, 3);

    int nr = NrNod(lista);
    printf("Numărul de noduri din listă este: %d\n", nr);

    deleteList(lista);
    
    return 0;
}
