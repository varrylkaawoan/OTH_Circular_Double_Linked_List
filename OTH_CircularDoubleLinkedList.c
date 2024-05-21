#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* tail = (*head)->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

void printList(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    do {
        printf("address:%p %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

void swapNodes(Node** head, Node* a, Node* b) {
    if (a == b || *head == NULL) return;

    Node* aPrev = a->prev;
    Node* aNext = a->next;
    Node* bPrev = b->prev;
    Node* bNext = b->next;

    if (*head == a) {
        *head = b;
    } else if (*head == b) {
        *head = a;
    }

    if (a->next == b) {
        a->next = bNext;
        bNext->prev = a;
        b->prev = aPrev;
        aPrev->next = b;
        b->next = a;
        a->prev = b;
    } else if (b->next == a) {
        b->next = aNext;
        aNext->prev = b;
        a->prev = bPrev;
        bPrev->next = a;
        a->next = b;
        b->prev = a;
    } else {
        aPrev->next = b;
        b->prev = aPrev;
        aNext->prev = b;
        b->next = aNext;
        bPrev->next = a;
        a->prev = bPrev;
        bNext->prev = a;
        a->next = bNext;
    }
}

void sortList(Node** head) {
    if (*head == NULL) return;
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr && ptr1->next != *head) {
            if (ptr1->data > ptr1->next->data) {
                swapNodes(head, ptr1, ptr1->next);
                swapped = 1;
                Node* temp = ptr1;
                ptr1 = ptr1->prev;
                ptr1->next = temp;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


int main() {
    int N;
    printf("Enter the number of elements: ");
    scanf("%d", &N);

    Node* head = NULL;
    for (int i = 0; i < N; i++) {
        int data;
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    printf("\nList before sorting:\n");
    printList(head);

    sortList(&head);

    printf("\nList after sorting:\n");
    printList(head);

    return 0;
}