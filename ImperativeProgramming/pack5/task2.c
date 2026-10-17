#include <stdio.h>
#include <math.h>

double sin(double x) {

    x = fmod(x, M_PI_2);

    double prevPart = x;
    double result = prevPart;
    for (int i = 1; i < 10; ++i) {
        prevPart *= -(x * x) / ((2 * i) * (2 * i + 1));
        result += prevPart;
    }

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
        printf("%0.15lf\n", sin(num));
    }

    return 0;
}