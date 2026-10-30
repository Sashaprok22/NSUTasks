#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum ModelsEnum {
    LP32 = 0,
    ILP32 = 1,
    LLP64 = 2,
    LP64 = 3,
};

typedef struct Field_s {
    char type[16];
    int isPointer;
    int sizes[4];
} Field;

int getPower(int n) {
    int prev = 2;
    int i = 0;
    while (prev <= n) {
        prev *= 2;
        ++i;
    }

    return i;
}

void parseSizes(Field *field) {
    if (field->isPointer) {
        field->sizes[LP32] = 4;
        field->sizes[ILP32] = 4;
        field->sizes[LLP64] = 8;
        field->sizes[LP64] = 8;
        return; 
    }

    if (!strcmp(field->type, "char")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 1;

    } else if (!strcmp(field->type, "short")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 2;

    } else if (!strcmp(field->type, "int")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 4;
        field->sizes[LP32] = 2;
        
    } else if (!strcmp(field->type, "long")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 4;
        field->sizes[LP64] = 8;
        
    } else if (!strcmp(field->type, "float")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 4;
        
    } else if (!strcmp(field->type, "int64_t") || !strcmp(field->type, "double")) {
        for(int i = 0; i < 4; ++i) field->sizes[i] = 8;
    }
}

int parseField(Field *field) {
    char symbol = getchar();

    while (isspace(symbol) && symbol != EOF) symbol = getchar();
    if (symbol == '\n' || symbol == '{') return 0;
    if (symbol == EOF || symbol == '}') return -1;

    int typeLen = 0;
    while (isalpha(symbol) || isdigit(symbol) || symbol == '_') {
        field->type[typeLen++] = symbol;
        symbol = getchar();
    }
    field->type[typeLen] = '\0';

    field->isPointer = 0;
    while (symbol != '\n' && symbol != EOF) {
        if (symbol == '*') field->isPointer = 1;
        symbol = getchar();
    }

    parseSizes(field);

    return 1;
}

int getMinSize(int c1, int c2, int c4, int c8) {
    int total = c1 + (c2 * 2) + (c4 * 4) + (c8 * 8);
    
    int aligment = 1;
    if (c8 > 0) aligment = 8;
    else if (c4 > 0) aligment = 4;
    else if (c2 > 0) aligment = 2;

    return ((total + aligment - 1) / aligment) * aligment;
}

int packMax(int count, int places) {
    int result = (count + places) / 2;
    if (result > count) result = count;

    return result;
}

int getMaxSize(int c1, int c2, int c4, int c8) {
    if (c8 > 0) {
        int blocks2 = c2 + packMax(c1, c2 + c4 + c8 + 1);
        int blocks4 = c4 + packMax(blocks2, c4 + c8 + 1);
        int blocks8 = c8 + packMax(blocks4, c8 + 1);
        return blocks8 * 8;
    }

    if (c4 > 0) {
        int blocks2 = c2 + packMax(c1, c2 + c4 + 1);
        int blocks4 = c4 + packMax(blocks2, c4 + 1);

        return blocks4 * 4;
    }

    if (c2 > 0) {
        int blocks2 = c2 + packMax(c1, c2 + 1);
        return blocks2 * 2;
    }

    return c1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char c = getchar();
    while (c != '\n' && c != EOF) c = getchar();

    int counts[4][4] = {0};

    while (1) {
        Field field;
        int result = parseField(&field);
        if (result == -1) break;
        if (!result) {
            c = getchar();
            while (c != '\n' && c != EOF) c = getchar();
            continue;
        }

        for (int model = 0; model < 4; ++model) {
            ++counts[model][getPower(field.sizes[model])];
        }
    }

    for (int model = 0; model < 4; ++model) {
        int c1 = counts[model][0];
        int c2 = counts[model][1];
        int c4 = counts[model][2];
        int c8 = counts[model][3];

        int minSize = getMinSize(c1, c2, c4, c8);
        int maxSize = getMaxSize(c1, c2, c4, c8);

        printf("%d %d\n", minSize, maxSize);
    }

    return 0;
}