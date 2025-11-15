#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Structura pentru un nod de produs
typedef struct Product {
    int code;  // Codul produsului
    struct Product* next;  // Pointer la următorul produs
} Product;

// Structura pentru un magazin
typedef struct Store {
    char name[MAX_NAME_LENGTH];  // Numele magazinului
    Product* productList;  // Lista de produse
    struct Store* next;  // Pointer la următorul magazin
} Store;

// Functie pentru crearea unui produs nou
Product* create_product(int code) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    newProduct->code = code;
    newProduct->next = NULL;
    return newProduct;
}

// Functie pentru crearea unui magazin nou
Store* create_store(const char* name) {
    Store* newStore = (Store*)malloc(sizeof(Store));
    strncpy(newStore->name, name, MAX_NAME_LENGTH);
    newStore->productList = NULL;
    newStore->next = NULL;
    return newStore;
}

// Functie pentru inserarea unui produs ordonat in lista unui magazin
void insert_product(Store* store, int code) {
    Product* newProduct = create_product(code);
    if (store->productList == NULL || store->productList->code > code) {
        newProduct->next = store->productList;
        store->productList = newProduct;
        return;
    }
    Product* current = store->productList;
    while (current->next != NULL && current->next->code < code) {
        current = current->next;
    }
    newProduct->next = current->next;
    current->next = newProduct;
}

// Functie pentru eliminarea unui produs dupa cod din toate magazinele
void remove_product_from_all_stores(Store* head, int code) {
    Store* currentStore = head;
    while (currentStore != NULL) {
        Product* currentProduct = currentStore->productList;
        Product* prevProduct = NULL;
        while (currentProduct != NULL) {
            if (currentProduct->code == code) {
                if (prevProduct == NULL) {
                    currentStore->productList = currentProduct->next;
                } else {
                    prevProduct->next = currentProduct->next;
                }
                free(currentProduct);
                break;  // Trecem la urmatorul magazin dupa gasirea produsului
            }
            prevProduct = currentProduct;
            currentProduct = currentProduct->next;
        }
        currentStore = currentStore->next;
    }
}

// Functie pentru afisarea listei de magazine si produse
void display_stores(Store* head) {
    Store* currentStore = head;
    while (currentStore != NULL) {
        printf("Magazin: %s\n", currentStore->name);
        Product* currentProduct = currentStore->productList;
        printf(" Produse: ");
        while (currentProduct != NULL) {
            printf("%d ", currentProduct->code);
            currentProduct = currentProduct->next;
        }
        printf("\n");
        currentStore = currentStore->next;
    }
}

int main() {
    // Creare lista de magazine
    Store* store1 = create_store("Magazin A");
    Store* store2 = create_store("Magazin B");
    Store* store3 = create_store("Magazin C");

    // Conectare magazine
    store1->next = store2;
    store2->next = store3;

    // Adaugare produse
    insert_product(store1, 12345678);
    insert_product(store1, 87654321);
    insert_product(store1, 23456789);
    insert_product(store1, 34567890);
    insert_product(store1, 98765432);

    insert_product(store2, 11111111);
    insert_product(store2, 22222222);
    insert_product(store2, 33333333);
    insert_product(store2, 44444444);
    insert_product(store2, 55555555);

    insert_product(store3, 66666666);
    insert_product(store3, 77777777);
    insert_product(store3, 88888888);
    insert_product(store3, 99999999);
    insert_product(store3, 12345678);

    printf("Structura inainte de eliminarea produsului:\n");
    display_stores(store1);

    // Eliminare produs cu codul 12345678
    printf("\nEliminare produs cu codul 12345678:\n");
    remove_product_from_all_stores(store1, 12345678);

    printf("Structura dupa eliminarea produsului:\n");
    display_stores(store1);

    return 0;
}
