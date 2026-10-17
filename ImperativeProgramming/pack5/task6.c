#include <stdio.h>

#define LONG_NUM_LEN 3000

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

void intToNum(LongNum *num, int n) {
    clearNum(num);
    int len = 0;
    while (n > 0) {
        num->arr[len++] = n % 10;
        n /= 10;
    }
    num->len = len; 
}

void shiftRightNum(LongNum *num, int digits) {
    if (digits <= 0) return;

    for(int i = num->len - 1; i >= 0; --i) num->arr[i + digits] = num->arr[i];
    for (int i = 0; i < digits; ++i) num->arr[i] = 0;
    num->len += digits;
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

void multNum(LongNum *result, int mult) {
    int toNextDigit = 0;

    for (int i = 0; i < result->len; ++i) {
        int tempMult = result->arr[i] * mult + toNextDigit;

        result->arr[i] = tempMult % 10;
        toNextDigit = tempMult / 10;
    }

    while (toNextDigit > 0) {
        result->arr[result->len] = toNextDigit % 10;
        toNextDigit /= 10;
        ++result->len;
    }
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

void factorial(LongNum *result, int n) {
    clearNum(result);
    result->arr[0] = 1;

    for (int i = 2; i <= n; ++i) multNum(result, i);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    LongNum result;
    factorial(&result, n);

    printNum(result);
    return 0;
}