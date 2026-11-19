#include <stdio.h>
#include <stdlib.h>

int compareInts(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), compareInts);

    int uniqueNums[n];
    int uniqueNumsCount = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;
        uniqueNums[uniqueNumsCount++] = arr[i];
    }

    printf("%d\n", uniqueNumsCount);
    for (int i = 0; i < uniqueNumsCount; ++i) printf("%d\n", uniqueNums[i]);

    return 0;
}