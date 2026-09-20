#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int numsCount;
    scanf("%d", &numsCount);

    int negativeNums = 0;
    int zeroCount = 0;
    int positiveCount = 0;
    for (int i = 0; i < numsCount; ++i) {
        int currentNum;
        scanf("%d", &currentNum);

        if (currentNum > 0) ++positiveCount;
        else if (currentNum < 0) ++negativeNums;
        else ++zeroCount;
    }

    double negativePart = (double)negativeNums / (double)numsCount;
    double zeroPart = (double)zeroCount / (double)numsCount;
    double positivePart = (double)positiveCount / (double)numsCount;

    printf("%0.5lf %0.5lf %0.5lf", negativePart, zeroPart, positivePart);
    return 0;
}