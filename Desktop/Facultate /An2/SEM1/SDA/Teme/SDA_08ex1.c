#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int n, Node* urmator) {
    Node* nodNou = (Node*)malloc(sizeof(Node));
    nodNou->data = n;
    nodNou->next = urmator;
    return nodNou;
}

Node* adaugaInceput(Node* lista, int n) {
    return createNode(n, lista); 
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void deleteNode(Node** head_ref, int key) {
    Node* temp = *head_ref;
    Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Nu a fost gasita valoarea ceruta \n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

int main() {
    Node* lista = NULL;  

    lista = adaugaInceput(lista, 2);
    lista = adaugaInceput(lista, 1);
    lista = adaugaInceput(lista, 4);
    lista = adaugaInceput(lista, 3);

    printf("Lista inițială: ");
    printList(lista);

    deleteNode(&lista, 3);
    printf("Lista după ștergerea nodului cu cheia 3: ");
    printList(lista);

    deleteNode(&lista, 1);
    printf("Lista după ștergerea nodului cu cheia 1: ");
    printList(lista);

    deleteNode(&lista, 5);
    return 0;
}
