#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10
#define MAX_WORDS 5

char solution[MAX_LENGTH + 1]; // Soluție curentă (caracteristică pentru backtracking)
int count = 0;                 // Contor pentru numărarea cuvintelor generate

// Funcție pentru afișarea unui cuvânt generat
void display_solution() {
    printf("%s\n", solution);
    count++;
}

// Funcție pentru verificarea condițiilor de oprire
int is_valid_solution(int a_count, int b_count, int c_count, int position) {
    return position == MAX_LENGTH && a_count == 0 && b_count == 0 && c_count == 0;
}

// Funcție pentru generarea cuvintelor
void generate_words(int position, int a_count, int b_count, int c_count) {
    // Condiția de oprire - când poziția ajunge la lungimea dorită și toate constrângerile sunt îndeplinite
    if (is_valid_solution(a_count, b_count, c_count, position)) {
        display_solution();
        return;
    }

    // Dacă deja am generat suficiente cuvinte, oprim recursivitatea
    if (count >= MAX_WORDS) {
        return;
    }

    // Backtracking: încercăm fiecare literă cu constrângeri rămase
    if (a_count > 0) {
        solution[position] = 'a';
        generate_words(position + 1, a_count - 1, b_count, c_count);
    }

    if (b_count > 0) {
        solution[position] = 'b';
        generate_words(position + 1, a_count, b_count - 1, c_count);
    }

    if (c_count > 0) {
        solution[position] = 'c';
        generate_words(position + 1, a_count, b_count, c_count - 1);
    }
}

int main() {
    // Inițializare pentru soluția curentă
    memset(solution, 0, sizeof(solution));

    printf("Primele %d cuvinte generate sunt:\n", MAX_WORDS);

    // Apel funcție pentru generare cuvinte, având exact 3 'a', 4 'b', și 3 'c'
    generate_words(0, 3, 4, 3);

    return 0;
}
