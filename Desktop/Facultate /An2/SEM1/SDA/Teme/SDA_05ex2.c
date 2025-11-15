#include <stdio.h>

void insertion_sort(int a[], int n) {
    int i, j;
    int tmp;
    
    for (i = n - 2; i >= 0; i--) { 
        tmp = a[i];  
        
        for (j = i; (j < n - 1) && (tmp < a[j + 1]); j++) {
            a[j] = a[j + 1]; 
        }
        
        a[j] = tmp; 
    }
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
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

    printf("Before ");
    print_array(a, n);
    
    insertion_sort(a, n);
    
    printf("After ");
    print_array(a, n);
    
    return 0;
}
