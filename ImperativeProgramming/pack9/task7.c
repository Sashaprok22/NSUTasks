#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

void heapify(int32_t *arr, int n, int i)
{
    int largest = i;   
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int32_t temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int32_t *arr, int32_t n) {
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        int32_t temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int32_t n;
    fread(&n, sizeof(int32_t), 1, stdin);

    int32_t arr[n];
    fread(arr, sizeof(int32_t), n, stdin);
    heapSort(arr, n);
    fwrite(arr, sizeof(int32_t), n, stdout);

    return 0;
}