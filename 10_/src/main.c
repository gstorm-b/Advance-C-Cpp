#include <stdio.h>
#include <stdint.h>
// #include "stack.h"
#include "queue.h"

// const int stack_size = 5;
const int queue_size = 4;

int main(void) {

    Queue_t queue;
    queueInitialize(&queue, queue_size);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    printf("%d\n", dequeue(&queue));
    printf("%d\n", dequeue(&queue));
    
    enqueue(&queue, 50);
    enqueue(&queue, 60);

    printf("%d\n", dequeue(&queue));
    printf("%d\n", dequeue(&queue));



    // Stack_t numbers;
    // stackInitialize(&numbers, stack_size);

    // stackPush(&numbers, 10);
    // stackPush(&numbers, 20);
    // stackPush(&numbers, 30);
    // stackPush(&numbers, 40);
    // stackPush(&numbers, 50);
    // stackPush(&numbers, 60);

    // printf("%d\n", stackPop(&numbers));
    // printf("%d\n", stackPop(&numbers));
    
    // stackPush(&numbers, 70);

    // printf("%d\n", stackPop(&numbers));
    // printf("%d\n", stackPop(&numbers));
    // printf("%d\n", stackPop(&numbers));
    // printf("%d\n", stackPop(&numbers));
    // printf("%d\n", stackPop(&numbers));

    return 0;
}