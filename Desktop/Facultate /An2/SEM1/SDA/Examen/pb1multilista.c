#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru un produs
typedef struct Produs {
    int cod; // Cod numeric unic (max 8 cifre)
    char nume[30]; // Numele produsului
    struct Produs* next; // Pointer către următorul produs
} Produs;

// Structura pentru un magazin
typedef struct Magazin {
    char nume[30]; // Numele magazinului
    Produs* produse; // Lista de produse a magazinului
    struct Magazin* next; // Pointer către următorul magazin
} Magazin;

// Adăugare produs în lista unui magazin
void adaugaProdus(Magazin* magazin, int cod, const char* nume) {
    Produs* produsNou = (Produs*)malloc(sizeof(Produs));
    produsNou->cod = cod;
    strcpy(produsNou->nume, nume);
    produsNou->next = magazin->produse;
    magazin->produse = produsNou;
}

// Adăugare magazin în lista principală
Magazin* adaugaMagazin(Magazin* head, const char* nume) {
    Magazin* magazinNou = (Magazin*)malloc(sizeof(Magazin));
    strcpy(magazinNou->nume, nume);
    magazinNou->produse = NULL;
    magazinNou->next = head;
    return magazinNou;
}

// Ștergere produs după cod dintr-o listă de produse
void stergeProdusDinMagazin(Magazin* magazin, int cod) {
    Produs *curent = magazin->produse, *anterior = NULL;

    while (curent != NULL) {
        if (curent->cod == cod) {
            if (anterior == NULL) {
                // Produsul de șters este primul din listă
                magazin->produse = curent->next;
            } else {
                anterior->next = curent->next;
            }
            free(curent);
            return;
        }
        anterior = curent;
        curent = curent->next;
    }
}

// Ștergere produs după cod din toate magazinele
void stergeProdus(Magazin* head, int cod) {
    Magazin* curent = head;
    while (curent != NULL) {
        stergeProdusDinMagazin(curent, cod);
        curent = curent->next;
    }
}

// Afișare structura multilista
void afiseazaMagazine(Magazin* head) {
    Magazin* curentMagazin = head;
    while (curentMagazin != NULL) {
        printf("Magazin: %s\n", curentMagazin->nume);
        Produs* curentProdus = curentMagazin->produse;
        while (curentProdus != NULL) {
            printf("  Cod: %d, Nume: %s\n", curentProdus->cod, curentProdus->nume);
            curentProdus = curentProdus->next;
        }
        curentMagazin = curentMagazin->next;
    }
}

int main() {
    // Creăm lista de magazine
    Magazin* magazine = NULL;
    magazine = adaugaMagazin(magazine, "Magazin1");
    magazine = adaugaMagazin(magazine, "Magazin2");
    magazine = adaugaMagazin(magazine, "Magazin3");

    // Adăugăm produse în fiecare magazin
    adaugaProdus(magazine, 101, "Lapte");
    adaugaProdus(magazine, 102, "Paine");
    adaugaProdus(magazine, 103, "Oua");

    adaugaProdus(magazine->next, 104, "Zahar");
    adaugaProdus(magazine->next, 105, "Cafea");
    adaugaProdus(magazine->next, 106, "Ciocolata");

    adaugaProdus(magazine->next->next, 107, "Paste");
    adaugaProdus(magazine->next->next, 108, "Suc");
    adaugaProdus(magazine->next->next, 109, "Ulei");

    printf("Structura multilista initiala:\n");
    afiseazaMagazine(magazine);

    // Ștergem un produs (de exemplu, produsul cu codul 104)
    printf("\nDupa stergerea produsului cu codul 104:\n");
    stergeProdus(magazine, 104);
    afiseazaMagazine(magazine);

    return 0;
}
