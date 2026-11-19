#include <stdio.h>

#define THRESHOLD 64

int arr[2000000];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int *arr, int size) {
    if (size <= 1) return;

    for (int i = 1; i < size; ++i) {
        int pivot = arr[i];
        int j = i;

        while (j > 0 && arr[j - 1] > pivot) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = pivot;
    }
}

void heapify(int *arr, int n, int i)
{
    int largest = i;   
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr, int n) {
    if (n <= 1) return;

    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);

    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int median3(int a, int b, int c) {
    if (a > b) swap(&a, &b);
    if (b > c) swap(&b, &c);
    if (a > b) b = a;

    return b;
}

void quickSort(int *arr, int n, int depth, int maxDepth) {
    if (n <= 1) return;
    else if (n <= THRESHOLD) {
        insertionSort(arr, n);
        return;
    }
    if (depth > maxDepth) {
        heapSort(arr, n);
        return;
    }

    int pivot = median3(arr[0], arr[n / 2], arr[n - 1]);

    int leftI = 0;
    int rightI = n - 1;
    int i = 0;

    while (i <= rightI) {
        if (arr[i] < pivot) swap(&arr[leftI++], &arr[i++]);
        else if (arr[i] > pivot) swap(&arr[rightI--], &arr[i]);
        else ++i;
    }

    quickSort(arr, leftI, depth + 1, maxDepth);
    quickSort(arr + rightI + 1, n - 1 - rightI, depth + 1, maxDepth);
}

int intLog2(int n) {
    int result = 0;
    while (n > 1) {
        n >>= 1;
        ++result;
    }

    return result;
}
void adaptiveSort(int *arr, int size) {
    if (size <= 1) return;
    else if (size <= THRESHOLD) insertionSort(arr, size);
    else quickSort(arr, size, 0, intLog2(size) * 2);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
    adaptiveSort(arr, n);
    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);

    return 0;
}