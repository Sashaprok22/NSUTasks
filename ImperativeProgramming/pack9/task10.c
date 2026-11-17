#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_ELEMENTS 64

typedef struct Element_s {
    uint32_t key;
    uint32_t value;
} Element;

uint32_t xorwow(uint32_t state[5]) {
/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
    uint32_t s, t = state[3];
    t ^= t >> 2;
    t ^= t << 1;
    state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
    t ^= s;
    t ^= s << 4;
    state[0] = t;
    return t + (state[4] += 362437);
}

void sortArrayByKeys(Element **arr, int size) {
    for (int i = 1; i < size; ++i) {
        Element *temp = arr[i];
        uint32_t key = temp->key;
        int j = i;

        while (j > 0 && arr[j - 1]->key > key) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = temp;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Element *arr[MAX_ELEMENTS];
    for (int i = 0; i < MAX_ELEMENTS; ++i) arr[i] = (Element*)malloc(sizeof(Element));

    int testsCount;
    scanf("%d", &testsCount);

    for (int test = 0; test < testsCount; ++test) {
        int arrSize, rounds;
        scanf("%d %d", &arrSize, &rounds);

        uint32_t state[5];
        for (int stateI = 0; stateI < 5; ++stateI) scanf("%x", &state[stateI]);

        for (int i = 0; i < arrSize; ++i) {
            scanf("%d", &arr[i]->value);
            arr[i]->key = 0;
        }

        for (int round = 0; round < rounds; ++round) {
            for (int i = 0; i < arrSize; ++i) arr[i]->key = xorwow(state) & 0x3fffffff;
            sortArrayByKeys(arr, arrSize);
        }

        for (int i = 0; i < arrSize; ++i) printf("%d ", arr[i]->value);
        printf("\n");
    }

    return 0;
}