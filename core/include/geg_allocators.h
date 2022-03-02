#pragma once
#include <stdlib.h>

/*
 * Struct wich specify the malloc, realloc and free functions
 */
typedef struct _geg_allocator
{
    void *(*f_malloc)(size_t);
    void *(*f_realloc)(void *, size_t);
    void *(*f_free)(void *);
    int size;
} geg_object_allocator_t;

/*
 * Initialize new allocator type with default memory functions
 *
 * @return Returns new allocator type with default malloc, realloc, free functions
 */
geg_object_allocator_t init_allocator();

/*
 * Initialize new allocator type with custom memory functions
 *
 * @param f_malloc The malloc function. It takes the memory size to instantiate (block)
 * @param f_realloc The realloc function. It takes the block of memory and the size of new memory
 * @param f_free The free function. It takes the memory size to be free (block)
 *
 * @return Returns new allocator type
 */
geg_object_allocator_t init_allocator_custom3(void *(*f_malloc)(size_t), void *(*f_realloc)(void *, size_t), void *(*f_free)(void *));

/*
 * Initialize or change the memory function allocator
 *
 * @param index Function index which want to init or change
 * @param f_mem The memory function which want to
 * @param allocator The allocator_obj on which the memory function must be specify
 *
 * @return Returns 0 if success, -1 otherwise
 */
int init_allocator_by_index(int index, void *(*f_mem)(void*), geg_object_allocator_t *allocator);

/*
 * Nullify the allocator pointers function and free its memory
 *
 * @param allocator The allocator object which want to delete
 * 
 * @return Return 0 if success; -1 otherwise
 */
int delete_allocator(geg_object_allocator_t *allocator);