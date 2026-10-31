#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tokens_s {
    int num; // количество слов в строке
    char **arr; // массив слов (каждый элемент –- строка, т.е. char*)
} Tokens;

int isSplitter(char symbol, const char *delims) {
    for (int i = 0; i < strlen(delims); ++i) {
        if (delims[i] == symbol) return 1;
    }
    return 0;
}

void tokensSplit(Tokens *tokens, const char *str, const char *delims) {
    if (tokens->arr == NULL) {
        int i = 0;
        int wordsCount = 0;
        while (str[i] != '\0') {
            if (isSplitter(str[i], delims)) {
                ++i;
                continue;
            }

            ++wordsCount;
            while (str[i] != '\0' && !isSplitter(str[i], delims)) ++i;
        }
        tokens->num = wordsCount;
        return;
    }

    int i = 0;
    for (int wordI = 0; wordI < tokens->num; ++wordI) {
        while (isSplitter(str[i], delims)) ++i;

        int wordLen = 0;
        while (str[i + wordLen] != '\0' && !isSplitter(str[i + wordLen], delims)) ++wordLen;

        tokens->arr[wordI] = malloc((wordLen + 1) * sizeof(char));
        for (int symbolI = 0; symbolI < wordLen; ++symbolI) {
            tokens->arr[wordI][symbolI] = str[i + symbolI];
        }
        tokens->arr[wordI][wordLen] = '\0';

        i += wordLen;
    }
}

void tokensFree(Tokens *tokens) {
    if (tokens->arr == NULL) return;

    for (int i = 0; i < tokens->num; ++i) {
        free(tokens->arr[i]);
    }
    free(tokens->arr);
    tokens->arr = NULL;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char inputStr[1000001];
    fgets(inputStr, sizeof(inputStr), stdin);
    inputStr[strcspn(inputStr, "\r\n")] = '\0';

    Tokens tokens;
    tokens.arr = NULL;
    char delims[] =  ".,;:";
    tokensSplit(&tokens, inputStr, delims);

    tokens.arr = malloc(tokens.num * sizeof(char*));
    tokensSplit(&tokens, inputStr, delims);

    printf("%d\n", tokens.num);
    for (int word = 0; word < tokens.num; ++word) {
        printf("%s\n", tokens.arr[word]);
    }

    tokensFree(&tokens);

    return 0;
}