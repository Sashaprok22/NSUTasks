#include <stdio.h>

typedef struct Node_s {
    int next;
    int prev;
    int value;
} Node;

void printList(int firstNode, Node *nodes) {
    int currentNode = firstNode;

    while (currentNode != -1) {
        printf("%d\n", nodes[currentNode].value);
        currentNode = nodes[currentNode].next;
    }

    printf("===\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int testsCount;
    scanf("%d", &testsCount);

    for (int test = 0; test < testsCount; ++test) {
        int nodesCount, firstNodeI, lastNodeI, actionsCount;
        scanf("%d %d %d %d", &nodesCount, &firstNodeI, &lastNodeI, &actionsCount);

        Node nodes[nodesCount + actionsCount];

        for (int i = 0; i < nodesCount; ++i) {
            int value, nextI, prevI;
            scanf("%d %d %d", &value, &nextI, &prevI);

            Node *node = &nodes[i];
            node->value = value;
            node->next = nextI;
            node->prev = prevI;
        }

        int nextNodeI = nodesCount;
        for (int i = 0; i < actionsCount; ++i) {
            int operType, nodeI, value;
            scanf("%d %d", &operType, &nodeI);
            if (operType != 0) scanf("%d", &value);

            if (operType == 1) {
                Node *node = &nodes[nextNodeI];
                node->value = value;

                if (nodeI == -1) {
                    node->prev = -1;
                    node->next = firstNodeI;
                    if (firstNodeI != -1) nodes[firstNodeI].prev = nextNodeI;
                    firstNodeI = nextNodeI;
                    if (lastNodeI == -1) lastNodeI = nextNodeI;
                } else {
                    Node *prevNode = &nodes[nodeI];

                    if (prevNode->next != -1) {
                        Node *nextNode = &nodes[prevNode->next];
                        nextNode->prev = nextNodeI;
                    } else {
                        lastNodeI = nextNodeI;
                    }

                    node->prev = nodeI;
                    node->next = prevNode->next;
                    prevNode->next = nextNodeI;
                }
                printf("%d\n", nextNodeI);
                ++nextNodeI;

            } else if (operType == -1) {
                Node *node = &nodes[nextNodeI];
                node->value = value;

                if (nodeI == -1) {
                    node->next = -1;
                    node->prev = lastNodeI;
                    if (lastNodeI != -1) nodes[lastNodeI].next = nextNodeI;
                    lastNodeI = nextNodeI;
                    if (firstNodeI == -1) firstNodeI = nextNodeI;
                } else {
                    Node *nextNode = &nodes[nodeI];

                    if (nextNode->prev != -1) {
                        Node *prevNode = &nodes[nextNode->prev];
                        prevNode->next = nextNodeI;
                    } else {
                        firstNodeI = nextNodeI;
                    }

                    node->prev = nextNode->prev;
                    node->next = nodeI;
                    nextNode->prev = nextNodeI;
                }
                printf("%d\n", nextNodeI);
                ++nextNodeI;
                
            } else if (operType == 0) {
                Node *node = &nodes[nodeI];
                
                if (firstNodeI == nodeI) {
                    firstNodeI = node->next;
                    if (node->next != -1) nodes[node->next].prev = -1;
                }
                if (lastNodeI == nodeI) {
                    lastNodeI = node->prev;
                    if (node->prev != -1) nodes[node->prev].next = -1;
                }
                if (node->prev != -1 && node->next != -1) {
                    nodes[node->prev].next = node->next;
                    nodes[node->next].prev = node->prev;
                }

                printf("%d\n", node->value);
            }
        }
        printf("===\n");

        printList(firstNodeI, nodes);
    }

    return 0;
}