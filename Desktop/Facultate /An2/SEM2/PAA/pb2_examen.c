#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_LINE 256

typedef struct Nod {
    int id;
    int raspuns; // 1 = adevărat, 0 = fals
    char intrebare[200];
} Nod;

int main() {
    FILE *f = fopen("intrebari.txt", "r");
    if (!f) {
        printf("Nu s-a putut deschide fișierul.\n");
        return 1;
    }

    Nod arbore[MAX_N];  // vector de noduri
    int n = 0;

    // Citim fișierul linie cu linie
    char linie[MAX_LINE];
    while (fgets(linie, sizeof(linie), f)) {
        int id, raspuns;
        char intrebare[200];

        // Extragem id și raspuns (primii doi intregi), restul e întrebare
        sscanf(linie, "%d %d %[^\n]", &id, &raspuns, intrebare);

        arbore[id].id = id;
        arbore[id].raspuns = raspuns;
        strcpy(arbore[id].intrebare, intrebare);

        if (id > n) n = id; // ținem minte maximul
    }

    fclose(f);

    // Parcurgere binară începând de la nodul 1
    int curent = 1;
    int count = 0;
    int traseu[MAX_N];

    while (curent <= n && arbore[curent].raspuns == 1) {
        traseu[count++] = curent;
        // mergem pe copilul stâng (2 * curent)
        curent = 2 * curent;
    }

    printf("Număr maxim întrebări parcurse: %d\n", count);
    printf("Întrebări parcurse:\n");

    for (int i = 0; i < count; i++) {
        int idx = traseu[i];
        printf("[%d] %s\n", arbore[idx].id, arbore[idx].intrebare);
    }

    return 0;
}


/*

1. Alegerea structurii de date și justificare

🔸 a. Structură aleasă: Matrice de adiacență (graf orientat)
Matricea este folosită pentru a reprezenta dependențele între întrebări.
Dacă mat[i][j] == 1, înseamnă că întrebarea j depinde de răspunsul la întrebarea i.
Răspunsurile pacientului sunt păstrate într-un vector raspuns[i] ∈ {0, 1}.
🔸 b. Justificare:
Relația dintre întrebări este de tipul: „dacă răspunsul la i e pozitiv, treci la j”.
Un graf orientat exprimă clar această logică.
Nu putem continua cu întrebările care depind de un răspuns negativ (0), deci trebuie să urmărim doar ramurile valide.
📊 2. Algoritmul propus (în cuvinte)
Pașii:

Citim numărul total de întrebări n și construim o matrice de adiacență.
Citim vectorul de răspunsuri DA/NU (0/1).
Pornim de la întrebarea 0 (prima).
Cât timp mai putem merge:
Dacă răspunsul este 1, mergem la întrebările care depind de întrebarea curentă.
Dacă răspunsul este 0, ne oprim – consultația nu poate continua.
Numărăm câte întrebări am parcurs până la oprire (numărul maxim de întrebări utile).

Am reprezentat sistemul expert ca un graf orientat, în care fiecare întrebare este un nod.
Există o muchie de la întrebarea i la j dacă întrebarea j depinde de un răspuns pozitiv la i.

Am parcurs graful pornind de la întrebarea 0 și am urmărit ramurile unde răspunsul pacientului este pozitiv (1).
În momentul în care întâlnim un 0, ne oprim, deoarece sistemul nu poate continua în mod logic.

Scopul a fost să determinăm numărul maxim de întrebări la care pacientul a răspuns afirmativ, permițând sistemului să avanseze către un diagnostic.
*/