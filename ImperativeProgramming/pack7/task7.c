#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    int value;
    struct Node_s *next, *nextBig;

    int isBig;
    int distance;

} Node;

int getListLen(Node *head) {
    int len = 0;
    Node *currentNode = head;
    while (currentNode != NULL) {
        ++len;
        currentNode = currentNode->next;
    }
    return len;
}

void recalcList(Node *head) {
    int len = getListLen(head);
    int dist = len / (len * 0.5);
    
    Node *prevBigNode = NULL;
    Node *currentNode = head;
    int i = 0;
    while (currentNode != NULL) {
        int isBig = i % dist == 0;
        currentNode->isBig = isBig;
        currentNode->nextBig = NULL;

        if (isBig && prevBigNode != NULL) {
            prevBigNode->nextBig = currentNode;
            prevBigNode->distance = dist;
            prevBigNode = currentNode;
        }
        currentNode = currentNode->next;
    }
}

Node *getNodeByIndex(Node *head, int index) {
    int i = 0;
    Node *currentNode = head;

    while (i != index) {
        if (currentNode->isBig && currentNode->nextBig != NULL) {
            if (currentNode->distance + i <= index) {
                currentNode = currentNode->nextBig;
                i += currentNode->distance;
                continue;
            }
        }
        ++i;
        currentNode = currentNode->next;
    }
    
    return currentNode;
}

Node *createNode(int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->isBig = 0;
    node->distance = 0;

    return node;
}

void insertToIndex(Node *head, int index, int value) {
    Node *node = createNode(value);

    Node *oldNode = getNodeByIndex(head, index-1);
    node->next = oldNode->next;
    oldNode->next = node;

    recalcList(head);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int requests;
    scanf("%d", &requests);

    Node *head = NULL;

    for (int request = 0; request < requests; ++request) {
        int type, k;
        scanf("%d %d", &type, &k);

        switch (type) {
            case 0:
                int value;
                scanf("%d", &value);

                if (head == NULL) {
                    head = createNode(value);
                    head->isBig = 1;
                } else {
                    if (k > 0) {
                        Node *node = createNode(value);
                        Node *oldNode = getNodeByIndex(head, k - 1);
                        node->next = oldNode->next;
                        oldNode->next = node;
                    } else {
                        Node *node = createNode(value);
                        node->next = head;
                        head = node;
                    }
                    recalcList(head);
                }

                break;

            case 1:
                printf("%d\n", getNodeByIndex(head, k)->value);
                break;
            
            default:
                break;
        }
    }

    return 0;
}