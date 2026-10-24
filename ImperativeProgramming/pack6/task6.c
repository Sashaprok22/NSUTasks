#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

typedef struct Field_s {
    char *name;
    uint8_t type;

    double doubleValue;
    char *stringValue;
    uint8_t boolValue;
    uint32_t int32Value;
    uint64_t int64Value;
} Field;

int readField(Field *field) {
    if (fread(&field->type, sizeof(uint8_t), 1, stdin) <= 0) return 0;
    if (field->type == 0) return 0;
    
    int nameLen = 0;
    char *fieldName = NULL;
    while (1) {
        char symbol = (char)fgetc(stdin);
        if (symbol == 0) break;

        ++nameLen;
        fieldName = (char *)realloc(fieldName, nameLen + 1);
        fieldName[nameLen - 1] = symbol;
    }
    fieldName[nameLen] = '\0';
    field->name = fieldName;

    switch (field->type) {
        case 1:
            fread(&field->doubleValue, sizeof(double), 1, stdin);
            break;

        case 2:
            uint32_t strLen;
            fread(&strLen, sizeof(strLen), 1, stdin);
            field->stringValue = (char*)malloc(sizeof(char) * strLen);
            fread(field->stringValue, sizeof(char), strLen, stdin);
            break;

        case 8:
            field->boolValue = (uint8_t)fgetc(stdin);
            break;

        case 16:
            fread(&field->int32Value, sizeof(uint32_t), 1, stdin);
            break;

        case 18:
            fread(&field->int64Value, sizeof(uint64_t), 1, stdin);
            break;
        
        default:
            break;
    }

    return 1;
} 

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "w", stdout);

    uint32_t totalBytes;
    int isFirstField = 1;
    fread(&totalBytes, sizeof(totalBytes), 1, stdin);

    printf("{\n");
    while (!feof(stdin)) {
        Field field;
        if (!readField(&field)) break;

        if (!isFirstField) printf(",\n");
        isFirstField = 0;

        printf("    \"%s\": ", field.name);

        switch (field.type) {
            case 1:
                printf("%0.15g", field.doubleValue);
                break;

            case 2:
                printf("\"%s\"", field.stringValue);
                break;

            case 8:
                if (field.boolValue) printf("true");
                else printf("false");
                break;

            case 10:
                printf("null");
                break;

            case 16:
                printf("%d", field.int32Value);
                break;

            case 18:
                printf("%lld", field.int64Value);
                break;
            
            default:
                break;
        }
    }
    printf("\n}");

    return 0;
}