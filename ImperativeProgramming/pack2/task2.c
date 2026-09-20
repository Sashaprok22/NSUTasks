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

int hexToDec(char *hex) {
    int hexLen = get_word_len(hex);
    int result = 0;

    for (int pos = 0; pos < hexLen; ++pos) {
        char symbol = hex[pos];
        int currentDigit = hex[pos] - '0';
        if (symbol >= 'a') currentDigit = hex[pos] - 'a' + 10;
        else if (symbol >= 'A') currentDigit = hex[pos] - 'A' + 10;
        if (currentDigit > 15) return -1;

        result = result + currentDigit * pow(16, hexLen - pos - 1);
    }

    return result;
}

void parseHex(int *result, char *hexCode) {
    if (get_word_len(hexCode) != 6) {
        result[0] = -1;
        result[1] = -1;
        result[2] = -1;
        return;
    }

    for (int i = 0; i < 3; ++i) {
        char currentHex[3] = { hexCode[i * 2], hexCode[i * 2 + 1], '\0' };
        int converResult = hexToDec(currentHex);
        if (converResult < 0) {
            result[0] = -1;
            result[1] = -1;
            result[2] = -1;
            return;
        } else {
            result[i] = converResult;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char hexCode[7];
    scanf("%6s", hexCode);

    int rgb[3];
    parseHex(rgb, hexCode);

    printf("%d %d %d", rgb[0], rgb[1], rgb[2]);
}