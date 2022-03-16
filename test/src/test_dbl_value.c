#define CLOVE_SUITE_NAME geg_dbl_value_test
// #include <stdio.h>
#include "clove.h"
#include "geg_dbl_value.h"

CLOVE_TEST(init_dbl_with_size_t_value_NULL)
{
    size_t *item_01 = NULL;
    geg_dbl_value_t *result = geg_dbl_init_item(item_01);

    CLOVE_NULL(result);
}

CLOVE_TEST(init_dbl_with_char_value_NULL)
{
    char *item_01 = NULL;
    printf("1. item_01: %s\n", item_01);
    printf("1. item_01: %llu\n", item_01);
    printf("2. &item_01: %llu\n", &item_01);
    printf("3. (size_t *)&item_01: %llu\n", (size_t *)&item_01);
    printf("4. (size_t *)item_01: %llu\n", (size_t *)item_01);
    geg_dbl_value_t *result = geg_dbl_init_item( (size_t *)item_01);
    CLOVE_NULL(result);
}


CLOVE_TEST(init_dbl_with_value_CHAR)
{
    char *item_01 = "value_01";
    // int item_01 = 13;
    geg_dbl_value_t *result = geg_dbl_init_item((size_t *)item_01);

    CLOVE_NOT_NULL(result);
    CLOVE_NULL(result->nodes.prev);
    CLOVE_NULL(result->nodes.next);

    char *value = (char*)result->value;
    printf("value is %s\n", value);
    // CLOVE_CHAR_EQ(item_01, (char *)&result->value);
}

CLOVE_TEST(init_dbl_with_value_INT)
{
    int item_01 = 13;
    geg_dbl_value_t *result = geg_dbl_init_item((size_t *)&item_01);

    CLOVE_NOT_NULL(result);
    CLOVE_NULL(result->nodes.prev);
    CLOVE_NULL(result->nodes.next);

    char *value = (char*)result->value;
    printf("value is %d\n", value);
    CLOVE_INT_EQ(item_01, result->value);
}

CLOVE_TEST(dbl_NULL_append_size_t_value_NULL)
{
    size_t *item_01 = NULL;
    int result = geg_dbl_append_value(NULL, item_01);

    CLOVE_INT_EQ(-1, result);
}

CLOVE_TEST(dbl_NULL_append_char_value_NULL)
{
    char *item_01 = NULL;
    int result = geg_dbl_append_value(NULL, (size_t *)item_01);

    CLOVE_INT_EQ(-1, result);
}


CLOVE_TEST(dbl_head_append_value_NULL)
{
    // TODO create new geg_dbl_value_t element to be head of the list

    char *item_01 = NULL;
    // int result = geg_dbl_append_value(NULL, (size_t *)&item_01);

    // CLOVE_INT_EQ(-1, result);
}