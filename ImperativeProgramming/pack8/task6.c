#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    int value;
    struct Node_s *next;
} Node;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d %d", &n, &k);

    Node *firstNode = NULL, *lastNode = NULL;
    for (int i = 0; i < n; ++i) {
        Node *node = (Node*)malloc(sizeof(Node));
        node->value = i + 1;
        
        if (firstNode == NULL) firstNode = node;
        if (lastNode != NULL) lastNode->next = node;
        lastNode = node;
    }
    lastNode->next = firstNode;

    while (lastNode != lastNode->next) {
        for (int i = 1; i < k; ++i) {
            lastNode = lastNode->next;
        }

        Node *newNextNode = lastNode->next->next;
        printf("%d\n", lastNode->next->value);
        free(lastNode->next);
        lastNode->next = newNextNode;
    }
    printf("%d\n", lastNode->value);

    return 0;
}