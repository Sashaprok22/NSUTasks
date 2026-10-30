#include <stdio.h>

typedef struct Node_s {
    struct Node_s *next;
    char value[8];
} Node;

void printList(Node *firstNode) {
    Node *currentNode = firstNode;

    while (currentNode != NULL) {
        printf("%s\n", currentNode->value);
        currentNode = currentNode->next;
    }

    printf("===\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int testsCount;
    scanf("%d", &testsCount);

    for (int test = 0; test < testsCount; ++test) {
        int nodesCount, firstIndex, actionCount;
        scanf("%d %d %d", &nodesCount, &firstIndex, &actionCount);

        Node nodes[nodesCount + actionCount];
        for (int i = 0; i < nodesCount; ++i) {
            Node *node = &nodes[i];
            char value[8];
            int nextNodeI;
            scanf("%s %d", node->value, &nextNodeI);
            if (nextNodeI == -1) node->next = NULL;
            else node->next = &(nodes[nextNodeI]);
        }

        Node *firstNode = &nodes[firstIndex];

        int nextNodeI = nodesCount;
        for (int i = 0; i < actionCount; ++i) {
            int operType, nodeIndex;
            scanf("%d %d", &operType, &nodeIndex);

            if (operType == 0) {
                Node *node = &nodes[nextNodeI++];
                printf("%d\n", nextNodeI - 1);
                scanf("%s", node->value);
                
                if (nodeIndex == -1) {
                    node->next = firstNode;
                    firstNode = node;

                } else {
                    Node *oldNode = &nodes[nodeIndex];
                    node->next = oldNode->next;
                    oldNode->next = node;
                }
            } else if (operType == 1) {
                if (nodeIndex == -1) {
                    printf("%s\n", firstNode->value);
                    firstNode = firstNode->next;
                } else {
                    printf("%s\n", nodes[nodeIndex].next->value);
                    nodes[nodeIndex].next = nodes[nodeIndex].next->next;
                }
            }
        }

        printf("===\n");

        printList(firstNode);
    }

    return 0;
}