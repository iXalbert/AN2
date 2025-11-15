#include <stdio.h>

int Binarysearch(int A[], int stanga, int dreapta) {
    if (stanga > dreapta) {
        return -1;  
    }

    int mijloc = stanga + (dreapta - stanga) / 2;

    if (A[mijloc] == mijloc) {
        return mijloc;
    }

    if (A[mijloc] < mijloc) {
        return Binarysearch(A, mijloc + 1, dreapta);
    }

    return Binarysearch(A, stanga, mijloc - 1);
}

int main() {
    int n;

    printf("Valoare lui n ");
    scanf("%d", &n);

    int A[n];  

    printf("Vectorul este  ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int rezultat = Binarysearch(A, 0, n - 1);

    if (rezultat != -1) {
        printf("Există un index i astfel încât A[%d] = %d\n", rezultat, A[rezultat]);
    } else {
        printf("Nu există niciun index i astfel încât A[i] = i\n");
    }

    return 0;
}
