#include <stdio.h>
#include <string.h>

void getPrefixValues(char *word, int *result) {
    int len = strlen(word);

    result[0] = 0;
    for (int i = 1; i < len; ++i) {
        int j = result[i - 1];
        while (j > 0 && word[j] != word[i]) j = result[j - 1];
        if (word[i] == word[j]) ++j;
        result[i] = j;  
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    char subStr[] = "GGGGCC";
    int len = strlen(subStr);
    int prefixValues[len];
    getPrefixValues(subStr, prefixValues);

    char symbol;
    int j = 0;
    int counter = 0;
    int lastMatchSymbols = 0;
    while (counter <= 30) {
        symbol = getchar();
        if (symbol == EOF) break;
        if (lastMatchSymbols <= len) ++lastMatchSymbols;

        while (j > 0 && symbol != subStr[j]) j = prefixValues[j - 1];
        if (symbol == subStr[j]) ++j;

        if (j == len) {
            if (lastMatchSymbols >= len) {
                ++counter;
                lastMatchSymbols = 0;
            }
            j = prefixValues[j - 1];
        }
    }

    if (counter > 30) printf("Pathogenic"); 
    else printf("Non-pathogenic");

    return 0;
}