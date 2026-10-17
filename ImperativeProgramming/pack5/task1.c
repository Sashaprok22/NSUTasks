#include <stdio.h>

double exp(double x) {
    int negative = 0;
    if (x < 0) {
        negative = 1;
        x = -x;
    }

    double prevPart = 1.0;
    double result = prevPart;
    for (int i = 1; i < 380; ++i) {
        prevPart *= x / (double)i;
        result += prevPart;

        if (prevPart < 1e-16) break;
    }

    if (negative) result = 1.0 / result;
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        double num;
        scanf("%lf", &num);
        printf("%0.15g\n", exp(num));
    }

    return 0;
}