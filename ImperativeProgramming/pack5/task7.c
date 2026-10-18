#include <stdio.h>
#include <string.h>

typedef struct Asymptotic_s {
    double p;
    double s;
    double l;
} Asymptotic;

void parseAsymptotic(Asymptotic *asymptotic, char *raw) {
    asymptotic->l = 0;
    asymptotic->s = 0;
    asymptotic->p = 1;

    char *token = strtok(raw, " \r\n");
    while (token != NULL) {
        if (strncmp(token, "logN", 4) == 0) {
            double l;
            if (sscanf(token, "logN^%lf", &l) > 0) asymptotic->l = l;
            else asymptotic->l = 1.0;

        } else if (token[0] == 'N') {
            double s;
            if (sscanf(token, "N^%lf", &s) > 0) asymptotic->s = s;
            else asymptotic->s = 1.0;

        } else if (token[0] >= '0' && token[0] <= '9') {
            double p;
            if (sscanf(token, "%lf^N", &p) > 0) asymptotic->p = p;
            else asymptotic->p = 1.0;
        }

        token = strtok(NULL, " \r\n");
    }
}

int compareAsymptotics(Asymptotic a, Asymptotic b) {
    if (a.p < b.p) return -1;
    else if (a.p > b.p) return 1;

    if (a.s < b.s) return -1;
    else if (a.s > b.s) return 1;

    if (a.l < b.l) return -1;
    else if (a.l > b.l) return 1;

    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char rawCount[101];
    fgets(rawCount, 100, stdin);

    int n;
    sscanf(rawCount, "%d", &n);

    for (int i = 0; i < n; ++i) {
        char rawAsymptotic1[101];
        fgets(rawAsymptotic1, 100, stdin);

        Asymptotic asymptotic1;
        parseAsymptotic(&asymptotic1, rawAsymptotic1);

        char rawAsymptotic2[101];
        fgets(rawAsymptotic2, 100, stdin);

        Asymptotic asymptotic2;
        parseAsymptotic(&asymptotic2, rawAsymptotic2);

        printf("%d\n", compareAsymptotics(asymptotic1, asymptotic2));
    }
}