#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int masksCount;
    scanf("%d", &masksCount);

    long long masks[masksCount];
    int result = 0;
    for (int i = 0; i < masksCount; ++i) {
        long long mask;
        scanf("%llx", &mask);
        masks[i] = mask;

        for (int k = 0; k < i; ++k) {
            if ((mask & masks[k]) == 0) ++result;
        }
    }

    printf("%d", result);
}