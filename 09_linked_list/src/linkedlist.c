#include "linkedlist.h"
#include <assert.h>

#define _DEBUG_LOG(condition, cmd)       assert((condition) && cmd)
#define _SET_NEXT_NODE(node)             node = node->next

static void _insertNodeBefore(Node_t **node, int data) {
    Node_t *new_node = createNode(data);
    new_node->next = *node;
    *node = new_node;
}

Node_t *createNode(int data) {
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    node->value = data;
    node->next = NULL;
    return node;
}

void pushBack(Node_t **node, int data) {
    Node_t *new_node = createNode(data);
    if (*node == NULL) {
        *node = new_node;
    } else {
        Node_t *temp = *node;
        while (temp->next != NULL) {
            _SET_NEXT_NODE(temp);
        }
        temp->next = new_node;
    }
}

void pushFront(Node_t **node, int data) {
    Node_t *new_node = createNode(data);
    if (*node == NULL) {
        *node = new_node;
    } else { 
        new_node->next = *node;
        *node = new_node;
    }
}

void popBack(Node_t **node) {
    _DEBUG_LOG((*node != NULL), "popBack() err, Input node invalid");

    Node_t *current_node = *node;
    Node_t *next_node = NULL;
    while (current_node->next != NULL) {
        next_node = current_node->next;
        if (next_node->next == NULL) {
            current_node->next = NULL;
            free(next_node);
            return;
        }
        _SET_NEXT_NODE(current_node);
    }
    free(current_node);
    *node = NULL;
}

void popFront(Node_t **node) {
    _DEBUG_LOG((*node != NULL), "popFront err, Input node invalid");
    
    Node_t *temp = *node;
    *node = temp->next;
    free(temp);
}

int getFront(Node_t *node) {
    _DEBUG_LOG((node != NULL), "getFront() err, Input node invalid");
    return node->value;
}

int getBack(Node_t *node) {
    _DEBUG_LOG((node != NULL), "getBack() err, Input node invalid");
    while (node->next != NULL) {
        _SET_NEXT_NODE(node);
    }
    return node->value;
}

int getAt(Node_t *node, int index) {
    _DEBUG_LOG((node != NULL), "getAt() err, Input node invalid");

    int count = 0;
    while (count++ != index) {
        // index out of range
        if (node->next == NULL) {
            _DEBUG_LOG(0, "getAt() err, Index out of range.");
        }
        _SET_NEXT_NODE(node);
    }

    return node->value;
}

void insertAt(Node_t **node, int data, int index) {
    _DEBUG_LOG((node != NULL), "insertAt() err, Input node invalid");

    Node_t *temp = *node;
    if (index == 0) {
        _insertNodeBefore(node, data);
        return;
    }

    int count = 1;
    while (count++ != index) {
        if (temp->next == NULL) {
            // index out range
            _DEBUG_LOG(0, "insertAt() err, Index out of range.");
            return;
        }
        _SET_NEXT_NODE(temp);
    }

    _insertNodeBefore(&(temp->next), data);
}

void deleteAt(Node_t **node, int index) {
    _DEBUG_LOG((node != NULL), "deleteAt() err, Input node invalid");
    
    Node_t *temp = *node;
    if (index == 0) {
        *node = temp->next;
        free(temp);
        return;
    }

    int count = 1;
    while (count++ != index) {
        _SET_NEXT_NODE(temp);
        if (temp->next == NULL) {
            // index out of range
            _DEBUG_LOG(0, "deleteAt() err, Index out of range.");
            // return;
        }
    }
    Node_t *delete_node = temp->next;
    temp->next = delete_node->next;
    free(delete_node);
}

int getSize(Node_t *node) {
    if (node == NULL) {
        return 0;
    }

    int list_size = 1;
    while (node->next != NULL) {
        _SET_NEXT_NODE(node);
        list_size++;
    }
    
    return list_size;
}

bool isEmpty(Node_t *node) {
    if (node == NULL) {
        return true;
    }
    return false;
}

void clearList(Node_t **node) {
    if (*node == NULL) {
        return;
    }

    Node_t *temp_node = NULL;
    while (*node != NULL) {
        temp_node = *node;
        *node = temp_node->next;
        // *node = (Node_t *)(*node)->next;
        free(temp_node);
    }
}
