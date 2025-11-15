#include <stdio.h>

int factorial(int n) {
    long long rezultat = 1; 
    
    for (int i = 1; i <= n; i++) {
        rezultat *= i;
    }
    
    return rezultat;
}

int main() {
    int n;
    
    printf("Citim pe n = ");
    scanf("%d", &n);

    if (n < 0) {
        printf("A fost introdus un numar negativ\n");
    } else {
        printf("Rezultatul factorialuiui %d este %d \n", n, factorial(n));
    }

    return 0;
}
