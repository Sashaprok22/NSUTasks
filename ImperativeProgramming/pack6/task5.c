#include <stdio.h>
#include <inttypes.h>
#include <string.h>

typedef struct File_s {
    char name[21];
    uint64_t size;
    uint8_t isDirectory;
    uint64_t creationTimestamp;
    uint64_t changeTimestamp;
    uint8_t isHidden;
} File;

void insert(File *arr, int arrLen, int index, File value) {
    for (int i = arrLen - 2; i >= index; --i) {
        arr[i+1] = arr[i];
    }
    arr[index] = value;
}

File readFile() {
    File file;

    fread(&file.name, sizeof(char), 21, stdin);
    fread(&file.size, sizeof(uint64_t), 1, stdin);
    fread(&file.isDirectory, sizeof(uint8_t), 1, stdin);
    fread(&file.creationTimestamp, sizeof(uint64_t), 1, stdin);
    fread(&file.changeTimestamp, sizeof(uint64_t), 1, stdin);
    fread(&file.isHidden, sizeof(uint8_t), 1, stdin);

    return file;
}

void printFile(File file) {
    fwrite(&file.name, sizeof(char), 21, stdout);
    fwrite(&file.size, sizeof(uint64_t), 1, stdout);
    fwrite(&file.isDirectory, sizeof(uint8_t), 1, stdout);
    fwrite(&file.creationTimestamp, sizeof(uint64_t), 1, stdout);
    fwrite(&file.changeTimestamp, sizeof(uint64_t), 1, stdout);
    fwrite(&file.isHidden, sizeof(uint8_t), 1, stdout);
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    uint32_t filesCount;
    fread(&filesCount, sizeof(filesCount), 1, stdin);

    uint64_t startTime;
    fread(&startTime, sizeof(startTime), 1, stdin);

    uint64_t endTime;
    fread(&endTime, sizeof(endTime), 1, stdin);

    int filteredCount = 0;
    File files[filesCount];
    for (int i = 0; i < filesCount; ++i) {
        File file = readFile();
        
        if (file.isDirectory || file.isHidden || file.creationTimestamp < startTime || file.changeTimestamp > endTime) continue;

        int insertI = filteredCount;
        for (int k = 0; k < filteredCount; ++k) {
            if (strcmp(file.name, files[k].name) < 0) {
                insertI = k;
                break;
            }
        }

        insert(files, ++filteredCount, insertI, file);
    }

    for (int i = 0; i < filteredCount; ++i) printFile(files[i]);

    return 0;
}