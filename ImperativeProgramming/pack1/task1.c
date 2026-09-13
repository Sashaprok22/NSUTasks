#include <stdio.h>
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int count;
    scanf("%d", &count);
 
    int summ = 0;
    for (int i = 0; i < count; ++i) {
        int currentNumber;
        scanf("%d", &currentNumber);
 
        if (currentNumber % 2 == 0) continue;
        summ += currentNumber;
    }
 
    printf("%d", summ);
    return 0;
}