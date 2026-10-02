#include <stdio.h>

int getValue(int (*pairs)[2], int pairsCount, int x, int *result) {
    int resultSize = 0;
    for (int i = 0; i < pairsCount; ++i) {
        if (pairs[i][0] == x) result[resultSize++] = pairs[i][1];
    }
    return resultSize;
}

int getKey(int (*pairs)[2], int pairsCount, int y, int *result) {
    int resultSize = 0;
    for (int i = 0; i < pairsCount; ++i) {
        if (pairs[i][1] == y) result[resultSize++] = pairs[i][0];
    }
    return resultSize;
}

int isMultFunc(int (*pairs)[2], int pairsCount) {
    for (int i = 0; i < pairsCount; ++i) {
        int values[pairsCount];
        int valuesCount = getValue(pairs, pairsCount, pairs[i][0], values);
        if (valuesCount > 2) return 1;
        if (valuesCount == 1) continue;
        if (values[0] == pairs[i][0] || values[1] == pairs[i][0]) continue;
        return 1;
    }
    return 0;
}

int isAllFunc(int (*pairs)[2], int pairsCount, int setSize) {
    for (int i = 1; i <= setSize; ++i) {
        int temp[pairsCount];
        int valuesCount = getValue(pairs, pairsCount, i, temp);
        if (valuesCount <= 0) return 0;
    }
    return 1;
}

int isInjectFunc(int (*pairs)[2], int pairsCount) {
    for (int i = 0; i < pairsCount; ++i) {
        int values[pairsCount];
        int valuesCount = getKey(pairs, pairsCount, pairs[i][1], values);
        if (valuesCount > 2) return 0;
        if (valuesCount == 1) continue;
        if (values[0] == pairs[i][1] || values[1] == pairs[i][1]) continue;
        return 0;
    }
    return 1;
}

int isSurFunc(int (*pairs)[2], int pairsCount, int setSize) {
    for (int i = 1; i <= setSize; ++i) {
        int temp[pairsCount];
        int valuesCount = getKey(pairs, pairsCount, i, temp);
        if (valuesCount <= 0) return 0;
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int sizeP, pairsCount;
    scanf("%d %d", &sizeP, &pairsCount);

    int pairs[pairsCount][2];

    for (int pairI = 0; pairI < pairsCount; ++pairI) {
        int x, y;
        scanf("%d %d", &x, &y);
        pairs[pairI][0] = x;
        pairs[pairI][1] = y;
    }

    int multFunc = isMultFunc(pairs, pairsCount);
    printf("%d ", 1 - multFunc);
    if (multFunc == 1) return 0;

    int allFunc = isAllFunc(pairs, pairsCount, sizeP);
    int injFunc = isInjectFunc(pairs, pairsCount);
    int surFunc = isSurFunc(pairs, pairsCount, sizeP);

    if (allFunc == 1) printf("2 ");
    if (injFunc == 1) printf("3 ");
    if (surFunc == 1) printf("4 ");
    if (surFunc == 1 && injFunc == 1) printf("5 ");

    return 0;
}