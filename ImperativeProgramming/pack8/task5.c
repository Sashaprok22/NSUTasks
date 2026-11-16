#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int start, int arrLen, int n) {
    int left = 0;
    int right = arrLen - 1;

    while (left < right) {
        int pivotI = left + (right - left) / 2;
        if (arr[pivotI] < n) left = pivotI + 1;
        else right = pivotI;
    }

    return left;
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