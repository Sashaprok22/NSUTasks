#include <stdio.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int hour = -1, mins = -1, secs = -1, duration = -1;
    scanf("%d %d %d %d", &hour, &mins, &secs, &duration);
    if (hour < 0 || mins < 0 || secs < 0 || duration < 0) return 0;

    int addMins = (secs + duration) / 60;
    secs = (secs + duration) % 60;

    int addHours = (mins + addMins) / 60;
    mins = (mins + addMins) % 60;

    hour = (hour + addHours) % 24;

    printf("%d %d %d", hour, mins, secs);

    return 0;
}