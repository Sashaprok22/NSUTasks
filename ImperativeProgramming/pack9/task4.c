#include <stdio.h>
#include <stdlib.h>

int compareInts(const void *a, const void *b) {
    int arg1 = *(const long long *)a;
    int arg2 = *(const long long *)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    long long arr[n];
    for (int i = 0; i < n; ++i) scanf("%lld", &arr[i]);
    qsort(arr, n, sizeof(long long), compareInts);

    long long result = 0;
    for (int i = 0; i < n; ++i) result += arr[i] * (n - i - 1);

    printf("%lld", result);

    return 0;
}