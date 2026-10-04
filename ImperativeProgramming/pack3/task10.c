#include <stdio.h>
#include <math.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int getBitsCount(int n) {
    int count = 0;
    while (n > 0)
    {
        count += n % 2;
        n /= 2;
    }
    return count;
}

int getFixedMaxNum(int n, int needBites) {
    int bites[32];
    int bitesCount = 0;
    while (n > 0) {
        bites[bitesCount++] = n % 2;
        n /= 2;
    }

    int counter = 0;
    int result = 0;
    for (int i = bitesCount - 1; i >= 0; --i) {
        int bit = bites[i];
        if (bit == 1) ++counter;

        result += bit * pow(2, i);
        if (counter >= needBites) break;
    }

    return result;
}

int getFixedMinNum(int n, int needBites) {
    int bites[32];
    int bitesCount = 0;
    while (n > 0) {
        bites[bitesCount++] = n % 2;
        n /= 2;
    }

    int counter = 0;
    int result = 0;
    for (int i = bitesCount - 1; i >= 0; --i) {
        int bit = bites[i];
        if (bit == 1) ++counter;

        if (counter >= needBites - 1 && bit == 0) {
            bit = 1;
            result += pow(2, i);
            break;
        }

        result += bit * pow(2, i);
    }

    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int existsFly, widthFly, stickLen;
    scanf("%d %d\n%d", &existsFly, &widthFly, &stickLen);


    // Физические ограничения палочки, чтобы мухи не наглели
    int heuristicMin = max((stickLen + widthFly) / (2 * widthFly), existsFly);
    int heuristicMax = stickLen / widthFly;

    int minFly = heuristicMin;
    if (getBitsCount(heuristicMin) > existsFly) minFly = getFixedMinNum(heuristicMin, existsFly);

    int maxFly = getFixedMaxNum(heuristicMax, existsFly);

    printf("%d %d", minFly, maxFly);

    return 0;
}