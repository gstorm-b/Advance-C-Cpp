#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int value);
void addNode(Node **head, int value);
Node *searchNode(Node *head, int left, int right, int value);

int *generateRandomNumber(int total_size);
void printList(const int *numb_list, int total_size);
void swapNumber(int *number_1, int *number_2);
void bubbleSort(int *number_list, int list_size);
int binarySearch(int *number_list, int left, int right, int value);



#endif