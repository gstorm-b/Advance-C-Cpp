#include <stdio.h>
#include <stdint.h>
#include "linkedlist.h"

void printList(Node_t *list) {
    if (isEmpty(list)) {
        printf("List empty.\n");
        return;
    }
    
    printf("List: %d", list->value);
    list = list->next;
    while (list!=NULL) {
        printf(" - %d", list->value);
        list = list->next;
    }
    printf(".\n");
}

int main(void) {

    Node_t *linkNode = NULL;
    printf("Is list empty: %s\n", isEmpty(linkNode) ? "True" : "False");

    pushBack(&linkNode, 3);
    printList(linkNode);
    
    popFront(&linkNode);
    printList(linkNode);

    pushBack(&linkNode, 5);
    pushBack(&linkNode, 7);

    // printList(linkNode);
    // printf("Value at front: %d\n", getFront(linkNode));
    // printf("Value at back: %d\n", getBack(linkNode));

    // pushFront(&linkNode, 1);
    // pushBack(&linkNode, 12);
    // printList(linkNode);
    // printf("Value at front: %d\n", getFront(linkNode));

    // insertAt(&linkNode, 27, 0);
    // printList(linkNode);
    // insertAt(&linkNode, 13, 3);
    // printList(linkNode);
    // insertAt(&linkNode, 100, 13);
    // printList(linkNode);
    // insertAt(&linkNode, 100, 1);
    // printList(linkNode);

    // popBack(&linkNode);
    // printList(linkNode);

    // popFront(&linkNode);
    // printList(linkNode);

    // insertAt(&linkNode, 100, 1);
    // printList(linkNode);

    // insertAt(&linkNode, 101, 0);
    // printList(linkNode);

    printf("Value at %d = %d.\n", 1, getAt(linkNode, 1));
    printf("Value at %d = %d.\n", 2, getAt(linkNode, 2));
    printf("Value at %d = %d.\n", 4, getAt(linkNode, 6));

    deleteAt(&linkNode, 0);
    printList(linkNode);
    // printf("List size: %d.\n", getSize(linkNode));

    deleteAt(&linkNode, 3);
    printList(linkNode);
    // printf("List size: %d.\n", getSize(linkNode));

    deleteAt(&linkNode, 5);
    printList(linkNode);

    // deleteAt(&linkNode, 1);
    // printList(linkNode);
    // printf("List size: %d.\n", getSize(linkNode));

    // popFront(&linkNode);
    // printList(linkNode);
    // printf("List size: %d.\n", getSize(linkNode));

    // deleteAt(&linkNode, 0);
    // printList(linkNode);
    // printf("List size: %d.\n", getSize(linkNode));

    printf("Is list empty: %s\n", isEmpty(linkNode) ? "True" : "False");

    return 0;
}