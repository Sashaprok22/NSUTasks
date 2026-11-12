#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charcnt(char *str, char symbol) {
    int i = 0;
    int counter = 0;
    while (str[i] != '\0') {
        if (str[i] == symbol) ++counter;
        ++i;
    }
    return counter;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    char *strs[100000];
    int nextFreeID = 0;

    for (int i = 0; i < n; ++i) {
        int queryType, k;
        scanf("%d %d", &queryType, &k);

        switch (queryType) {
            case 0:
                char *str = (char*)malloc(sizeof(char) * (k + 1));
                scanf("%s", str);
                strs[nextFreeID++] = str;
                break;

            case 1:
                if (nextFreeID <= k) break;
                free(strs[k]);
                strs[k] = NULL;
                break;

            case 2:
                if (nextFreeID <= k) break;
                printf("%s\n", strs[k]);
                break;

            case 3:
                if (nextFreeID <= k) break;
                char symbol;
                scanf(" %c", &symbol);
                printf("%d\n", charcnt(strs[k], symbol));
                break;
            
            default:
                break;
        }
    }

    for (int i = 0; i < nextFreeID; ++i) {
        if (strs[i] == NULL) continue;
        free(strs[i]);
    }

    return 0;
}