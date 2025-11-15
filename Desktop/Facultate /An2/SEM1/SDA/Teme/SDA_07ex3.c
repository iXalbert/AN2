#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int Dublura(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);  
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            return 1; 
        }
    }
    return 0; 
}

int main() {
    int n;

    printf("Valoare lui n ");
    scanf("%d", &n);

    int a[n];  

    printf("Vectorul este  ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }


    if (Dublura(a, n)) {
        printf("Am gasit o valoare ce se repeta\n");
    } else {
        printf("Nu am gasit valoare ce sa se repete.\n");
    }
    return 0;
}
