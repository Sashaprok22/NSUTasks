#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat(char *preff, char *suff) {
    int startI = strlen(preff);
    int suffLen = strlen(suff);
    for (int i = 0; i < suffLen; ++i) {
        preff[startI + i] = suff[i];
    }
    preff[startI + suffLen] = '\0';
    return preff;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int wordsCount;
    scanf("%d", &wordsCount);

    char *result = NULL;
    for (int i = 0; i < wordsCount; ++i) {
        char word[101];
        scanf("%s", word);
        int oldLen = result == NULL ? 0 : strlen(result);
        int newSize = sizeof(char) * (strlen(word) + oldLen + 1);
        result = realloc(result, newSize);
        result = concat(result, word);
    }
    printf("%s", result);
}