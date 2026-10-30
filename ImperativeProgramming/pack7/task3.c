#include <stdio.h>

#define MAX_NODES 200001
#define MAX_KEYS 1000000

typedef struct Node_s {
    int next;
    char value[8];
} Node;

Node nodes[MAX_NODES];
int first[MAX_KEYS];
int last[MAX_KEYS];

void printList(int key, int firstNode) {
    if (firstNode == -1) return;
    int currentNode = firstNode;

    while (currentNode != -1) {
        printf("%d %s\n", key, nodes[currentNode].value);
        currentNode = nodes[currentNode].next;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int count;
    scanf("%d", &count);

    int nextNodeI = 0;
    
    for (int i = 0; i < MAX_KEYS; ++i) {
        first[i] = -1;
        last[i] = -1;
    }

    for (int i = 0; i < count; ++i) {
        int key;
        scanf("%d", &key);

        Node *node = &nodes[nextNodeI];
        node->next = -1;
        scanf("%7s", node->value);

        if (first[key] == -1) first[key] = nextNodeI;
        else nodes[last[key]].next = nextNodeI;
        last[key] = nextNodeI;
        ++nextNodeI;
    }

    for (int i = 0; i < MAX_KEYS; ++i) printList(i, first[i]);

    return 0;
}