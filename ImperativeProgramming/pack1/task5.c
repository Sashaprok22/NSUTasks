#include <stdio.h>
#include <math.h>

int abs(int n) {
    if (n < 0) return -n;
    else return n;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a = -10001, b = -10001;
    scanf("%d %d", &a, &b);
    if (a < -10000 || b < -10000) return 0;

    double divResult = (double)a / (double)b;
    int divCeil = ceil(divResult);
    int divFloor = floor(divResult);
    int divToZero = divResult > 0 ? divFloor : divCeil;

    int remainder = a % b;
    int finallyRemainder = remainder < 0 ? abs(b) + remainder : remainder;

    printf("%d %d %d %d", divFloor, divCeil, divToZero, finallyRemainder);
    return 0;
}