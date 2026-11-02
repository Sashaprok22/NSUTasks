#include <stdio.h>
#include <string.h>

typedef union Value_s {
    long long longVal;
    double doubleVal;
} Value;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int p, q;
        long long m;
        scanf("%d/%d xor %llx", &p, &q, &m);

        Value val;
        val.doubleVal = (double)p / (double)q;
        val.longVal ^= m;

        printf("%0.15g\n", val.doubleVal);
    }
    return 0;
}