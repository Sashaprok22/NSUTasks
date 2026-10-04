#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int symbolsCount;
    scanf("%d", &symbolsCount);

    char symbols[symbolsCount];
    for (int i = 0; i < symbolsCount; ++i) scanf(" %c", &symbols[i]);

    int swapSymbol1 = -1;
    for (int i = symbolsCount - 2; i >= 0; --i) {
        if (symbols[i] < symbols[i + 1]) {
            swapSymbol1 = i;
            break;
        }
    }

    int swapSymbol2 = -1;
    for (int i = symbolsCount - 1; i > swapSymbol1; --i) {
        if (symbols[i] > symbols[swapSymbol1]) {
            swapSymbol2 = i;
            break;
        }
    }

    int temp = symbols[swapSymbol1];
    symbols[swapSymbol1] = symbols[swapSymbol2];
    symbols[swapSymbol2] = temp;

    int left = swapSymbol1 + 1;
    int right = symbolsCount - 1;

    while (left < right) {
        temp = symbols[left];
        symbols[left] = symbols[right];
        symbols[right] = temp;

        ++left;
        --right;
    }

    for (int i = 0; i < symbolsCount; ++i) printf("%c ", symbols[i]);
    return 0;
}