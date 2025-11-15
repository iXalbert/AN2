#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilizare: %s nume_fisier\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    int n;
    if (fscanf(fin, "%d", &n) != 1 || n < 1 || n > MAX_N) {
        fprintf(stderr, "Număr invalid de noduri (1 ≤ n ≤ %d)\n", MAX_N);
        fclose(fin);
        return 1;
    }

    int in_degree[MAX_N] = {0};
    int out_degree[MAX_N] = {0};

    int x, y, c;
    while (fscanf(fin, "%d %d %d", &x, &y, &c) == 3) {
        if (x < 0 || x >= n || y < 0 || y >= n) {
            fprintf(stderr, "Nod invalid în muchie: %d -> %d\n", x, y);
            fclose(fin);
            return 1;
        }
        out_degree[x]++;
        in_degree[y]++;
    }

    fclose(fin);
 
    int max_in = -1;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] > out_degree[i] && in_degree[i] > max_in) {
            max_in = in_degree[i];
        }
    }

    int gasit = 0;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] > out_degree[i] && in_degree[i] == max_in) {
            printf("Nod: %d, Grad intern: %d, Grad extern: %d\n", i, in_degree[i], out_degree[i]);
            gasit = 1;
        }
    }

    if (!gasit) {
        printf("Nu exista niciun nod cu grad intern mai mare decat gradul extern si cu grad intern maxim.\n");
    }

    return 0;
}