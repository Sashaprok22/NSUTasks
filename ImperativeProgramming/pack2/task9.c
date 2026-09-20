#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int state = 0; // 0 - базовая обработка, 1 - после /, 2 - обычный комм, 3 - большой комм, 4 - строка, 5 - символ, 6 - большой комм обработка *
    int screening = 0;
    char symbol;

    while (1) {
        if (scanf("%c", &symbol) != 1) {
            if (state == 1) printf("/");
            break;
        }

        switch (state) {
        case 0:
            if (symbol == '/') state = 1;
            else {
                if (symbol == '"' && screening % 2 == 0) state = 4;
                else if (symbol == '\'' && screening % 2 == 0) state = 5;
                printf("%c", symbol);
            }
            break;

        case 1:
            if (symbol == '/') state = 2;
            else if (symbol == '*') state = 3;
            else {
                printf("/%c", symbol);
                state = 0;
            }
            break;

        case 2:
            if (symbol == '\n' || symbol == '\r') {
                printf("%c", symbol);
                state = 0;
            }
            break;

        case 3:
            if (symbol == '*') state = 6;
            else if (symbol == '\n' || symbol == '\r') printf("%c", symbol);
            break;

        case 6:
            if (symbol == '\n' || symbol == '\r') printf("%c", symbol);
            if (symbol == '/') state = 0;
            else if (symbol == '*') state = 6;
            else state = 3;
            break;

        case 4:
            if (symbol == '"' && screening % 2 == 0) state = 0;
            printf("%c", symbol);
            break;

        case 5:
            if (symbol == '\'' && screening % 2 == 0) state = 0;
            printf("%c", symbol);
            break;
        
        default:
            break;
        }

        if (symbol == '\\') ++screening;
        else screening = 0;
    }
    
    return 0;
}