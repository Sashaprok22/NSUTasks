#include <stdio.h>

int next_symbol(int *code) {
    int firstByte = fgetc(stdin);
    if (firstByte == EOF) return 0;

    int addBytes = 0;
    int result = 0;

    if ((firstByte & 0x80) == 0) { // Накладываем маски
        result = firstByte;

    } else if ((firstByte & 0xE0) == 0xC0) {
        addBytes = 1;
        result = firstByte & 0x1F;

    } else if ((firstByte & 0xF0) == 0xE0) {
        addBytes = 2;
        result = firstByte & 0xF;
        
    } else if ((firstByte & 0xF8) == 0xF0) {
        addBytes = 3;
        result = firstByte & 0x7;
    } else {
        return -1;
    }

    for (int i = 0; i < addBytes; ++i) {
        int byte = fgetc(stdin);
        if (byte == EOF || (byte & 0xC0) != 0x80) return -1;
        result = (result << 6) | (byte & 0x3F);
    }

    *code = result;

    if (
        result > 0x10FFFF ||
        result >= 0xD800 && result <= 0xDFFF ||
        addBytes > 0 && result <= 0x7F ||
        addBytes > 1 && result <= 0x7FF ||
        addBytes > 2 && result <= 0xFFFF
    ) return -2;

    return 1;
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    while(1) {
        int code;
        int status = next_symbol(&code);
        if (!status || status == -1) break;
        else if (status == -2) code = 0xFFFD;
        fwrite(&code, sizeof(code), 1, stdout);
    }

    return 0;
} 