#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    
    int count;
    scanf("%d", &count);

    int nums[count];
    for (int i = 0; i < count; ++i) {
        int n;
        scanf("%d", &n);
        nums[i] = n;
    }

    int totalMaxSum = nums[0];
    int bestL = 0;
    int bestR = 0;
    for (int l = 0; l < count; ++l) {
        int sum = nums[l];
        int biggestSum = sum;
        int bestCurrentR = l;
        for (int r = l + 1; r < count; ++r) {
            sum += nums[r];
            if (sum > biggestSum) {
                biggestSum = sum;
                bestCurrentR = r;
            }
        }

        if (biggestSum > totalMaxSum) {
            totalMaxSum = biggestSum;
            bestL = l;
            bestR = bestCurrentR;
        }
    }

    printf("%d %d %d", bestL, bestR, totalMaxSum);

    return 0;
}