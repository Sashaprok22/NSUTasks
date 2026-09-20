#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int start, end, count;
    scanf("%d %d %d", &start, &end, &count);

    int diff = end - start;
    int maxStep = diff / (count - 1);
    int threshold = diff / count;

    int result = 0;
    for (int step = 1; step <= maxStep; ++step) {
        if (step <= threshold) result += step;
        else result += diff - (count - 1) * step + 1;
    }


    printf("%d", result);

    return 0;
}