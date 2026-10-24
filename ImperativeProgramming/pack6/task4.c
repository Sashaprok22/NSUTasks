#include <stdio.h>
#include <inttypes.h>

typedef struct Symbol_s {
    int bitsCount;
    uint64_t bits;
} Symbol;


int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    uint32_t n;
    fread(&n, sizeof(n), 1, stdin);

    Symbol symbols[n];
    for (int i = 0; i < n; ++i) {
        uint32_t len;
        fread(&len, sizeof(len), 1, stdin);

        Symbol symbol = {len, 0};
        for (int k = 0; k < symbol.bitsCount; ++k) {
            uint8_t byte = fgetc(stdin);
            symbol.bits |= ((uint64_t)byte << k);
        }
        
        symbols[i] = symbol;
    }

    uint32_t textLen;
    fread(&textLen, sizeof(textLen), 1, stdin);

    uint8_t buffer = 0;
    int bufferSize = 0;
    for (int i = 0; i < textLen; ++i) {
        uint16_t symbol;
        fread(&symbol, sizeof(symbol), 1, stdin);
        
        Symbol currentSymbol = symbols[symbol];
        for (int i = 0; i < currentSymbol.bitsCount; ++i) {
            int nextBit = (currentSymbol.bits >> i) & 1;
            buffer |= (nextBit << bufferSize++);

            if (bufferSize >= 8) {
                fwrite(&buffer, sizeof(buffer), 1, stdout);
                buffer = 0;
                bufferSize = 0;
            }
        }
    }

    if (bufferSize > 0) fwrite(&buffer, sizeof(buffer), 1, stdout);
    
    return 0;
}