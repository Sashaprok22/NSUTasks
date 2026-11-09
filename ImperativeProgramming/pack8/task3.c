#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printIndent(char indent, int indentLen) {
    for (int i = 0; i < indentLen; ++i) putchar(indent);
}

int checkErrors(char *word, char *compareTo) {
    int wordLen = strlen(word);
    int compLen = strlen(compareTo);

    if (abs(wordLen - compLen) > 1) return 0;

    int errors = 0;
    int wordI = 0, compI = 0;
    while (wordI < wordLen && compI < compLen) {
        if (word[wordI] == compareTo[compI]) {
            ++wordI;
            ++compI;
        } else {
            ++errors;
            if (wordLen > compLen) ++wordI;
            else if (wordLen < compLen) ++compI;
            else {
                ++wordI;
                ++compI;
            }
        }
    }

    return errors <= 1;
}

void checkWord(char *word, int indentLen, char indent) {
    int len = strlen(word);

    char cmds[3][5] = {
        "puk",
        "yaz",
        "hiya",
    };

    int currentCmd = -1;
    for (int cmdI = 0; cmdI < 3; ++cmdI) {
        if (checkErrors(word, cmds[cmdI])) {
            currentCmd = cmdI;
            break;
        }
    }

    if (currentCmd == -1) {
        printf("%s", word);
        return;
    }

    if (currentCmd == 0) {
        printf("#include <stdio.h>\n");

        printIndent(indent, indentLen);
        printf("#include <stdlib.h>\n");

        printIndent(indent, indentLen);
        printf("#include <memory.h>\n");

        printIndent(indent, indentLen);
        printf("#include <ctype.h>\n");

        printIndent(indent, indentLen);
        printf("#include <math.h>\n");

        printIndent(indent, indentLen);
        printf("#include <string.h>");
    } else if (currentCmd == 1) {
        printf("freopen(\"input.txt\", \"r\", stdin);\n");
        printIndent(indent, indentLen);
        printf("freopen(\"output.txt\", \"w\", stdout);");

    } else if (currentCmd == 2) {
        printf("__auto_type");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char symbol = EOF;
    char prevSymbol = symbol;

    char word[100000] = {'\0'};
    int wordLen = 0;

    int isComment = 0;
    int isStr = 0;
    int isBigComment = 0;

    int isIndentEnd = 0;
    int indentLen = 0;
    char indent = ' ';

    while (1) {
        prevSymbol = symbol;
        symbol = getchar();
        if (symbol == EOF) {
            if (wordLen > 0) {
                word[wordLen] = '\0';
                checkWord(word, indentLen, indent);
            }

            break;
        }

        if (symbol == '\n') {
            if (wordLen > 0) {
                word[wordLen] = '\0';
                checkWord(word, indentLen, indent);
            }
            
            putchar(symbol);

            isIndentEnd = 0;
            indentLen = 0;
            isComment = 0;
            isStr = 0;
            wordLen = 0;
            word[0] = '\0';
            continue;
        }

        if (isStr) {
            putchar(symbol);
            continue;
        }
        
        if (symbol == '/' && prevSymbol == '*' && isBigComment) {
            isBigComment = 0;
            putchar(symbol);
            continue;
        }

        if (isComment || isBigComment) {
            putchar(symbol);
            continue;
        }

        if (!isIndentEnd) {
            if (isspace(symbol)) {
                ++indentLen;
                indent = symbol;
            } else {
                isIndentEnd = 1;
            }
        }

        if (symbol == '/' && prevSymbol == '/') {
            checkWord(word, indentLen, indent);
            wordLen = 0;
            word[0] = '\0';
            isComment = 1;
            putchar(symbol);
            continue;
        }

        if (symbol == '*' && prevSymbol == '/') {
            checkWord(word, indentLen, indent);
            wordLen = 0;
            word[0] = '\0';
            isBigComment = 1;
            putchar(symbol);
            continue;
        }

        if (symbol == '"') {
            isStr = !isStr;
        }

        if (isalpha(symbol) || isdigit(symbol) || symbol == '_') {
            word[wordLen++] = symbol; 
        } else {
            word[wordLen] = '\0';
            checkWord(word, indentLen, indent);
            wordLen = 0;
            word[0] = '\0';
            putchar(symbol);
        }

    }

    return 0;
}