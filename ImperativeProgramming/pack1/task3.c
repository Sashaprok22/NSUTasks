#include <stdio.h>

int getDigitsCount(int price) {
    int totalDigits = 0;
    while (price > 0)
    {
        int digit = price % 10;
        if (digit == 9) ++totalDigits;

        price /= 10;
    }
    return totalDigits;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int itemsCount = -1;
    scanf("%d", &itemsCount);
    if (itemsCount <= 0) {
        printf("0");
        return 0;
    }

    int freeDigits = 0;
    int needDigits = 2 * itemsCount;
    for (int i = 0; i < itemsCount; ++i) {
        int oldPrice = -1;
        scanf("%d", &oldPrice);
        if (oldPrice <= 0) continue;
        int oldDigitsCount = getDigitsCount(oldPrice);
        int newDigitsCount = getDigitsCount(oldPrice - 1);
        freeDigits += oldDigitsCount - newDigitsCount;
    }

    printf("%d", needDigits - freeDigits);
    return 0;
}