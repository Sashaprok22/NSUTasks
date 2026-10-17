#include <stdio.h>
#include <string.h>

typedef struct Label_s {
    char name[16];
    int age;
} Label;

typedef struct NameStats_s {
    int cntTotal;
    int cntLong;
} NameStats;

typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;
} AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges) {
    for (int i = 0; i < cnt; ++i) {
        ++oNames->cntTotal;
        if (strlen(arr[i].name) > 10) ++oNames->cntLong;

        ++oAges->cntTotal;
        if (arr[i].age >= 18) ++oAges->cntAdults;
        else if (arr[i].age < 14) ++oAges->cntKids;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    Label labels[n];
    for (int i = 0; i < n; ++i) {
        Label label;
        scanf("%s %d let", label.name, &label.age);
        labels[i] = label;
    }

    NameStats names;
    names.cntLong = 0;
    names.cntTotal = 0;

    AgeStats ages;
    ages.cntAdults = 0;
    ages.cntKids = 0;
    ages.cntTotal = 0;

    calcStats(labels, n, &names, &ages);

    printf("names: total = %d\n", names.cntTotal);
    printf("names: long = %d\n", names.cntLong);
    printf("ages: total = %d\n", ages.cntTotal);
    printf("ages: adult = %d\n", ages.cntAdults);
    printf("ages: kid = %d\n", ages.cntKids);

    return 0;
}