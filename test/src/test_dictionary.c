#define CLOVE_SUITE_NAME geg_dictionary_test
#include <stdio.h>
#include "clove.h"
#include "geg_dictionary.h"
#include "geg_allocators.h"
#include "mem_functions.h"

CLOVE_TEST(init_dict_default)
{
    geg_dictionary_t *dict = geg_new_dict();

    CLOVE_NOT_NULL(dict);
    CLOVE_NOT_NULL(&(dict->allocators));
    CLOVE_NOT_NULL(dict->keys);
    CLOVE_INT_EQ(4, dict->hashmap_size);
    CLOVE_INT_EQ(0, dict->num_keys);
}

CLOVE_TEST(init_dict_hashmap)
{
    geg_dictionary_t *dict = geg_new_dict_with_hashsize(10);

    CLOVE_NOT_NULL(dict);
    CLOVE_NOT_NULL(&(dict->allocators));
    CLOVE_NOT_NULL(dict->keys);
    CLOVE_INT_EQ(10, dict->hashmap_size);
    CLOVE_INT_EQ(0, dict->num_keys);
}

CLOVE_TEST(init_dict_hashmap_allocators)
{
    // geg_object_allocator_t cst_allocator = {bad_malloc_func, bad_realloc_func, bad_free_func};

    // geg_dictionary_t *dict = geg_new_dict_ha(10, &cst_allocator);

    // CLOVE_NOT_NULL(dict);
    // CLOVE_PTR_EQ(&(dict->allocators), &cst_allocator);
    // CLOVE_NOT_NULL(dict->keys);
    // CLOVE_INT_EQ(10, dict->hashmap_size);
    // CLOVE_INT_EQ(0, dict->num_keys);
}

CLOVE_TEST(add_key_to_dict)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";

    geg_key_t *k_001 = geg_add_key(dict, &k_1, 5, "test");
    // geg_add_key(dict, "K_001", 5, "test");
    // geg_test_add_key();

    CLOVE_PTR_EQ(k_001, k_1);
}