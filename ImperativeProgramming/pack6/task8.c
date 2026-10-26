#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct Pixel_s {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Pixel;

int min(int a, int b) {
    return a < b ? a : b;
}

Pixel readPixel(uint8_t depth) {
    Pixel pixel = {0, 0, 0, 0xFF};

    fread(&pixel.b, sizeof(uint8_t), 1, stdin);
    fread(&pixel.g, sizeof(uint8_t), 1, stdin);
    fread(&pixel.r, sizeof(uint8_t), 1, stdin);
    if (depth == 32) fread(&pixel.a, sizeof(uint8_t), 1, stdin);

    return pixel;
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    // Чтение заголовка TGA
    uint8_t idLen = fgetc(stdin);
    uint8_t colorMapType = fgetc(stdin);
    uint8_t imageType = fgetc(stdin);
    
    // Карта цветов
    uint16_t colorMapFirstIndex;
    fread(&colorMapFirstIndex, sizeof(colorMapFirstIndex), 1, stdin);

    uint16_t colorMapLen;
    fread(&colorMapLen, sizeof(colorMapLen), 1, stdin);

    uint8_t colorMapElementSize = fgetc(stdin);

    // Описание изображения
    uint16_t posX;
    fread(&posX, sizeof(posX), 1, stdin);

    uint16_t posY;
    fread(&posY, sizeof(posY), 1, stdin);

    uint16_t width;
    fread(&width, sizeof(width), 1, stdin);

    uint16_t height;
    fread(&height, sizeof(height), 1, stdin);

    uint8_t depth = fgetc(stdin);
    uint8_t descriptor = fgetc(stdin);

    // ID
    // char id[idLen];
    // if (idLen > 0) fread(id, sizeof(char), idLen, stdin);
    fseek(stdin, idLen, SEEK_CUR);

    if (colorMapType) {
        int bytes = colorMapLen * min(colorMapElementSize / 3, 8);
        fseek(stdin, bytes, SEEK_CUR); // Пропускаем данные карты
    }

    // Чтение пикселей
    int totalPixels = width * height;
    int cursor = 0;
    Pixel *pixels = malloc(totalPixels * sizeof(Pixel));
    while (cursor < totalPixels) {
        switch (imageType) {
            case 2:
                pixels[cursor++] = readPixel(depth);
                break;

            case 10:
                uint8_t control = fgetc(stdin);
                int isRepeatPacket = (control & 0x80) != 0;
                int count = (control & 0x7F) + 1;

                if (isRepeatPacket) {
                    Pixel pixel = readPixel(depth);
                    for (int i = 0; i < count; ++i) pixels[cursor++] = pixel;
                } else {
                    for (int i = 0; i < count; ++i) pixels[cursor++] = readPixel(depth);
                }

                break;
            
            default:
                break;
        }
    }

    // Запись в BMP
    fwrite("BM", sizeof(char), 2, stdout);

    int rowSize = width * 3;
    int padding = (4 - (rowSize % 4)) % 4;
    int pixelsDataSize = (rowSize + padding) * height;
    uint32_t totalBMPSize = 26 + pixelsDataSize;
    fwrite(&totalBMPSize, sizeof(totalBMPSize), 1, stdout);

    uint32_t reserved = 0;
    fwrite(&reserved, sizeof(uint32_t), 1, stdout); // Reserved

    uint32_t bfOffBits = 26;
    fwrite(&bfOffBits, sizeof(uint32_t), 1, stdout); // Зависит от версии

    uint32_t bcSize = 12;
    fwrite(&bcSize, sizeof(uint32_t), 1, stdout); // Зависит от версии

    fwrite(&width, sizeof(width), 1, stdout);
    fwrite(&height, sizeof(height), 1, stdout);

    uint16_t bcPlanes = 1;
    fwrite(&bcPlanes, sizeof(bcPlanes), 1, stdout);

    uint16_t bcBitCount = 24;
    fwrite(&bcBitCount, sizeof(bcBitCount), 1, stdout);

    int isTopDown = (descriptor & 0x20) != 0;
    int isRightLeft = (descriptor & 0x10) != 0;

    for (int line = 0; line < height; ++line) {
        int formattedLine = isTopDown ? (height - line - 1) : line;
        for (int col = 0; col < width; ++col) {
            int formattedCol = isRightLeft ? (width - col - 1) : col;
            int i = formattedLine * width + formattedCol;
            fwrite(&pixels[i].b, sizeof(uint8_t), 1, stdout);
            fwrite(&pixels[i].g, sizeof(uint8_t), 1, stdout);
            fwrite(&pixels[i].r, sizeof(uint8_t), 1, stdout);
        }

        for (int p = 0; p < padding; ++p) fputc(0, stdout);
    }

    return 0;
}