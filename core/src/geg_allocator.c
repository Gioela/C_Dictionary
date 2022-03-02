#include <string.h>
#include <stdlib.h> // required for malloc
#include "geg_allocators.h"

geg_object_allocator_t init_allocator()
{
    // geg_object_allocator_t allocators = {malloc, realloc, free};
    // return allocators;

    return init_allocator_custom3(malloc, realloc, free);
}

geg_object_allocator_t init_allocator_custom3(void *(*f_malloc)(size_t), void *(*f_realloc)(void *, size_t), void *(*f_free)(void*))
{
    geg_object_allocator_t allocators = {f_malloc, f_realloc, f_free};
    allocators.size = 3;

    return allocators;
}

int init_allocator_by_index(int index, void *(*f_mem)(void*), geg_object_allocator_t *allocator)
{
    if (!allocator || index > allocator->size)
    {
        return -1;
    }
    
    if (index == 0)
    {
        allocator->f_malloc = f_mem;
    }
    else if (index == 1)
    {
        allocator->f_realloc = f_mem;
    }
    else
    {
        allocator->f_free = f_mem;
    }
    
    return 0;
}


int delete_allocator(geg_object_allocator_t *allocator)
{
    if (!allocator)
    {
        return -1;
    }
    
    allocator->f_malloc = NULL;
    allocator->f_realloc = NULL;
    allocator->f_free = NULL;
    allocator->size = 0;

    free(allocator);

    return 0;
}