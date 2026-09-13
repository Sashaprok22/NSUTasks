#include <stdio.h>
#include <math.h>

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n = -1;
    scanf("%d", &n);
    if (n < 1) return 0;

    long long answer = 0;

    // for (int a = 1; a <= n; ++a) {
    //     for (int b = 1; b <= a; ++b) {
    //         if (a * b > n) break;
    //         for (int c = 1; c <= b; ++c) {
    //             int volume = a * b * c;
    //             if (volume > n) break;
    //             ++answer;
    //         }
    //     }
    // }

    // for (int a = 1; a <= n; ++a) {
    //     for (int b = 1; b <= min(a, n / a); ++b) {
    //         answer += min( b, n / (a * b) );
    //     }
    // }

    for (int a = 1; pow(a, 3) <= n; ++a) {
        for (int b = a; a * pow(b, 2) <= n; ++b) {
            int max_c = n / (a * b);
            answer += (max_c - b + 1);
        }
    }

    printf("%lld", answer);

    return 0;
}