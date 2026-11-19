#include <stdio.h>
#include <inttypes.h>

void merge(int32_t *arr, int start, int mid, int end) {
    int32_t result[end - start];

    int lastI = 0;
    int i = start, j = mid;

    while (i < mid && j < end) {
        if (arr[i] <= arr[j]) result[lastI++] = arr[i++];
        else result[lastI++] = arr[j++];
    }

    while (i < mid) result[lastI++] = arr[i++];
    while (j < end) result[lastI++] = arr[j++];

    for (int i = start; i < end; ++i) arr[i] = result[i - start];
}

void mergeSort(int32_t *arr, int start, int n) {
    if ((n - start) <= 1) return;

    int mid = start + (n - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, n);
    merge(arr, start, mid, n);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int32_t n;
    fread(&n, sizeof(int32_t), 1, stdin);

    int32_t arr[n];
    for (int i = 0; i < n; ++i) fread(&arr[i], sizeof(int32_t), 1, stdin);
    mergeSort(arr, 0, n);

    for (int i = 0; i < n; ++i) fwrite(&arr[i], sizeof(int32_t), 1, stdout);

    return 0;
}