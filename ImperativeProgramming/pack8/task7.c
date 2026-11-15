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

void multLongNums(LongNum *result, LongNum a, LongNum b) {
    result->len = 0;
    result->arr[0] = 0;

    for (int numI = 0; numI < b.len; ++numI) {
        LongNum part;
        copyNum(&part, a);
        multNum(&part, b.arr[numI]);
        if (numI > 0) shiftRightNum(&part, numI);
        sumNums(result, part);
    }
}

LongNum readNum() {
    LongNum num;
    num.len = 0;
    num.arr[0] = 0;

    char symbol = getchar();
    while (symbol != '\n' && symbol != EOF) {
        if (symbol == '\r') {
            symbol = getchar();
            continue;
        }
        shiftRightNum(&num, 1);
        num.arr[0] = symbol - '0';
        symbol = getchar();
    }
    
    return num;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    LongNum a = readNum();
    LongNum b = readNum();

    LongNum result;
    multLongNums(&result, a, b);

    printNum(result);
    printf("\n");
    return 0;
}