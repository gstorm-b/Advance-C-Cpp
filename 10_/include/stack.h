#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef int     Stack_Data_Type;

typedef struct Stack {
    Stack_Data_Type *items;
    int size;
    int top;
} Stack_t;

void stackInitialize(Stack_t *stack, int size);
void stackPush(Stack_t *stack, Stack_Data_Type data);
Stack_Data_Type stackPop(Stack_t *stack);
Stack_Data_Type stackTop(Stack_t *stack);
int stackIsEmpty(Stack_t const *stack);
int stackIsFull(Stack_t const *stack);

#endif