#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int strToInt(char *str) {
    int strLen = strlen(str);
    int result = 0;
    for (int i = 0; i < strLen; ++i) {
        int digit = str[i] - '0';
        result = result * 10 + digit;
    }
    return result;
}

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds) {
    int strLen = strlen(iStr);

    int i = 0;
    int part = 0;

    char hoursStr[strLen];
    hoursStr[0] = '\0';

    char minsStr[strLen];
    minsStr[0] = '\0';

    char secsStr[strLen];
    secsStr[0] = '\0';

    while (i < strLen) {
        if (!isdigit(iStr[i]) && iStr[i] != ':') {
            if (iStr[i] == '\0' || iStr[i] == ' ' || iStr[i] == '\n') break;
            *oHours = -1;
            if (oMinutes != NULL) *oMinutes = -1;
            if (oSeconds != NULL) *oSeconds = -1;
            return 0;
        }

        if (isdigit(iStr[i])) {
            char *arrToAdd = hoursStr;
            if (part == 1) arrToAdd = minsStr;
            else if (part == 2) arrToAdd = secsStr;

            int partLen = strlen(arrToAdd);
            arrToAdd[partLen] = iStr[i];
            arrToAdd[partLen + 1] = '\0';

        } else ++part;
        ++i;
    }

    int hours = strToInt(hoursStr);
    int mins = strToInt(minsStr);
    int secs = strToInt(secsStr);

    if (hours < 0 || hours > 23 || mins < 0 || mins > 59 || secs < 0 || secs > 59) {
        *oHours = -1;
        if (oMinutes != NULL) *oMinutes = -1;
        if (oSeconds != NULL) *oSeconds = -1;
        return 0;
    }

    *oHours = hours;
    if (oMinutes != NULL) *oMinutes = mins;
    if (oSeconds != NULL) *oSeconds = secs;

    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[16];
    fgets(str, sizeof(str), stdin);

    int result, hours, mins, secs;

    result = readTime(str, &hours, &mins, &secs);
    printf("%d %d %d %d\n", result, hours, mins, secs);

    result = readTime(str, &hours, &mins, NULL);
    printf("%d %d %d\n", result, hours, mins);

    result = readTime(str, &hours, NULL, NULL);
    printf("%d %d", result, hours);
}