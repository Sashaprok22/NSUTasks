#include <stdio.h>

int check_include(int a1, int a2, int b1, int b2, int c1, int c2) {
    if (a1 * a2 < b1 * b2 + c1 * c2) return 0;

    if (a1 < b1 || a2 < b2) return 0;
    if (b1 + c1 <= a1 && c2 <= a2) return 1;
    if (b2 + c2 <= a2 && c1 <= a1) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int a1, a2, b1, b2, c1, c2;
    scanf("%d %d %d %d %d %d", &a1, &a2, &b1, &b2, &c1, &c2);

    int a[2] = {a1, a2};
    int b[2] = {b1, b2};
    int c[2] = {c1, c2};

    for (int aI = 0; aI  < 2; ++aI) {
        for (int bI = 0; bI < 2; ++bI) {
            for (int cI = 0; cI < 2; ++cI) {
                int result = check_include(a[aI], a[1 - aI], b[bI], b[1 - bI], c[cI], c[1 - cI]);
                if (result == 1) {
                    printf("YES");
                    return 0;
                }
            }
        }
    }

    printf("NO");
    return 0;

}