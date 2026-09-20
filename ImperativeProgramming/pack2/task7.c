#include <stdio.h>

int pow(int num, int power) {
    if (power == 0) return 1; 
    int result = num;
    for (int i = 1; i < power; ++i) result = result * num;
    return result;
}

int get_word_len(char *word) {
    int len = 0;
    while (word[len] != '\0') ++len;

    return len;
}

int convertFromNotation(char *num, int notation) {
    int numLen = get_word_len(num);
    int result = 0;

    for (int pos = 0; pos < numLen; ++pos) {
        char symbol = num[pos];
        int currentDigit = num[pos] - '0';
        if (symbol >= 'a') currentDigit = num[pos] - 'a' + 10;
        else if (symbol >= 'A') currentDigit = num[pos] - 'A' + 10;
        if (currentDigit > notation - 1) return -1;

        result = result + currentDigit * pow(notation, numLen - pos - 1);
    }

    return result;
}

char getDigitChar(int digit) {
    if (digit < 10) return '0' + digit;
    else return 'a' + digit - 10;
}

void reversString(char *str) {
    int len = get_word_len(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void convertToNotation(int num, int notation, char *result) {
    int index = -1;
    while (num > 0) {
        int digit = num % notation;
        result[++index] = getDigitChar(digit);
        num /= notation;
    }
    result[++index] = '\0';
    reversString(result);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int notationFrom, notationTo;
    char numFrom[65];
    scanf("%d %d %s", &notationFrom, &notationTo, numFrom);

    int decimal = convertFromNotation(numFrom, notationFrom);

    char result[65];
    convertToNotation(decimal, notationTo, result);

    printf("%s", result);

    return 0;
}