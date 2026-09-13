#include <stdio.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int count = -1;
    scanf("%d", &count);
    if (count < 0) return 0;

    int nums[count];
    int maxNumberIndex = 0;
    int minNumberIndex = 0;

    for (int i = 0; i < count; ++i) {
        int num  = 10001;
        scanf("%d", &num);
        if (num > 10000) continue;

        nums[i] = num;

        if (num < nums[minNumberIndex]) minNumberIndex = i;
        if (num > nums[maxNumberIndex]) maxNumberIndex = i;
    }

    printf("%d %d %d %d", nums[minNumberIndex], minNumberIndex + 1, nums[maxNumberIndex], maxNumberIndex + 1);
    return 0;
}