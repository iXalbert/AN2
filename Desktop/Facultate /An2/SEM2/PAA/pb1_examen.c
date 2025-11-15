#include <stdio.h>

#define MAX 100

int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        printf("Eroare la deschiderea fișierului.\n");
        return 1;
    }

    int n;
    int mat[MAX][MAX];

    // Citire dimensiune și matrice
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(f, "%d", &mat[i][j]);
    fclose(f);

    // Warshall – închidere tranzitivă
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][k] && mat[k][j])
                    mat[i][j] = 1;

    // Căutăm permisiunea care permite accesul la cele mai multe
    int maxPerm = -1, maxCount = -1;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++)
            if (mat[i][j]) count++;
        if (count > maxCount) {
            maxCount = count;
            maxPerm = i;
        }
    }

    printf("Permisiunea cu cel mai mare acces: %d\n", maxPerm);
    printf("Numar total de permisiuni accesibile: %d\n", maxCount);

    return 0;
}

/*
 1.a. Structura de date aleasă
Pentru această problemă, am ales să folosesc o matrice de adiacență pentru a reprezenta relațiile de dependență între permisiuni.

Definiție: O matrice de adiacență mat[i][j] de dimensiune n × n reține valoarea:

1 dacă permisiunea j depinde direct de permisiunea i
0 în caz contrar
Astfel, fiecare linie i din matrice corespunde unei permisiuni de pornire, iar fiecare coloană j indică dacă i poate permite (direct) accesul la j.

Motivația alegerii:

Matricea de adiacență permite acces rapid la relațiile dintre permisiuni (acces O(1)).
Este ușor de procesat prin algoritmul Warshall, care cere o astfel de reprezentare.
Dimensiunea maximă este rezonabilă (n=20 conform cerinței), deci spațiul nu este o problemă.
🔷 1.b. Alegerea structurii și justificarea sa
Am ales această structură deoarece:

Problema definește o relație binară de dependență între permisiuni, ceea ce corespunde perfect unui graf orientat.
Trebuie să identificăm accesibilitatea indirectă între permisiuni — deci avem nevoie de închiderea tranzitivă a relației.
Algoritmul clasic pentru închiderea tranzitivă într-un graf orientat este Warshall, care funcționează eficient pe matrice de adiacență.
Structura este statică și completă: știm numărul de noduri (permisiuni) de la început, deci nu avem nevoie de liste de adiacență sau structuri dinamice.
🔷 1.c. Exemplu de input și output
Exemplu de fișier de intrare:

4
0 1 0 0
0 0 1 0
0 0 0 1
0 0 0 0
Interpretare:

Permisiunea 0 → 1
Permisiunea 1 → 2
Permisiunea 2 → 3
Deci, dacă un angajat are permisiunea 0, el poate obține în lanț permisiunile 1, 2 și 3.

🔷 1.d. Cum determinăm angajatul cu acces maxim
Pas cu pas:

Aplicăm algoritmul lui Warshall:
Acest algoritm calculează toate permisiunile care pot fi obținute indirect pornind de la o permisiune inițială.
El parcurge toate perechile (i, j) și verifică dacă există un k intermediar pentru care i → k și k → j ⇒ înseamnă că i → j.
După aplicarea algoritmului, matricea ne spune toate perechile permisiune_i → permisiune_j valabile (direct sau indirect).
Numărăm pentru fiecare linie i câte valori de 1 are (câte permisiuni se pot accesa pornind de la i).
Păstrăm permisiunea i_max care are cel mai mare număr de accesuri.
Afișăm:
Indicele permisiunii
Numărul total de permisiuni accesibile prin ea
*/