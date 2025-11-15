#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a < 0 ? -a : a;
}

long long lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    long long g = gcd(a, b);
    return (long long)(a / g) * b;
}

int sum_array(const int *arr, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += arr[i];
    return s;
}

int main(void) {
    int a = 84, b = 30;
    int g = gcd(a, b);
    long long l = lcm(a, b);
    int arr[] = {1, 2, 3, 4, 5};
    int s = sum_array(arr, sizeof(arr) / sizeof(arr[0]));

    printf("gcd(%d,%d)=%d\n", a, b, g);
    printf("lcm(%d,%d)=%lld\n", a, b, l);
    printf("sum=%d\n", s);
    return 0;
}
