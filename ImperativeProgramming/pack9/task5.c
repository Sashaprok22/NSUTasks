#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int compareInts(const void *a, const void *b) {
    int arg1 = *(const int32_t *)a;
    int arg2 = *(const int32_t *)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void quickSort(int32_t *arr, int n) {
    if (n <= 1) return;

    int pivot = arr[n / 2];

    int leftLen = 0;
    int32_t left[n];

    int rightLen = 0;
    int32_t right[n];

    int pivotDups = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < pivot) left[leftLen++] = arr[i];
        else if (arr[i] > pivot) right[rightLen++] = arr[i];
        else ++pivotDups;
    }

    quickSort(left, leftLen);
    quickSort(right, rightLen);

    for (int i = 0; i < leftLen; ++i) arr[i] = left[i];
    for (int i = 0; i < pivotDups; ++i) arr[leftLen + i] = pivot;
    for (int i = 0; i < rightLen; ++i) arr[leftLen + pivotDups + i] = right[i];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int32_t n;
    fread(&n, sizeof(int32_t), 1, stdin);

    int32_t arr[n];
    for (int i = 0; i < n; ++i) fread(&arr[i], sizeof(int32_t), 1, stdin);
    //qsort(arr, n, sizeof(int32_t), compareInts);
    quickSort(arr, n);

    for (int i = 0; i < n; ++i) fwrite(&arr[i], sizeof(int32_t), 1, stdout);

    return 0;
}