#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Element_s {
    uint32_t key;
    uint32_t value;
} Element;

void sortArrayByKeys(Element *arr, uint32_t size) {
    Element *output = malloc(sizeof(Element) * size);

    for (uint32_t shift = 0; shift < 32; shift += 8) {
        uint32_t count[0xFF + 1] = {0};

        for (uint32_t i = 0; i < size; ++i) {
            uint32_t digit = (arr[i].key >> shift) & 0xFF;
            ++count[digit];
        }

        uint32_t position = 0;

        for (uint32_t i = 0; i <= 0xFF; ++i) {
            uint32_t temp = count[i];
            count[i] = position;
            position += temp;
        }

        for (uint32_t i = 0; i < size; ++i) {
            uint32_t digit = (arr[i].key >> shift) & 0xFF;
            output[count[digit]++] = arr[i];
        }

        for (uint32_t i = 0; i < size; ++i) arr[i] = output[i];
    }

    free(output);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    uint32_t n;
    fread(&n, sizeof(uint32_t), 1, stdin);

    Element *arr = malloc(sizeof(Element) * n);
    fread(arr, sizeof(Element), n, stdin);
    sortArrayByKeys(arr, n);
    fwrite(arr, sizeof(Element), n, stdout);

    return 0;
}