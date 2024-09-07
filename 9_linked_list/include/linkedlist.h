#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node_t;

Node_t *createNode(int _value);
void pushBack(Node_t **node, int _value);
void pushFront(Node_t **node, int _value);
void popBack(Node_t **node);
void popFront(Node_t **node);
int getFront(Node_t *node);
int getBack(Node_t *node);
void insertAt(Node_t **node, int _value, int index);
void deleteAt(Node_t **node, int index);
int getSize(Node_t *node);
bool isEmpty(Node_t *node);
int getAt(Node_t *node, int index);

#endif