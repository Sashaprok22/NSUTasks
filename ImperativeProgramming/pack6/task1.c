#include <stdio.h>

int swapInt(int val) {
    return ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
           ((val & 0x00FF0000) >> 8)  | ((val & 0xFF000000) >> 24);
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    int needSwap = 0;
    int n;
    fread(&n, sizeof(n), 1, stdin);
    if (n < 1 || n > 10000) needSwap = 1;
    n = needSwap ? swapInt(n) : n;

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int currentNum;
        fread(&currentNum, sizeof(currentNum), 1, stdin);
        result += needSwap ? swapInt(currentNum) : currentNum;
    }

    result = needSwap ? swapInt(result) : result;
    fwrite(&result, sizeof(result), 1, stdout);
}