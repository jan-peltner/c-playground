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

int main(void) {
    IntList linked_list = {NULL, NULL};

    push_node(&linked_list, 5);
    push_node(&linked_list, 10);
    push_node(&linked_list, 20);
    push_node(&linked_list, 40);

    walk_and_print_list(linked_list.head, print_node);
}
