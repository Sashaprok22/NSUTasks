#include <stdio.h>

enum DirectionEnum {
    RIGHT,
    LEFT,
    UP,
    DOWN
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int rows, cols, iters;
    scanf("%d %d %d", &rows, &cols, &iters);

    __uint128_t cells[2][4][rows];
    for (int type = 0; type < 2; ++type) {
        for (int dir = 0; dir < 4; ++dir) {
            for (int row = 0; row < rows; ++row) cells[type][dir][row] = 0;
        }
    }

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int direction;
            scanf("%x", &direction);

            __uint128_t bit = (__uint128_t)1 << col;
            if (direction & 0b1000) cells[0][RIGHT][row] |= bit;
            if (direction & 0b0100) cells[0][LEFT][row] |= bit;
            if (direction & 0b0010) cells[0][UP][row] |= bit;
            if (direction & 0b0001) cells[0][DOWN][row] |= bit;
        }
    }

    int currentCells = 0, nextCells = 1;
    for (int iter = 0; iter < iters; ++iter) {
        nextCells = !currentCells;

        for (int row = 0; row < rows; ++row) {
            __uint128_t mask = ((__uint128_t)1 << cols) - 1;
            __uint128_t right = ((cells[currentCells][RIGHT][row] << 1) & mask) | (cells[currentCells][RIGHT][row] >> (cols - 1));
            __uint128_t left = (cells[currentCells][LEFT][row] >> 1) | ((cells[currentCells][LEFT][row] & 1) << (cols - 1));

            __uint128_t up = cells[currentCells][UP][row + 1 >= rows ? 0 : row + 1];
            __uint128_t down = cells[currentCells][DOWN][row <= 0 ? rows - 1 : row - 1];

            __uint128_t collision = ((right ^ left) & (up ^ down)) | ((right & left) & ~(up | down)) | ((up & down) & ~(right | left));

            cells[nextCells][RIGHT][row] = right ^ collision;
            cells[nextCells][LEFT][row] = left ^ collision;
            cells[nextCells][UP][row] = up ^ collision;
            cells[nextCells][DOWN][row] = down ^ collision;
        }

        currentCells = nextCells;
    }

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int value = 0;
            __uint128_t bit = (__uint128_t)1 << col;

            if (cells[currentCells][RIGHT][row] & bit) value |= 0b1000;
            if (cells[currentCells][LEFT][row] & bit) value |= 0b0100;
            if (cells[currentCells][UP][row] & bit) value |= 0b0010;
            if (cells[currentCells][DOWN][row] & bit) value |= 0b0001;

            printf("%X ", value);
        }
        printf("\n");
    }

    return 0;
}