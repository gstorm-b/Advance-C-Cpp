#include "queue.h"

#define PRINT_MSG_LN(msg)       printf(#msg);   printf("\n")

void queueInitialize(Queue_t *queue, int size) {
    queue->items = (Queue_Data_Type *)malloc(sizeof(Queue_Data_Type)*size);
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
}

void enqueue(Queue_t *queue, Queue_Data_Type data) {
    if (!queueIsFull(queue)) {
        if (queueIsEmpty(queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % queue->size;
        }
        queue->items[queue->rear] = data;
    } else {
        PRINT_MSG_LN("Queue overflow!");
    }
}

Queue_Data_Type dequeue(Queue_t *queue) {
    if (!queueIsEmpty(queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeued_value;
    } else {
        PRINT_MSG_LN("Queue underflow!");
        return -1;
    }
}

Queue_Data_Type queueFront(Queue_t *queue) {
    if (!queueIsEmpty(queue)) {
        return queue->items[queue->front];
    } else {
        PRINT_MSG_LN("Queue is empty.");
        return -1;
    }
}

int queueIsEmpty(Queue_t const *queue) {
    return (queue->front == -1);
}

int queueIsFull(Queue_t const *queue) {
    return (((queue->rear + 1) % queue->size) == queue->front);
}