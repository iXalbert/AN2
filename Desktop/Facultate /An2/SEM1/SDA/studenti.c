#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME];
    float grade;
} Student;

int read_students(const char* filename, Student students[], int* n) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Eroare la deschiderea fișierului!\n");
        return 0;
    }

    *n = 0;
    while (fgets(students[*n].name, MAX_NAME, file) != NULL) {
        students[*n].name[strcspn(students[*n].name, "\n")] = '\0';
        fscanf(file, "%f\n", &students[*n].grade);
        (*n)++;
    }

    fclose(file);
    return 1;
}

void print_students(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\t%.2f\n", students[i].name, students[i].grade);
    }
}

void sort_by_name(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void partition_by_grade(Student students[], int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        while (i < n && students[i].grade >= 5.0) i++;
        while (j >= 0 && students[j].grade < 5.0) j--;
        if (i < j) {
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
}

void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Student students[], int low, int high) {
    float pivot = students[high].grade;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (students[j].grade < pivot) {
            i++;
            swap(&students[i], &students[j]);
        }
    }
    swap(&students[i + 1], &students[high]);
    return i + 1;
}

void quicksort(Student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quicksort(students, low, pi - 1);
        quicksort(students, pi + 1, high);
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int n;

    if (!read_students("Studenti2.txt", students, &n)) {
        return 1;
    }

    printf("Studenții citiți din fișier:\n");
    print_students(students, n);

    sort_by_name(students, n);
    printf("\nStudenții sortati alfabetic după nume:\n");
    print_students(students, n);

    partition_by_grade(students, n);
    printf("\nStudenții cu medii >=5 pe primele poziții:\n");
    print_students(students, n);
    
    quicksort(students, 0, n - 1);
    printf("\nStudenții sortati crescător după medie:\n");
    print_students(students, n);

    return 0;
}
