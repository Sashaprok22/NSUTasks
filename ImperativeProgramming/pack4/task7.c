#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getEqualSymbols(char *word1, char *word2) {
    int minLen = min(strlen(word1), strlen(word2));

    for (int i = 0; i < minLen; ++i) {
        if (word1[i] != word2[i]) return i;
    }
    return minLen;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int wordsCount = 0;
    char *words[100];

    char word[101];
    while(scanf("%s ", word) > 0) {
        words[wordsCount] = malloc((strlen(word) + 1) * sizeof(char));
        strcpy(words[wordsCount], word);
        ++wordsCount;
    }

    for (int i = wordsCount - 1; i >= 0; --i) {
        char *word = words[i];
        int minSymbols = 1;

        for (int k = 0; k < wordsCount; ++k) {
            if (i == k) continue;
            minSymbols = max(minSymbols, getEqualSymbols(word, words[k]) + 1);
        }
        minSymbols = min(strlen(word), minSymbols);

        for (int k = 0; k < minSymbols; ++k) printf("%c", word[k]);
        if (i != 0) printf("#");
    }

    return 0;
}