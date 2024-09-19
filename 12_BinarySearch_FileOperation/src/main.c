#include "binary_search.h"

void test_binary_search() {
    int list_size = 20;
    int *number_list = generateRandomNumber(list_size);
    printList(number_list, list_size);

    int searchNumber = number_list[12];
    
    printf("\n");
    bubbleSort(number_list, list_size);
    printList(number_list, list_size);

    printf("\n");
    printf("%d => %d\n", searchNumber, binarySearch(number_list, 0, list_size-1, searchNumber));
    printf("%d => %d\n", 100, binarySearch(number_list, 0, list_size-1, 100));

    free(number_list);
}

void printLinkedList(Node *list) {
    if (list == NULL) {
        printf("List empty.\n");
        return;
    }
    
    printf("List: %d", list->data);
    list = list->next;
    while (list!=NULL) {
        printf(" - %d", list->data);
        list = list->next;
    }
    printf(".\n");
}

void test_binary_search_list() {
    int list_size = 20;
    int *numbers = generateRandomNumber(list_size);
    int searchNumber = numbers[12];
    printList(numbers, list_size);
    printf("\n");
    
    Node *number_list = NULL;
    for (int index=0;index<list_size;index++) {
        addNode(&number_list, numbers[index]);
    }
    free(numbers);
    printLinkedList(number_list);

    printf("\n");
    Node *node_1 = searchNode(number_list, 0, list_size-1, searchNumber);
    Node *node_2 = searchNode(number_list, 0, list_size-1, 100);
    printf("%d => address: 0x%p\n", searchNumber, (node_1) ? node_1 : 0);
    printf("%d => address: 0x%p\n", 25372, (node_2) ? node_2 : 0);
}

int main(void) {
    // test_binary_search();
    test_binary_search_list();

    // const int max_buffer = 1000;
    // char buffer[max_buffer];
    // FILE *file = fopen("./hello.txt", "r");
    // if (file == NULL) {
    //     printf("The file is not opened. The program will "
    //            "now exit.");
    //     return 0;
    // }

    // fgets(buffer, 1000, file);
    // printf("%s", buffer);
    // fgets(buffer, 1000, file);
    // printf("%s", buffer);

    return 0;
}