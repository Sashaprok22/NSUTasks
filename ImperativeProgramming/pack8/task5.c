#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int start, int arrLen, int n) {
    if (start >= arrLen) return start;

    int pivotI = (start + arrLen) / 2;
    if (arr[pivotI] < n) return binarySearch(arr, pivotI + 1, arrLen, n);
    else return binarySearch(arr, start, pivotI, n);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size;
    scanf("%d", &size);

    int arr[size];
    for (int i = 0; i < size; ++i) scanf("%d", &arr[i]);

    int queriesCount;
    scanf("%d", &queriesCount);

    for (int i = 0; i < queriesCount; ++i) {
        int x;
        scanf("%d", &x);

        int pos = binarySearch(arr, 0, size, x);
        int bestI;

        if (pos == 0) bestI = 0;
        else if (pos == size) bestI = size - 1;
        else {
            int leftDist = x - arr[pos - 1];
            int rightDist = arr[pos] - x;

            if (leftDist < rightDist) bestI = pos - 1;
            else bestI = pos;
        }

        printf("%d %d\n", bestI, abs(arr[bestI] - x));
    }

    return 0;
}