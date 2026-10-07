#include <stdio.h>
#include <string.h>

void reverse(char *start, int len) {
    int left = 0;
    int right = len - 1;

    while (left < right) {
        char temp = start[left];
        start[left] = start[right];
        start[right] = temp;
    
        ++left;
        --right;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int wordsCount;
    scanf("%d", &wordsCount);

    for (int i = 0; i < wordsCount; ++i) {
        char word[100];
        scanf("%s", word);
        reverse(word, strlen(word));
        printf("%s\n", word);
    }
}