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

    for (int i = 0; i < count; ++i) {
        int currentN = nums[i];
        int counter = 0;
        for (int k = i + 1; k < count; ++k) {
            if (nums[k] < nums[i]) ++counter;
        }
        printf("%d ", counter);
    }

    return 0;
}