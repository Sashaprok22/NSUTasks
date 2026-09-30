#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int count;
    scanf("%d", &count);

    int nums[count];
    for (int i = 0; i < count; ++i) {
        int n;
        scanf("%d", &n);
        nums[i] = n;
    }

    for (int step = 1; step <= count; ++step) {
        int sum = 0;
        for (int k = step - 1; k < count; k += step) sum += nums[k];

        printf("%d\n", sum);
    }

    return 0;
}