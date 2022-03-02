#pragma once
#include <stdlib.h>

void *bad_malloc_func(size_t value);

void *bad_realloc_func(void *block_mem, size_t value);

void *bad_free_func(void *block_mem);