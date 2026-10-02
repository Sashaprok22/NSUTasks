#include <stdio.h>

void insert(int *arr, int arrLen, int index, int value) {
    for (int i = arrLen - 2; i >= index; --i) {
        arr[i+1] = arr[i];
    }
    arr[index] = value;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int aLen;
    scanf("%d", &aLen);

    int arrA[aLen];
    for (int i = 0; i < aLen; ++i) {
        int n;
        scanf("%d", &n);
        arrA[i] = n;
    }

    int bLen;
    scanf("%d", &bLen);

    int arrB[bLen];
    for (int i = 0; i < bLen; ++i) {
        int n;
        scanf("%d", &n);
        arrB[i] = n;
    }

    int uniqueNums[aLen];
    int uniqueNumsCount = 0;

    for (int aI = 0; aI < aLen; ++aI) {
        int n = arrA[aI];
        int bFound = 0;
        for (int bI = 0; bI < bLen; ++bI) {
            if (n == arrB[bI]) bFound = 1;
        }

        
        if (bFound == 0) {
            int uniqueFound = -1;
            for (int k = 0; k < uniqueNumsCount; ++k) {
                if (uniqueNums[k] == n) {
                    uniqueFound = k;
                    break;
                }
            }

            if (uniqueFound == -1) {
                int newI = uniqueNumsCount;
                for (int k = 0; k < uniqueNumsCount; ++k) {
                    if (n < uniqueNums[k]) {
                        newI = k;
                        break;
                    }
                }

                ++uniqueNumsCount;
                insert(uniqueNums, uniqueNumsCount, newI, n);
            }
        };
    }

    printf("%d\n", uniqueNumsCount);
    for (int i = 0; i < uniqueNumsCount; ++i) printf("%d ", uniqueNums[i]);

    return 0;
}