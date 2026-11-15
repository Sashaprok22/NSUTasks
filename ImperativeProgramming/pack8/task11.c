#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_DIGITS 1000000
#define BLOCK_MAX_SIZE 1000000000

typedef struct LongNum_s {
    int len;
    int *arr;
} LongNum;

void printLongNum(LongNum num) {
    printf("%d", num.arr[num.len - 1]);
    for (int i = num.len - 2; i >= 0; --i) printf("%09d", num.arr[i]);
}

LongNum readNum() {
    char *str = (char*)malloc(sizeof(char) * (MAX_INPUT_DIGITS + 1));
    scanf("%1000000s", str);

    int len = strlen(str);
    int blocks = (len + 8) / 9;

    LongNum num;
    num.arr = (int*)calloc(blocks, sizeof(int));
    num.len = 0;

    for (int to = len; to > 0; to -= 9) {
        int from = to - 9;
        if (from < 0) from = 0;

        int block = 0;
        for (int i = from; i < to; ++i) block = block * 10 + (str[i] - '0');

        num.arr[num.len++] = block;
    }
    while (num.len > 1 && num.arr[num.len - 1] == 0) --num.len;

    free(str);

    return num;
}

int compareLongNums(LongNum *a, LongNum *b) {
    if (a->len != b->len) return a->len < b->len ? -1 : 1;

    for (int i = a->len - 1; i >= 0; --i) {
        if (a->arr[i] < b->arr[i]) return -1;
        if (a->arr[i] > b->arr[i]) return 1;
    }

    return 0;
}

int comparePart(int *remainder, int *pivotNums, int numI, int bLen) {
    for (int i = bLen; i >= 0; --i) {
        int a = remainder[numI + i];
        int b = pivotNums[i];

        if (a < b) return -1;
        if (a > b) return 1;
    }

    return 0;
}

void multLongNum(LongNum *longNum, int n, int *result) {
    long long toNextDigit = 0;

    for (int i = 0; i < longNum->len; ++i) {
        long long tempMult = (long long)longNum->arr[i] * n + toNextDigit;

        result[i] = tempMult % BLOCK_MAX_SIZE;
        toNextDigit = tempMult / BLOCK_MAX_SIZE;
    }

    result[longNum->len] = toNextDigit;
}

void updateRemainder(int *remainder, int *product, int numI, int bLen) {
    int toNextDigit = 0;

    for (int i = 0; i <= bLen; ++i) {
        long long diff = (long long)remainder[numI + i] - product[i] - toNextDigit;

        if (diff < 0) {
            diff += BLOCK_MAX_SIZE;
            toNextDigit = 1;
        } else {
            toNextDigit = 0;
        }

        remainder[numI + i] = diff;
    }
}

LongNum divLongNums(LongNum *a, LongNum *b) {
    LongNum result = {0, NULL};

    int compare = compareLongNums(a, b);
    if (compare <= 0) {
        result.len = 1;
        result.arr = (int*)calloc(1, sizeof(int));
        if (compare == 0) result.arr[0] = 1;
        return result;
    }

    int resultLen = a->len - b->len + 1;
    result.len = resultLen;
    result.arr = (int*)calloc(resultLen, sizeof(int));

    int *pivotNums = (int*)calloc(b->len + 1, sizeof(int));
    int *remainder = (int*)calloc(a->len + 1, sizeof(int));
    memcpy(remainder, a->arr, a->len * sizeof(int));

    for (int i = resultLen - 1; i >= 0; --i) {
        int left = 0;
        int right = BLOCK_MAX_SIZE - 1;

        while (left < right) {
            int pivot = left + (right - left + 1) / 2;
            multLongNum(b, pivot, pivotNums);

            if (comparePart(remainder, pivotNums, i, b->len) >= 0) left = pivot;
            else right = pivot - 1;
        }

        result.arr[i] = left;

        multLongNum(b, left, pivotNums);
        updateRemainder(remainder, pivotNums, i, b->len);
    }

    while (result.len > 1 && result.arr[result.len - 1] == 0) --result.len;

    free(pivotNums);
    free(remainder);

    return result;
}

LongNum divLongNumsV2(LongNum *a, LongNum *b) {
    LongNum result = {0, NULL};

    int compare = compareLongNums(a, b);
    if (compare <= 0) {
        result.len = 1;
        result.arr = (int*)calloc(1, sizeof(int));
        if (compare == 0) result.arr[0] = 1;
        return result;
    }

    int resultLen = a->len - b->len + 1;
    result.len = resultLen;
    result.arr = (int*)calloc(resultLen, sizeof(int));

    int *pivotNums = (int*)calloc(b->len + 1, sizeof(int));
    int *remainder = (int*)calloc(a->len + 1, sizeof(int));

    LongNum normB = { b->len, (int*)calloc(b->len, sizeof(int))};
    long long norm = (long long)BLOCK_MAX_SIZE / ((long long)b->arr[b->len - 1] + 1);

    long long toNextNum = 0;
    for (int i = 0; i < a->len; ++i) {
        long long tempMult = (long long)a->arr[i] * norm + toNextNum;

        remainder[i] = tempMult % BLOCK_MAX_SIZE;
        toNextNum = tempMult / BLOCK_MAX_SIZE;
    }
    remainder[a->len] = toNextNum;
    toNextNum = 0;

    for (int i = 0; i < b->len; ++i) {
        long long tempMult = (long long)b->arr[i] * norm + toNextNum;

        normB.arr[i] = tempMult % BLOCK_MAX_SIZE;
        toNextNum = tempMult / BLOCK_MAX_SIZE;
    }

    for (int i = result.len - 1; i >= 0; --i) {

        long long top = (long long)remainder[i + b->len] * BLOCK_MAX_SIZE + remainder[i + b->len - 1];
        long long digit = top / normB.arr[b->len - 1];

        if (digit >= BLOCK_MAX_SIZE) digit = BLOCK_MAX_SIZE - 1;

        multLongNum(&normB, digit, pivotNums);

        while (comparePart(remainder, pivotNums, i, b->len) < 0) {
            --digit;
            multLongNum(&normB, digit, pivotNums);
        }

        result.arr[i] = digit;
        updateRemainder(remainder, pivotNums, i, b->len);
    }

    while (result.len > 1 && result.arr[result.len - 1] == 0) --result.len;

    free(normB.arr);
    free(pivotNums);
    free(remainder);

    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    LongNum a = readNum();
    LongNum b = readNum();
    LongNum result = divLongNumsV2(&a, &b);
    printLongNum(result);

    return 0;
}
