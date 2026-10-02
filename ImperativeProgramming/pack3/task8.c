#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int getNextMaxHeight(int *heights, int heightsCount, int currentI) {
    int maxSearched = 0;
    for (int i = currentI + 1; i < heightsCount; ++i) {
        if (heights[i] >= heights[currentI]) return heights[i];
        if (heights[i] > maxSearched) maxSearched = heights[i];
    }
    return maxSearched;
}
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int heightsCount;
    scanf("%d", &heightsCount);
 
    int heights[heightsCount];
    for (int i = 0; i < heightsCount; ++i) {
        int height;
        scanf("%d", &height);
        heights[i] = height;
    }
 
   long long totalVolume = 0;

   int l = 0, r = heightsCount - 1;
   int maxL = 0, maxR = 0;

   while (l <= r) {
    if (heights[l] <= heights[r]) {
        if (heights[l] > maxL) maxL = heights[l];
        else totalVolume += (long long)maxL - (long long)heights[l];
        ++l;
    } else {
        if (heights[r] > maxR) maxR = heights[r];
        else totalVolume += (long long)maxR - (long long)heights[r];
        --r;
    }
   }
 
    printf("%lld", totalVolume);
 
    return 0;
}