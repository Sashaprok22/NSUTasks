#include <stdio.h>

int binarySearch(int *arr, int start, int arrLen, int n) {
    if ((arrLen - start) <= 1) {
        if (arr[start] == n) return start;
        else return -1;
    }
    
    int pivotI = (start + arrLen) / 2;
    int pivot = arr[pivotI];
    if (pivot == n && (pivotI + 1 >= arrLen || arr[pivotI + 1] != n)) return pivotI;
    else if (n < pivot) return binarySearch(arr, start, pivotI, n);
    else return binarySearch(arr, pivotI + 1, arrLen, n);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size;
    scanf("%d", &size);

    int arr[size];
    for (int i = 0; i < size; ++i) {
        int n;
        scanf("%d", &n);
        arr[i] = n;
    }

    int queriesCount;
    scanf("%d", &queriesCount);

    int lastResult = 0;
    for (int i = 0; i < queriesCount; ++i) {
        int x;
        scanf("%d", &x);

        int n = x + lastResult;
        lastResult = binarySearch(arr, 0, size, n);
        printf("%d\n", lastResult);
    }

    return 0;
}