#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *prev, *next;
    double value;
} Node;

Node *getNode(double *value) {
    return (Node*)((char *)value - offsetof(Node, value));
}

// создаёт пустой список
// возвращает указатель на value в голове списка (вспом. узел)
double *initList() {
    Node *node = malloc(sizeof(Node));

    node->next = node;
    node->prev = node;
    node->value = 0.0;

    return &node->value;
}

// полностью освобождает память списка
// принимает указатель на value голове списка (вспом. узел)
void freeList(double *head) {
    Node *headNode = getNode(head);
    Node *currentNode = headNode->next;

    while (currentNode != headNode) {
        Node *nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(headNode);
}

// определяет следующий элемент после заданного
//(для вспом. узла возвращает первый элемент)
double *getNext(double *curr) {
    Node *node = getNode(curr);
    return &node->next->value;
}

// определяет предыдущий элемент перед заданным
//(для вспом. узла возвращает последний элемент)
double *getPrev(double *curr) {
    Node *node = getNode(curr);
    return &node->prev->value;
}

// создаёт и вставляет узел со значением newval сразу после узла where
double *addAfter(double *where, double newval) {
    Node *node = getNode(where);

    Node *newNode = malloc(sizeof(Node));
    newNode->next = node->next;
    newNode->prev = node;
    newNode->value = newval;
    newNode->next->prev = newNode;
    node->next = newNode;

    return &newNode->value;
}

// создаёт и вставляет узел со значением newval сразу перед узлом where
double *addBefore(double *where, double newval) {
    Node *node = getNode(where);

    Node *newNode = malloc(sizeof(Node));
    newNode->prev = node->prev;
    newNode->next = node;
    newNode->value = newval;
    newNode->prev->next = newNode;
    node->prev = newNode;

    return &newNode->value;
}

// удаляет и освобождает заданный узел
void erase(double *what) {
    Node *node = getNode(what);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

void printList(double *head) {
    Node *headNode = getNode(head);
    Node *currentNode = headNode->next;

    while (currentNode != headNode) {
        printf("%0.3lf\n", currentNode->value);
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
        int actions;
        scanf("%d", &actions);

        double *head = initList();
        double *nodes[100001];
        nodes[0] = head;
        int freeNodeI = 1;

        for (int actionI = 0; actionI < actions; ++actionI) {
            int operType, nodeIndex;
            scanf("%d %d", &operType, &nodeIndex);

            double *node = nodes[nodeIndex + 1];

            double value;
            if (operType != 0) scanf("%lf", &value);

            switch (operType) {
                case -1:
                    nodes[freeNodeI++] = addBefore(node, value);
                    break;

                case 1:
                    nodes[freeNodeI++] = addAfter(node, value);
                    break;

                case 0:
                    printf("%0.3lf\n", *node);
                    erase(node);
                    break;
                
                default:
                    break;
            }
            
        }
        
        printf("===\n");
        printList(head);
    }

    return 0;
}