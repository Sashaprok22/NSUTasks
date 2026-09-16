#include <stdio.h>
#include <math.h>

int abs(int n) {
    if (n < 0) return -n;
    else return n;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a, b;
    scanf("%d %d", &a, &b);

    double divResult = (double)a / (double)b;
    int divCeil = ceil(divResult);
    int divFloor = floor(divResult);
    int divToZero = divResult > 0 ? divFloor : divCeil;

    int remainder = a % b;
    int finallyRemainder = remainder < 0 ? abs(b) + remainder : remainder;

    printf("%d %d %d %d", divFloor, divCeil, divToZero, finallyRemainder);
    return 0;
}