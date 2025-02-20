/*
 * Singly-Linked List Implementation in C
 * 
 * This file demonstrates how to implement a singly-linked list in C
 * with proper memory management and function pointers. The implementation supports:
 *
 * - Creating and adding nodes to a linked list
 * - Traversing the list with recursive functions
 * - Function pointer usage for customizable node processing
 * - Proper handling of head/tail pointers
 *
 * Key concepts demonstrated:
 * - Self-referential structures
 * - Function pointers for flexible node processing
 * - Proper struct initialization
 * - Dynamic memory allocation
 * - Recursive list traversal
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Node structure for the linked list.
 * Uses self-referential structure definition for the next pointer.
 */
typedef struct IntNode {
    struct IntNode* next;  /* Pointer to next node, NULL if last node */
    int value;            /* Integer value stored in this node */
} IntNode;

/**
 * List control structure that maintains pointers to both ends.
 * Tracking both head and tail allows O(1) insertions at either end.
 */
typedef struct {
    IntNode* head;  /* Pointer to first node, NULL if list is empty */
    IntNode* tail;  /* Pointer to last node, NULL if list is empty */
} IntList;

/**
 * Function pointer type for node processing functions.
 * Allows customizable operations on nodes during traversal.
 */
typedef void (*NodeFn)(IntNode* node);

/**
 * Adds a new node to the end of the list.
 * Handles both empty and non-empty list cases.
 * 
 * @param list Pointer to the list control structure
 * @param node_val Value to store in the new node
 */
void push_node(IntList* list, int node_val) {
    /* Allocate and initialize new node */
    IntNode* node = malloc(sizeof(IntNode));
    node->value = node_val;
    node->next = NULL;

    /* Handle empty list case */
    if (list->head == NULL) {
        list->head = node;
    } else {
        /* Append to existing list */
        list->tail->next = node;
    }
    list->tail = node;
}

/**
 * Simple node printing function.
 * Can be passed as a NodeFn function pointer.
 * 
 * @param node Pointer to the node to print
 */
void print_node(IntNode* node) {
    printf("Node value: %d\n", node->value);
}

/**
 * Recursively walks the list, applying the provided function to each node.
 * 
 * @param node Starting node for the walk
 * @param pfn Function to apply to each node
 */
void walk_and_print_list(IntNode* node, NodeFn nfn) {
    /* Process current node */
    nfn(node);
    
    /* Recursively process remaining nodes */
    if (node->next != NULL) {
        walk_and_print_list(node->next, nfn);
    }
}

/**
 * Example function demonstrating how heap-allocated nodes
 * persist beyond function scope.
 * 
 * @param list Pointer to the list to modify
 */
void some_fn(IntList* list) {
    /* Simulate some work and generate a result */
    int result = 50;
    
    /* Add result to list - node persists after function returns */
    push_node(list, result);
}

/**
 * Example usage of the linked list implementation.
 */
int main(void) {
    /* Initialize empty list */
    IntList numbers = {NULL, NULL};
    
    /* Add some numbers to the list */
    push_node(&numbers, 5);
    push_node(&numbers, 10);
    push_node(&numbers, 20);
    push_node(&numbers, 40);
    
    /* Demonstrate function scope and heap allocation */
    some_fn(&numbers);
    
    /* Walk and print the entire list */
    walk_and_print_list(numbers.head, print_node);

    /* Memory cleanup would go here */
    return 0;
}
