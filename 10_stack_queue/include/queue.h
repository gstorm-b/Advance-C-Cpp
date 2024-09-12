#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef int     Queue_Data_Type;

typedef struct Queue {
    Queue_Data_Type *items;
    int size;
    int front;
    int rear;
} Queue_t;

void queueInitialize(Queue_t *queue, int size);
void enqueue(Queue_t *queue, Queue_Data_Type data);
Queue_Data_Type dequeue(Queue_t *queue);
Queue_Data_Type queueFront(Queue_t *queue);
int queueIsEmpty(Queue_t const *queue);
int queueIsFull(Queue_t const *queue);

#endif