#include <stdio.h>

int get_word_len(char *word) {
    int len = 0;
    while (word[len] != '\0') ++len;

    return len;
}

int compare_words(char *word, char *compareWith) {
    int wordLen = get_word_len(word);
    int compareWithLen = get_word_len(word);

    if (wordLen > compareWithLen) return 0;

    for (int i = 0; i < wordLen; ++i) {
        if (word[i] != compareWith[i]) return 0;
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char dayName[11];
    scanf("%s", &dayName);

    char weekDays[7][11] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    int searched = 0;
    int searchedWordI = -1;
    for (int i = 0; i < 7; ++i) {
        int checkResult = compare_words(dayName, weekDays[i]);
        if (checkResult == 1) searchedWordI = i;
        searched = searched + checkResult;
        if (searched >= 2) break;
    }

    switch (searched)
    {
    case 0:
        printf("Invalid");
        break;
    case 1:
        printf("%d", searchedWordI+1);
        break;
    case 2:
        printf("Ambiguous");
        break;
    
    default:
        printf("Why are you here?");
        break;
    }
    return 0;
}