#include "binary_search.h"

Node *createNode(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void addNode(Node **head, int value) {
    Node *new_node = createNode(value);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    if ((*head)->data > value) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        if (temp->next->data > value) {
            break;
        }
        temp = temp->next;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

Node *searchNode(Node *head, int left, int right, int value) {
    if (right >= left) {
        Node *current_node = head;
        int mid = (left + right) / 2;
        
        int counter = left;
        while (counter++ != mid) {
            current_node = current_node->next;
        }
        int value_mid = current_node->data;

        if (value_mid == value)  {
            return current_node;
        }
        if (value_mid > value) {
            return searchNode(head, left, mid - 1, value);
        }
        return searchNode(current_node->next, mid + 1, right, value);
    }
    return NULL;
}

int *generateRandomNumber(int total_size) {
    srand(time(NULL));
    int *numb_list = (int *)malloc(sizeof(int)*total_size);
    for (int index=0;index<total_size;index++) {
        numb_list[index] = rand();
    }
    return numb_list;
}

void printList(const int *numb_list, int total_size) {
    if (numb_list == NULL) {
        return;
    }

    for (int index=0;index<total_size;index++) {
        printf("%d\t", numb_list[index]);
    }
}

void swapNumber(int *number_1, int *number_2) {
    int temp = *number_1;
    *number_1 = *number_2;
    *number_2 = temp;
}

void bubbleSort(int *number_list, int list_size) {
    int index_1, index_2;
    for (index_1=0;index_1<(list_size-2);index_1++) {
        for (index_2=list_size-1;index_2>index_1;index_2--) {
            if (number_list[index_2] < number_list[index_2-1]) {
                swapNumber(&number_list[index_2], &number_list[index_2-1]);
            }
        }
    }
}

int binarySearch(int *number_list, int left, int right, int value) {
    if (right >= left) {
        int mid = (left + right) / 2;
        if (number_list[mid] == value)  {
            return mid;
        }
        if (number_list[mid] > value) {
            return binarySearch(number_list, left, mid - 1, value);
        }
        return binarySearch(number_list, mid + 1, right, value);
    }
    return -1;
}