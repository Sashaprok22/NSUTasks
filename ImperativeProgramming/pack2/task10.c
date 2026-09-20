#include <stdio.h>

int get_word_len(char *word) {
    int len = 0;
    while (word[len] != '\0') ++len;

    return len;
}

void reversString(char *str) {
    int len = get_word_len(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void convertToNotation(int numRe, int numIm, char *result, int maxLen) {
    if (numRe == 0 && numIm == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    int index = -1;
    while ((numRe != 0 || numIm != 0) && index < maxLen - 1) {
        int digit = (numRe + numIm) % 2 == 0 ? 0 : 1;
        result[++index] = '0' + digit;

        int oldRe = numRe;
        numRe = (numIm - numRe + digit) / 2;
        numIm = (-oldRe - numIm + digit) / 2;
    }
    result[++index] = '\0';
    reversString(result);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int real, imaginary, maxLen;
    scanf("%d %d %d", &maxLen, &real, &imaginary);

    char result[maxLen + 1];
    convertToNotation(real, imaginary, result, maxLen);
    printf("%s", result);
    return 0;
}