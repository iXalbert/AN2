#include <stdio.h>
#include <string.h>

#define NUM_CULORI 6
#define LUNGIME_STEAG 3

// Culorile disponibile
char culori[NUM_CULORI][10] = {"alb", "galben", "rosu", "verde", "albastru", "negru"};
// Matrice pentru a reține steagurile generate
char solutii[100][LUNGIME_STEAG][10];
int index_solutii = 0;

// Funcția de verificare
int esteValid(char steag[LUNGIME_STEAG][10]) {
    // Verificăm dacă culoarea din mijloc este galben
    if (strcmp(steag[1], "galben") != 0) {
        return 0;
    }

    // Verificăm dacă toate culorile sunt distincte
    if (strcmp(steag[0], steag[1]) == 0 || strcmp(steag[1], steag[2]) == 0 || strcmp(steag[0], steag[2]) == 0) {
        return 0;
    }

    return 1;
}

// Funcția de backtracking
void backtracking(int pas, char steag[LUNGIME_STEAG][10]) {
    // Dacă am construit un steag complet (3 culori), verificăm dacă e valid
    if (pas == LUNGIME_STEAG) {
        if (esteValid(steag)) {
            // Salvăm soluția validă
            for (int i = 0; i < LUNGIME_STEAG; i++) {
                strcpy(solutii[index_solutii][i], steag[i]);
            }
            index_solutii++;
        }
        return;
    }

    // Iterăm prin toate culorile disponibile
    for (int i = 0; i < NUM_CULORI; i++) {
        strcpy(steag[pas], culori[i]);  // Alegem o culoare
        backtracking(pas + 1, steag);  // Continuăm la pasul următor
    }
}

int main() {
    // Vector pentru a construi un steag
    char steag[LUNGIME_STEAG][10];

    // Generăm combinațiile folosind backtracking
    backtracking(0, steag);

    // Afișăm primele 3 steaguri generate
    printf("Steaguri generate:\n");
    for (int i = 0; i < 3 && i < index_solutii; i++) {
        printf("Steag %d: %s - %s - %s\n", i + 1, solutii[i][0], solutii[i][1], solutii[i][2]);
    }

    return 0;
}
