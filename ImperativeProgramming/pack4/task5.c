#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char symbol = getchar();
    while (symbol != EOF) {
        if (isalpha(symbol)) {
            int upperCount = 0, wordLen = 0;
            char *word = malloc(sizeof(char) * 2);
            word[0] = '\0';
            while (symbol != EOF && isalpha(symbol)) {
                if (isupper(symbol)) ++upperCount;
                word = realloc(word, sizeof(char) * (wordLen + 2));
                word[wordLen] = symbol;
                word[++wordLen] = '\0';
                symbol = getchar();

            }

            printf("%d/%d %s\n", upperCount, wordLen, word);
            free(word);
        }
        symbol = getchar();
    }
    
}