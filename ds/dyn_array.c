/*
 * Generic Dynamic Array Implementation in C
 * 
 * This file demonstrates how to implement a generic (type-agnostic) dynamic array in C
 * using void pointers and manual memory management. The implementation supports:
 *
 * - Creating arrays that can store any data type
 * - Automatic capacity management with doubling strategy
 * - Adding elements (push)
 * - Removing elements (pop)
 * - Accessing elements with proper type casting
 *
 * The example uses a User struct to show how to store complex types in the array.
 * Key concepts demonstrated:
 * - void pointer usage for type-agnostic storage
 * - Pointer arithmetic with byte-level precision using char* casting
 * - Memory reallocation strategy
 * - Proper struct copying with memcpy
 * - Error handling with status codes
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Simple user structure to demonstrate storing complex types.
 * The fixed-size character array avoids dynamic memory allocation
 * for the name, simplifying memory management.
 */
typedef struct {
    char name[50];  /* Fixed-size array for name storage */
    short id;       /* Unique identifier */
} User;

/**
 * Generic dynamic array structure.
 * Uses void pointer to store elements of any type.
 */
typedef struct {
    void* items;    /* Pointer to the contiguous block of memory */
    size_t count;   /* Number of elements currently stored */
    size_t cap;     /* Current capacity (in number of elements) */
    size_t size;    /* Size of each element in bytes */
} DynArray;

/**
 * Creates a new dynamic array for elements of the specified size.
 * 
 * @param size Size of each element in bytes (use sizeof())
 * @return Pointer to newly allocated dynamic array
 */
DynArray* new_dyn_array(size_t size) {
    /* Allocate the array control structure */
    DynArray* array = malloc(sizeof(DynArray));
    
    /* Initialize with default values */
    array->count = 0;
    array->cap = 2;         /* Start with small capacity */
    array->size = size;
    
    /* Allocate initial memory block for items */
    array->items = malloc(array->size * array->cap);
    
    return array;
}

/**
 * Adds an element to the dynamic array, handling resizing if needed.
 * Uses memcpy to properly copy the element's bytes.
 * 
 * @param array Pointer to the dynamic array
 * @param val Pointer to the element to add (can be any type)
 */
void push_dyn_array(DynArray* array, void* val) {
    /* Check if we need to resize */
    if(array->count >= array->cap) {
        /* Double the capacity */
        array->cap *= 2;
        
        /* Calculate new memory block size in bytes */
        size_t new_size = array->cap * array->size;
        
        /* Allocate new, larger memory block */
        void* new_items = malloc(new_size);
        
        /* Copy existing elements to new memory block */
        memcpy(new_items, array->items, array->size * array->count);
        
        /* Free the old memory block */
        free(array->items);
        
        /* Update items pointer to new memory block */
        array->items = new_items;
    }
    
    /* Calculate destination address for new element
     * We cast to char* to get byte-level pointer arithmetic */
    void* dest = (char*)array->items + array->size * array->count;
    
    /* Copy the element's bytes to the array */
    memcpy(dest, val, array->size);
    
    /* Increment element count */
    array->count++;
}

/**
 * Removes and returns the last element from the dynamic array.
 * 
 * @param array Pointer to the dynamic array
 * @param out_val Optional pointer where the popped value will be copied
 * @return 1 on success, 0 if array is empty
 */
/**
 * Removes and returns the last element from the dynamic array.
 * 
 * @param array Pointer to the dynamic array
 * @param out_val Optional pointer where the popped value will be copied
 * @return 1 on success, 0 if array is empty
 */
int pop_dyn_array(DynArray* array, void* popped) {
    /* Check if the array is empty */
    if (array->count == 0) {
        return 0;
    }

    void* src = (char*)array->items + ((array->count - 1) * array->size);
    memcpy(popped, src, array->size);

    /* It's sufficient to just decrement the count.
     * On the next push, the popped item will be overwritten */
    array->count--;
    return 1;
}

/**
 * Prints all users in the array.
 * This is a type-specific function that knows how to interpret the bytes
 * as User structures.
 * 
 * @param array Pointer to dynamic array containing User elements
 */
void print_user_array(DynArray* array) {
    for (size_t i = 0; i < array->count; ++i) {
        /* Calculate pointer to the i-th element
         * We cast to char* for byte-precise pointer arithmetic,
         * then cast result to User* to access fields */
        User* user = (User*)((char*)array->items + (array->size * i));
        
        /* Print the user's information */
        printf("Index: [%zu], name: %s, id: %d\n", i, user->name, user->id);
    }
}

/**
 * Example usage of the generic dynamic array with User elements.
 */
int main(void) {
    /* Create some sample users */
    User user1 = {"meg", 1};    
    User user2 = {"bobo", 2};    
    User user3 = {"rigby", 3};    
    
    /* Create dynamic array sized for User elements */
    DynArray* array = new_dyn_array(sizeof(User));
    
    /* Add the users to the array */
    push_dyn_array(array, &user1);
    push_dyn_array(array, &user2);
    push_dyn_array(array, &user3);
    
    /* Print the array contents */
    print_user_array(array);

    /* Pop from array and print the popped User */
    User popped_user;
    pop_dyn_array(array, &popped_user);
    printf("Popped User - name: %s, id: %d\n", popped_user.name, popped_user.id);
    
    /* Clean-up would go here (free array) */ return 0;
}
