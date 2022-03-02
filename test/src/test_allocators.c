#define CLOVE_SUITE_NAME geg_allocators_test
#include "clove.h"
#include "geg_allocators.h"
#include "mem_functions.h"

CLOVE_TEST(fmem_default_init)
{
    geg_object_allocator_t allocator = init_allocator();

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NOT_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, malloc);
    CLOVE_PTR_EQ(allocator.f_realloc, realloc);
    CLOVE_PTR_EQ(allocator.f_free, free);
}

CLOVE_TEST(fmem_custom_init)
{
    geg_object_allocator_t allocator = init_allocator_custom3(bad_malloc_func, bad_realloc_func, bad_free_func);

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NOT_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, bad_malloc_func);
    CLOVE_PTR_EQ(allocator.f_realloc, bad_realloc_func);
    CLOVE_PTR_EQ(allocator.f_free, bad_free_func);
}

CLOVE_TEST(fmem_custom_init_all_null)
{
    void *a = NULL;
    geg_object_allocator_t allocator = init_allocator_custom3(a, a, a);

    CLOVE_NULL(allocator.f_malloc);
    CLOVE_NULL(allocator.f_realloc);
    CLOVE_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, a);
    CLOVE_PTR_EQ(allocator.f_realloc, a);
    CLOVE_PTR_EQ(allocator.f_free, a);
}

CLOVE_TEST(fmem_custom_init_mix_funcs)
{
    geg_object_allocator_t allocator = init_allocator_custom3(malloc, bad_realloc_func, NULL);

    CLOVE_NOT_NULL(allocator.f_malloc);
    CLOVE_NOT_NULL(allocator.f_realloc);
    CLOVE_NULL(allocator.f_free);

    CLOVE_PTR_EQ(allocator.f_malloc, malloc);
    CLOVE_PTR_EQ(allocator.f_realloc, bad_realloc_func);
    CLOVE_PTR_EQ(allocator.f_free, NULL);
}

CLOVE_TEST(fmem_change_1st_mem_function)
{
    geg_object_allocator_t allocator = init_allocator();

    int result = init_allocator_by_index(0, bad_free_func, &allocator);

    CLOVE_INT_EQ(0, result);
    CLOVE_PTR_EQ(allocator.f_malloc, bad_free_func);
}

CLOVE_TEST(fmem_change_2nd_mem_function)
{
    geg_object_allocator_t allocator = init_allocator();

    init_allocator_by_index(1, bad_free_func, &allocator);

    CLOVE_PTR_EQ(allocator.f_realloc, bad_free_func);
}

CLOVE_TEST(fmem_change_3rd_mem_function)
{
    geg_object_allocator_t allocator = init_allocator();

    init_allocator_by_index(2, bad_free_func, &allocator);

    CLOVE_PTR_EQ(allocator.f_free, bad_free_func);
}

CLOVE_TEST(fmem_change_1st_mem_function_NULL)
{
    geg_object_allocator_t allocator = init_allocator();

    init_allocator_by_index(0, NULL, &allocator);

    CLOVE_PTR_EQ(allocator.f_malloc, NULL);
}

CLOVE_TEST(fmem_change_mem_function_out_index)
{
    geg_object_allocator_t allocator = init_allocator();

    int result = init_allocator_by_index(4, bad_free_func, &allocator);

    CLOVE_INT_EQ(-1, result);
    CLOVE_PTR_EQ(allocator.f_malloc, malloc);
}

// CLOVE_TEST(delete_init_allocator)
// {
//     geg_object_allocator_t allocator = init_allocator();

//     // void* allocator_ptr_before_delete = &allocator;

//     int result = delete_allocator(&allocator);

//     // void* allocator_ptr_after_delete = &allocator;

//     CLOVE_INT_EQ(0, allocator.size);
//     CLOVE_INT_EQ(0, result);

//     // CLOVE_PTR_EQ(allocator.f_malloc, NULL);
//     // CLOVE_PTR_EQ(allocator.f_realloc, NULL);
//     // CLOVE_PTR_EQ(allocator.f_free, NULL);
//     // CLOVE_PTR_EQ(&allocator, NULL);
//     // CLOVE_PTR_NE(allocator_ptr_before_delete, allocator_ptr_after_delete);
// }

// CLOVE_TEST(delete_null_allocator)
// {
//     geg_object_allocator_t allocator;

//     int result = delete_allocator(&allocator);

//     CLOVE_INT_EQ(0, allocator.size);
//     CLOVE_INT_EQ(0, result);
//     CLOVE_NULL(&allocator);
// }