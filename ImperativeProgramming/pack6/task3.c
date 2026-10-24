#include <stdio.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int p, q;
        long long m;
        scanf("%d/%d xor %llx", &p, &q, &m);

        double current = (double)p / (double)q;
        long long bytes;
        memcpy(&bytes, &current, sizeof(double));
        bytes ^= m;

        double result;
        memcpy(&result, &bytes, sizeof(double));

        printf("%0.15g\n", result);
    }
    return 0;
}