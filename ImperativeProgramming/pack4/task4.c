#include <stdio.h>
#include <ctype.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int i = 0;
    while (iStr[i] != '\0' && iStr[i] != '\n') {
        char symbol = iStr[i];
        if (isupper(symbol)) ++(*oUpperCnt);
        else if (islower(symbol)) ++(*oLowerCnt);
        else if (isdigit(symbol)) ++(*oDigitsCnt);
        ++i;
    }

    return i;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[102];
    int i = 0;
    while (fgets(str, sizeof(str), stdin) != NULL) {
        int lower = 0, upper = 0, digits = 0;
        int charsCount = calcLetters(str, &lower, &upper, &digits);
        int letters = lower + upper;
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", ++i, charsCount, letters, lower, upper, digits);
    }
    return 0;
}