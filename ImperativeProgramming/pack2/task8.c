#include <stdio.h>

int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 != 0 || year % 400 == 0) return 1;
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int day, month, year, days;
    scanf("%d %d %d %d", &day, &month, &year, &days);

    while (days > 0) {
        int daysToNextMonth = daysInMonth[month - 1] - day;
        if (month == 2 && isLeapYear(year) == 1) ++daysToNextMonth;
        if (daysToNextMonth >= days) {
            day += days;
            break;
        }

        days -= daysToNextMonth;
        day = 0;

        if (month == 12) {
            month = 1;
            ++year;
        } else {
            ++month;
        }
    }

    printf("%d %d %d", day, month, year);
}