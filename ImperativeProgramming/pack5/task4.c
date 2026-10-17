#include <stdio.h>
#include <math.h>

double calcAngle(double ax, double ay, double bx, double by, double cx, double cy) {
    double vec_ab_x = bx - ax, vec_ab_y = by - ay;
    double vec_ac_x = cx - ax, vec_ac_y = cy - ay;

    return atan2(
        fabs(vec_ab_x * vec_ac_y - vec_ab_y * vec_ac_x),
        vec_ab_x * vec_ac_x + vec_ab_y * vec_ac_y
    ) * (180 / M_PI);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        double ax, ay, bx, by, cx, cy;
        scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy);
        printf("%0.20g\n", calcAngle(ax, ay, bx, by, cx, cy));
    }

    return 0;
}