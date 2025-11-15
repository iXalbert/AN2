#include <stdio.h>
#include <string.h>

// Definim structura agenda
typedef struct {
    char nume[25];  // Numele persoanei
    char telefon[10]; // Telefonul persoanei
    int an;         // Anul nașterii
    int venit;      // Venitul persoanei
} agenda;

// Funcție pentru mutarea primelor două persoane cu venit sub 1000 pe ultimele poziții
void mutaVenitMic(agenda persoane[], int N) {
    int count = 0; // Numărăm câte persoane am mutat
    for (int i = 0; i < N && count < 2; i++) {
        if (persoane[i].venit < 1000) {
            // Mutăm persoana curentă la final
            agenda temp = persoane[i];
            for (int j = i; j < N - 1; j++) {
                persoane[j] = persoane[j + 1];
            }
            persoane[N - 1 - count] = temp;
            count++;
            i--; // Reanalizăm elementul de la poziția curentă
        }
    }
    // Complexitate: O(N^2) în cel mai rău caz, deoarece trebuie să mutăm elementele
}

// Funcție pentru sortarea în ordine alfabetică a persoanelor cu vârsta între 30 și 40 de ani
void sorteazaPersoane(agenda persoane[], int N, int anCurent) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            int varsta1 = anCurent - persoane[j].an;      // Calculăm vârsta primei persoane
            int varsta2 = anCurent - persoane[j + 1].an;  // Calculăm vârsta celei de-a doua persoane
            // Sortăm doar persoanele cu vârsta între 30 și 40 de ani
            if (varsta1 >= 30 && varsta1 <= 40 && varsta2 >= 30 && varsta2 <= 40) {
                if (strcmp(persoane[j].nume, persoane[j + 1].nume) > 0) {
                    agenda temp = persoane[j];
                    persoane[j] = persoane[j + 1];
                    persoane[j + 1] = temp;
                }
            }
        }
    }
    // Complexitate: O(N^2) în cel mai rău caz (Bubble Sort aplicat pe subsetul de persoane)
}

// Funcție pentru afișarea tabloului de agende
void afiseazaAgenda(agenda persoane[], int N) {
    for (int i = 0; i < N; i++) {
        printf("Nume: %s, Telefon: %s, An: %d, Venit: %d\n", persoane[i].nume, persoane[i].telefon, persoane[i].an, persoane[i].venit);
    }
    printf("\n");
}

int main() {
    // Exemplu de tablou cu 5 persoane
    agenda persoane[5] = {
        {"Maria", "0751234567", 1990, 1200},  // 34 ani
        {"Ion", "0722334455", 1985, 900},    // 39 ani
        {"Andrei", "0765432100", 1995, 700}, // 29 ani
        {"Elena", "0771239876", 1980, 2000}, // 44 ani
        {"Bogdan", "0730987654", 1987, 800}  // 37 ani
    };
    int anCurent = 2024;

    printf("Tabloul inițial:\n");
    afiseazaAgenda(persoane, 5);

    // Apelăm funcția pentru mutarea persoanelor cu venit mic
    mutaVenitMic(persoane, 5);
    printf("După mutarea primelor două persoane cu venit sub 1000:\n");
    afiseazaAgenda(persoane, 5);

    // Apelăm funcția pentru sortarea persoanelor cu vârsta între 30 și 40 de ani
    sorteazaPersoane(persoane, 5, anCurent);
    printf("După sortarea alfabetică a persoanelor cu vârsta între 30 și 40 de ani:\n");
    afiseazaAgenda(persoane, 5);

    return 0;
}
