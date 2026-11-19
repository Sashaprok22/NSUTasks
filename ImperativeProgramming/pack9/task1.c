#include <stdio.h>
#include <stdlib.h>

typedef struct Element_s {
    char value[8];
    int key;
} Element;

void sortArrayByKeys(Element **arr, int size) {
    for (int i = 1; i < size; ++i) {
        Element *temp = arr[i];
        int key = temp->key;
        int j = i;

        while (j > 0 && arr[j - 1]->key > key) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = temp;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    Element *elements[n];
    for (int i = 0; i < n; ++i) {
        elements[i] = (Element*)malloc(sizeof(Element));
        scanf("%d %s", &elements[i]->key, elements[i]->value);
    }
    sortArrayByKeys(elements, n);

    for (int i = 0; i < n; ++i) {
        printf("%d %s\n", elements[i]->key, elements[i]->value);
    }

    return 0;
}