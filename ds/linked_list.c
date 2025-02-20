#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    struct IntNode* next; // Need to use struct here because the typedef isn't available yet
    int value;
} IntNode;

typedef struct {
    IntNode* head;
    IntNode* tail;
} IntList;

typedef void (*PrinterFn)(IntNode* node);

void push_node(IntList* list, int node_val) {
    IntNode* node = malloc(sizeof(IntNode));

    node->value = node_val;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
}

void print_node(IntNode* node) {
    printf("Node value: %d\n", node->value);
}

void walk_and_print_list(IntNode* node, PrinterFn pfn) {
    pfn(node);
    if (node->next != NULL) {
        walk_and_print_list(node->next, pfn);
    }
}

void some_fn(IntList* list) {
    // Do some work...
    int result = 50;

    // Push a new node onto the linked list
    // Because we allocate it on the heap it's going to be
    // accessible even outside of this function's scope
    push_node(list, result);
}

int main(void) {
    IntList numbers = {NULL, NULL};

    push_node(&numbers, 5);
    push_node(&numbers, 10);
    push_node(&numbers, 20);
    push_node(&numbers, 40);

    some_fn(&numbers);

    walk_and_print_list(numbers.head, print_node);
}
