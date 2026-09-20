#include <stdio.h>
#include <math.h> 

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int bites;
    scanf("%d", &bites);

    int bytesCount = ceil(bites / 8.0);
    int lastByteSize = bites % 8 == 0 ? 8 : bites % 8;

    for (int byte = 0; byte < bytesCount; ++byte) {
        int bitesInByte = (byte + 1) == bytesCount ? lastByteSize : 8;
        int byteValue = 0;
        for (int bit = 0; bit < bitesInByte; ++bit) {
            int bitValue;
            scanf("%1d", &bitValue);
            byteValue += bitValue << bit;
        }

        printf("%d ", byteValue);
    }

    return 0;
}