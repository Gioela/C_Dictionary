#include "mem_functions.h"

void *bad_malloc_func(size_t value)
{
    return NULL;
}

void *bad_realloc_func(void *block_mem, size_t value)
{
    return NULL;
}

void *bad_free_func(void *block_mem)
{
    return NULL;
}