#include <stdio.h>
#include <string.h>

typedef struct {
    char nume[35];
    int varsta;   
    int premii;   
} student;

// a. Mutarea studenților premiați pe primele poziții
void mutaPremiati(student studenti[], int N) {
    int i = 0, j = N - 1;

    // Folosim două indicatoare (i și j) pentru a efectua mutarea în timp O(N)
    while (i < j) {
        // Avansăm i până găsim un student nepremiat
        while (i < N && studenti[i].premii == 1) {
            i++;
        }
        // Decrementăm j până găsim un student premiat
        while (j >= 0 && studenti[j].premii == 0) {
            j--;
        }
        // Dacă i este mai mic decât j, schimbăm elementele
        if (i < j) {
            student temp = studenti[i];
            studenti[i] = studenti[j];
            studenti[j] = temp;
        }
    }
    // Complexitate: O(N), deoarece parcurgem vectorul o singură dată
}

// b. Sortarea invers alfabetic a studenților premiați
void sorteazaPremiati(student studenti[], int N) {
    // Sortare prin metoda Bubble Sort aplicată doar studenților premiați
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            // Verificăm dacă ambii studenți sunt premiați
            if (studenti[j].premii == 1 && studenti[j + 1].premii == 1) {
                // Sortăm în ordine invers alfabetică
                if (strcmp(studenti[j].nume, studenti[j + 1].nume) < 0) {
                    student temp = studenti[j];
                    studenti[j] = studenti[j + 1];
                    studenti[j + 1] = temp;
                }
            }
        }
    }
    // Complexitate: O(N^2) în cel mai rău caz (datorită sortării Bubble Sort)
}

// Funcție pentru afișarea tabloului de studenți
void afiseazaStudenti(student studenti[], int N) {
    for (int i = 0; i < N; i++) {
        printf("Nume: %s, Varsta: %d, Premii: %d\n", studenti[i].nume, studenti[i].varsta, studenti[i].premii);
    }
    printf("\n");
}

int main() {
    // Exemplu de tablou cu 5 studenți
    student studenti[5] = {
        {"Andrei", 20, 0},
        {"Maria", 22, 1},
        {"Ion", 21, 1},
        {"Elena", 19, 0},
        {"Bogdan", 23, 1}
    };

    printf("Tabloul inițial:\n");
    afiseazaStudenti(studenti, 5);

    // Apelăm funcția pentru mutarea premianților
    mutaPremiati(studenti, 5);
    printf("După mutarea premianților:\n");
    afiseazaStudenti(studenti, 5);

    // Apelăm funcția pentru sortarea premianților
    sorteazaPremiati(studenti, 5);
    printf("După sortarea premianților în ordine invers alfabetică:\n");
    afiseazaStudenti(studenti, 5);

    return 0;
}
