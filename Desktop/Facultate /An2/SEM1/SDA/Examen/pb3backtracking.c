#include <stdio.h>

#define N 3  // Numărul de linii
#define M 3  // Numărul de coloane

// Culorile posibile (0 - prima culoare, 1 - a doua, etc.)
#define COLORS 4

int map[N][M];  // Matricea care reprezintă suprafața colorată

// Funcție pentru determinarea unei culori valide pentru o celulă
int get_valid_color(int i, int j) {
    int color_used[COLORS] = {0};  // Marcare a culorilor folosite de vecini

    // Verifică vecinii pe diagonală pentru a evita conflictele de culoare
    if (i > 0 && j > 0) {
        color_used[map[i - 1][j - 1]] = 1;
    }
    if (i > 0 && j < M - 1) {
        color_used[map[i - 1][j + 1]] = 1;
    }
    if (i < N - 1 && j > 0) {
        color_used[map[i + 1][j - 1]] = 1;
    }
    if (i < N - 1 && j < M - 1) {
        color_used[map[i + 1][j + 1]] = 1;
    }

    // Găsește o culoare disponibilă
    for (int c = 0; c < COLORS; c++) {
        if (!color_used[c]) {
            return c;
        }
    }
    return 0;  // Fallback, nu ar trebui să fie necesar
}

// Funcție pentru colorarea hărții
void color_map() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map[i][j] = get_valid_color(i, j);
        }
    }
}

// Funcție pentru afișarea hărții
void display_map() {
    printf("Suprafața colorată:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    color_map();
    display_map();
    return 0;
}
