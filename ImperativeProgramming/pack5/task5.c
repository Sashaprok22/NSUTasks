#include <stdio.h>

#define LONG_NUM_LEN 500

typedef struct LongNum_s
{
    int len;
    int arr[LONG_NUM_LEN];
} LongNum;

void printNum(LongNum num) {
    for (int i = num.len - 1; i >= 0; --i) printf("%d", num.arr[i]);
}

void clearNum(LongNum *num) {
    num->len = 1;
    for (int i = 0; i < LONG_NUM_LEN; ++i) num->arr[i] = 0;
}

void copyNum(LongNum *to, LongNum from) {
    to->len = from.len;
    for (int i = 0; i < LONG_NUM_LEN; ++i) to->arr[i] = from.arr[i];
}

void sumNums(LongNum *result, LongNum b) {
    int toNextDigit = 0;
    int newLen = 0;
    for (int i = 0; i < LONG_NUM_LEN; ++i) {
        if (i >= result->len && i >= b.len && toNextDigit <= 0) break;
        int sum = result->arr[i] + b.arr[i] + toNextDigit;
        result->arr[i] = sum % 10;
        toNextDigit = sum / 10;
        ++newLen;
    }

    result->len = newLen;
}

void fib(LongNum *result, int n) {
    LongNum prevNum;
    clearNum(&prevNum);
    clearNum(result);
    result->arr[0] = 1;

    for (int i = 1; i < n; ++i) {
        LongNum oldNum;
        copyNum(&oldNum, *result);

        sumNums(result, prevNum);
        prevNum = oldNum;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    LongNum result;
    fib(&result, n);


    printNum(result);
    return 0;
}