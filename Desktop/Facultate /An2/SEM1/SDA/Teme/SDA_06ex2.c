#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int mijla3(int arr[], int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid]) {
        int temp = arr[left];
        arr[left] = arr[mid];
        arr[mid] = temp;
    }
    if (arr[left] > arr[right]) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
    if (arr[mid] > arr[right]) {
        int temp = arr[mid];
        arr[mid] = arr[right];
        arr[right] = temp;
    }
    return arr[mid];
}

void partitiela3(int arr[], int left, int right, int *lt, int *gt) {
    int pivot = mijla3(arr, left, right);
    int i = left;
    *lt = left;
    *gt = right;
    while (i <= *gt) {
        if (arr[i] < pivot) {
            int temp = arr[i];
            arr[i] = arr[*lt];
            arr[*lt] = temp;
            (*lt)++;
            i++;
        } else if (arr[i] > pivot) {
            int temp = arr[i];
            arr[i] = arr[*gt];
            arr[*gt] = temp;
            (*gt)--;
        } else {
            i++;
        }
    }
}

void quickOpti(int arr[], int left, int right) {
    if (right - left + 1 <= 20) {
        insertionSort(arr, left, right);
        return;
    }
    
    int lt, gt;
    partitiela3(arr, left, right, &lt, &gt);
    quickOpti(arr, left, lt - 1);
    quickOpti(arr, gt + 1, right);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
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

    quickOpti(a, 0, n - 1);
    printf("Quick:\n");
    printArray(a, n);
    return 0;
}
