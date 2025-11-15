#include <stdio.h>
#include <string.h>

typedef struct Record{
    int id;
    char name[50];
} Record;

void sortare_id(Record *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n ; j++) {
            if (v[j].id > v[j + 1].id) {
                Record temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}
/*
void sortare_name(Record *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n ; j++) {
            if (strcmp(v+i, v+j)) {
                Record temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}
*/

int main() {

    Record v[] = { {3, "Alice"}, {1, "Bob"}, {5, "Carol"}, {4, "Dave"}, {2, "Eve"} };
    int n = sizeof(v) / sizeof(v[0]);

    // Afișare înainte de sortare
    printf("Înainte de sortare:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s\n", v[i].id, v[i].name);
    }
    //sortare_name(v, n);
    sortare_id(v, n);

    printf("După sortare:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s\n", v[i].id, v[i].name);
    }

    return 0;
}
