#define CLOVE_SUITE_NAME geg_allocators_test
#include "clove.h"
#include "geg_dictionary.h"

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

CLOVE_TEST(geg_allocator_initialization)
{
    geg_object_allocator_t allocator = init_allocator(malloc, realloc, free);

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NOT_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, malloc);
    CLOVE_PTR_EQ(allocator.f_realloc, realloc);
    CLOVE_PTR_EQ(allocator.f_free, free);
}

CLOVE_TEST(geg_allocator_initialization_bad_funcs)
{
    geg_object_allocator_t allocator = init_allocator(bad_malloc_func, bad_realloc_func, bad_free_func);

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NOT_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, bad_malloc_func);
    CLOVE_PTR_EQ(allocator.f_realloc, bad_realloc_func);
    CLOVE_PTR_EQ(allocator.f_free, bad_free_func);
}

CLOVE_TEST(geg_allocator_all_null)
{
    void *a = NULL;
    geg_object_allocator_t allocator = init_allocator(a, a, a);

    CLOVE_NULL(allocator.f_malloc);
    CLOVE_NULL(allocator.f_realloc);
    CLOVE_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, a);
    CLOVE_PTR_EQ(allocator.f_realloc, a);
    CLOVE_PTR_EQ(allocator.f_free, a);
}

CLOVE_TEST(geg_allocator_initialization_mix_funcs)
{
    geg_object_allocator_t allocator = init_allocator(malloc, bad_realloc_func, NULL);

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, malloc);
    CLOVE_PTR_EQ(allocator.f_realloc, bad_realloc_func);
    CLOVE_PTR_EQ(allocator.f_free, NULL);
}