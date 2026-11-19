#include <stdio.h>
#include <inttypes.h>

#define MAX_ELEMENTS 1000000

typedef struct Element_s {
    uint64_t key;
    uint32_t value;
} Element;

Element elements[MAX_ELEMENTS];
Element *arr[MAX_ELEMENTS];
Element *output[MAX_ELEMENTS];

uint64_t xorshift128plus(uint64_t state[2]) {
    uint64_t x = state[0];
    uint64_t const y = state[1];
    state[0] = y;
    x ^= x << 23;                             // a
    state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return state[1] + y;
}

void sortArrayByKeys(Element **arr, int size) {
    Element **from = arr;
    Element **to = output;

    for (int shift = 0; shift < 64; shift += 16) {
        int count[0xFFFF + 1] = {0};

        for (int i = 0; i < size; ++i) {
            int digit = (from[i]->key >> shift) & 0xFFFF;
            ++count[digit];
        }

        int position = 0;

        for (int i = 0; i <= 0xFFFF; ++i) {
            int temp = count[i];
            count[i] = position;
            position += temp;
        }

        for (int i = 0; i < size; ++i) {
            int digit = (from[i]->key >> shift) & 0xFFFF;
            to[count[digit]++] = from[i];
        }

        Element **temp = from;
        from = to;
        to = temp;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (int i = 0; i < MAX_ELEMENTS; ++i) arr[i] = &elements[i];

    int testsCount;
    scanf("%d", &testsCount);

    for (int test = 0; test < testsCount; ++test) {
        int arrSize, rounds;
        scanf("%d %d", &arrSize, &rounds);

        uint64_t state[2];
        for (int stateI = 0; stateI < 2; ++stateI)
            scanf("%16" SCNx64, &state[stateI]);

        for (int i = 0; i < arrSize; ++i) {
            arr[i]->value = i;
            arr[i]->key = 0;
        }

        for (int round = 0; round < rounds; ++round) {
            for (int i = 0; i < arrSize; ++i) arr[i]->key = xorshift128plus(state) & 0x3fffffffffffffffLL;
            sortArrayByKeys(arr, arrSize);
        }

        uint64_t hash = 5381;
        for (int i = 0; i < arrSize; i++) hash = hash * (uint64_t)31 + (uint64_t)arr[i]->value;
        printf("%016" PRIx64 "\n", hash);
    }

    return 0;
}