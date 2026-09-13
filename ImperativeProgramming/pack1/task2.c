#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int x = -1, y = -2, z = -3;
    scanf("%d %d %d", &x, &y, &z);

    if (x <= 0) {
        printf("-1");
        return 0;
    } else if (y <= 0) {
        printf("-2");
        return 0;
    } else if (z <= 0) {
        printf("-3");
        return 0;
    }

    int areaSize = 2 * (x * y + x * z + y * z);
    printf("%d", areaSize);
    return 0;
}