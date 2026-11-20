#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

#define MAX_ELEMENTS 1000000
#define THRESHOLD 64

typedef struct Element_s {
    uint64_t key;
    uint32_t value;
} Element;

Element elements[MAX_ELEMENTS];
Element output[MAX_ELEMENTS];
uint32_t positions[MAX_ELEMENTS];

uint64_t xorshift128plus(uint64_t state[2]) {
    uint64_t x = state[0];
    uint64_t const y = state[1];
    state[0] = y;
    x ^= x << 23;                             // a
    state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return state[1] + y;
}

void insertSortArrayByKeys(Element *arr, int size) {
    for (int i = 1; i < size; ++i) {
        Element temp = arr[i];
        int j = i;

        while (j > 0 && arr[j - 1].key > temp.key) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = temp;
    }
}

int compareElements(const void *a, const void *b) {
    const Element *arg1 = (const Element *)a;
    const Element *arg2 = (const Element *)b;

    if (arg1->key < arg2->key) return -1;
    if (arg1->key > arg2->key) return 1;
    return 0;
}

void sortArrayByKeys(Element *from, Element *to, int size) {
    int blockBits = 16;
    int blocksCount = 1 << blockBits;
    int shift = 62 - blockBits;
    for (int i = 0; i < blocksCount; ++i) positions[i] = 0;

    for (int i = 0; i < size; ++i) {
        int block = from[i].key >> shift;
        ++positions[block];
    }

    int start = 0;
    for (int i = 0; i < blocksCount; ++i) {
        int count = positions[i];
        positions[i] = start;
        start += count;
    }

    for (int i = 0; i < size; ++i) {
        Element temp = from[i];
        int block = temp.key >> shift;

        to[positions[block]++] = temp;
    }

    int begin = 0;

    for (int i = 0; i < blocksCount; ++i) {
        int end = positions[i];
        int len = end - begin;

        if (len <= THRESHOLD) insertSortArrayByKeys(to + begin, len);
        else qsort(to + begin, len, sizeof(Element), compareElements);
            
        begin = end;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int testsCount;
    scanf("%d", &testsCount);

    for (int test = 0; test < testsCount; ++test) {
        int arrSize, rounds;
        scanf("%d %d", &arrSize, &rounds);

        uint64_t state[2];
        for (int stateI = 0; stateI < 2; ++stateI)
            scanf("%16" SCNx64, &state[stateI]);

        Element *current = elements;
        Element *buffer = output;

        for (int i = 0; i < arrSize; ++i) current[i].value = i;

        for (int round = 0; round < rounds; ++round) {
            for (int i = 0; i < arrSize; ++i) current[i].key = xorshift128plus(state) & 0x3fffffffffffffffLL;
            if (arrSize <= THRESHOLD) insertSortArrayByKeys(current, arrSize);
            else {
                sortArrayByKeys(current, buffer, arrSize);

                Element *temp = current;
                current = buffer;
                buffer = temp;
            }
        }

        uint64_t hash = 5381;
        for (int i = 0; i < arrSize; i++) hash = hash * (uint64_t)31 + (uint64_t)current[i].value;
        printf("%016" PRIx64 "\n", hash);
    }

    return 0;
}