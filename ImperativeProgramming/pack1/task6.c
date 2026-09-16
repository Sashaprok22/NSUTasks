#include <stdio.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int count;
    scanf("%d", &count);

    int nums[count];
    int maxNumberIndex = 0;
    int minNumberIndex = 0;

    for (int i = 0; i < count; ++i) {
        int num;
        scanf("%d", &num);

        nums[i] = num;

        if (num < nums[minNumberIndex]) minNumberIndex = i;
        if (num > nums[maxNumberIndex]) maxNumberIndex = i;
    }

    printf("%d %d %d %d", nums[minNumberIndex], minNumberIndex + 1, nums[maxNumberIndex], maxNumberIndex + 1);
    return 0;
}