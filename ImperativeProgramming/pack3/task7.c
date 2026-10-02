#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char symbol, lastSymbol = ' ';
    int wordLen = 0;

    do {
        symbol = getchar();

        if (symbol == ' ' || symbol == EOF) {
            if (lastSymbol != ' ' && wordLen > 1) {
                printf("%d%c", wordLen - 2, lastSymbol);
            }
            if (symbol != EOF) printf("%c", symbol);
            wordLen = 0;

        } else {
            if (wordLen == 0) printf("%c", symbol);
            ++wordLen;
        }

        lastSymbol = symbol;
    } while (symbol != EOF);

    return 0;
}