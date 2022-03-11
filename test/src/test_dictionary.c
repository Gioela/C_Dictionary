#define CLOVE_SUITE_NAME geg_dictionary_test_char_key
#include <stdio.h>
#include "clove.h"
#include "geg_dictionary.h"

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

CLOVE_TEST(add_key_to_dict)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";

    int res = geg_add_key(dict, k_1, sizeof(k_1));

    CLOVE_INT_EQ(0, res);
    CLOVE_INT_EQ(1, dict->num_keys);
}

CLOVE_TEST(add_same_key_to_dict)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";
    const char *k_2 = "K_001";

    int res = geg_add_key(dict, k_1, sizeof(k_1));
    res = geg_add_key(dict, k_2, sizeof(k_2));
    
    CLOVE_INT_EQ(-1, res);
    CLOVE_INT_EQ(1, dict->num_keys);
}

CLOVE_TEST(add_2diff_keys_to_dict)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";
    const char *k_2 = "K_002";

    int res = geg_add_key(dict, k_1, sizeof(k_1));
    res = geg_add_key(dict, k_2, sizeof(k_2));
    
    CLOVE_INT_EQ(0, res);
    CLOVE_INT_EQ(2, dict->num_keys);
}

CLOVE_TEST(add_5diff_keys_to_dict)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";
    const char *k_2 = "K_002";
    const char *k_3 = "K_003";
    const char *k_4 = "K_004";
    const char *k_5 = "K_005";
    const char *k_6 = "K_006";
    const char *k_7 = "K_007";

    int res = geg_add_key(dict, k_1, sizeof(k_1));
    res = geg_add_key(dict, k_2, sizeof(k_2));
    res = geg_add_key(dict, k_3, sizeof(k_3));
    res = geg_add_key(dict, k_4, sizeof(k_4));
    res = geg_add_key(dict, k_5, sizeof(k_5));
    
    CLOVE_INT_EQ(0, res);
    CLOVE_INT_EQ(5, dict->num_keys);
}

CLOVE_TEST(add_same_time_key_value)
{
    geg_dictionary_t *dict = geg_new_dict();

    const char *k_1 = "K_001";
    // const char *v_1 = "K.01_V.01";
    int v_1 = 13;

    // int res = geg_add_key(dict, k_1, sizeof(k_1));
    int result = geg_add_key_value(dict, k_1, sizeof(k_1), v_1);

    CLOVE_INT_EQ(0, result);

    size_t hash = djb33x_hash( k_1, sizeof(k_1));
    size_t index = hash % dict->hashmap_size;
    printf("value of k.%s is %s\n", k_1, (char *)&dict->keys[index]->values->value);
    // CLOVE_INT_EQ(v_1, (dict->keys[k_1]) );

}