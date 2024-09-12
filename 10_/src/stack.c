#include <stack.h>

#define PRINT_MSG_LN(msg)       printf(#msg);   printf("\n")

void stackInitialize(Stack_t *stack, int size) {
    stack->items = (Stack_Data_Type *)malloc(sizeof(Stack_Data_Type) * size);
    stack->size = size;
    stack->top = -1;
}

void stackPush(Stack_t *stack, Stack_Data_Type data) {
    if (!stackIsFull(stack)) {
        stack->items[++(stack->top)] = data; 
    } else {
        PRINT_MSG_LN("Stack is overflow!");
    }
}

Stack_Data_Type stackPop(Stack_t *stack) {
    if (!stackIsEmpty(stack)) {
        return stack->items[(stack->top)--]; 
    } else {
        PRINT_MSG_LN("Stack is underflow!");
        return -1;
    }
}

Stack_Data_Type stackTop(Stack_t *stack) {
    if (!stackIsEmpty(stack)) {
        return stack->items[stack->top];
    } else {
        PRINT_MSG_LN("Stack is empty!");
        return -1;
    }
}

int stackIsEmpty(Stack_t const *stack){
    return (stack->top == -1);
}

int stackIsFull(Stack_t const *stack) {
    return (stack->top == (stack->size - 1));
}