#include <stdio.h>
#include <math.h>

int main() {
    double step = 1.0/2.0;
    int start = 1;
    double realSumm = start / (1.0 - step);
    
    double calcSumm = start;
    for (int i = 1; i < 5; ++i) {
        calcSumm += pow(step, i);
    }

    printf("%lf\n%lf", realSumm, calcSumm);
}