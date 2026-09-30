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

    int count;
    scanf("%d", &count);

    int nums[count];

    int uniqueNumsCount = 0;
    int uniqueNums[count];
    int uniqueNumsCounts[count];

    for (int i = 0; i < count; ++i) {
        int n;
        scanf("%d", &n);
        nums[i] = n;

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
            insert(uniqueNumsCounts, uniqueNumsCount, newI, 1);
            
        } else {
            ++uniqueNumsCounts[uniqueFound];
        }
    }

    for (int i = 0; i < uniqueNumsCount; ++i) {
        printf("%d: %d\n", uniqueNums[i], uniqueNumsCounts[i]);
    }

    return 0;
}