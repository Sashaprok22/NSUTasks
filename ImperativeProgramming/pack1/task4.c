#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n = -1;
    scanf("%d", &n);
    if (n <= 0) return 0;

    if (isPrime(n) == 1) printf("YES");
    else printf("NO");
    return 0;
}