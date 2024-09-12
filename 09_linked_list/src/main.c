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

    Node_t *numbers = NULL;

    printf("Is list empty: %s\n", isEmpty(numbers) ? "True" : "False");

    pushBack(&numbers, 10);
    pushBack(&numbers, 20);
    pushBack(&numbers, 30);
    printList(numbers);

    // popFront(&numbers);
    // printList(numbers);
    // popBack(&numbers);
    // popBack(&numbers);
    // printList(numbers);

    printf("Value at front of list: %d\n", getFront(numbers));
    printf("Value at back of list: %d\n", getBack(numbers));
    printf("Value at %d: %d\n", 1, getAt(numbers, 1));

    insertAt(&numbers, 27, 0);
    insertAt(&numbers, 28, 1);
    insertAt(&numbers, 29, 3);
    insertAt(&numbers, 35, 6);
    printList(numbers);

    deleteAt(&numbers, 0);
    deleteAt(&numbers, 2);
    printList(numbers);

    printf("Is list empty: %s\n", isEmpty(numbers) ? "True" : "False");
    printf("Size of Number list: %d", getSize(numbers));
    clearList(&numbers);
    // printf("Is list empty: %s\n", isEmpty(numbers) ? "True" : "False");

    return 0;
}