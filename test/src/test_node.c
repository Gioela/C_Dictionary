#define CLOVE_SUITE_NAME geg_node_test
#include <stdio.h>
#include "clove.h"
#include "geg_node.h"

CLOVE_TEST(a1_create_node_test)
{
    geg_nodes_t *node_01 = NULL;
    int result = geg_node_init(node_01);

    CLOVE_INT_EQ(0, result);
    CLOVE_PTR_EQ(node_01->prev, NULL);
    CLOVE_PTR_EQ(node_01->next, NULL);
}

CLOVE_TEST(a2_append_2node_test)
{
    geg_nodes_t *node_01 = NULL;
    geg_nodes_t *node_02 = NULL;
    geg_node_init(node_01);
    geg_node_init(node_02);
    // geg_nodes_t *node_03 = geg_node_append(node_01, node_02);

    // printf("node_01 mem_id: %llu\n", &node_01);
    // printf("node_01 PREV: %llu\n", &node_01->prev);
    // printf("node_01 NEXT: %llu\n", &node_01->next);

    // printf("node_02 mem_id: %llu\n", &node_02);
    // printf("node_02 PREV: %llu\n", &node_02->prev);
    // printf("node_02 NEXT: %llu\n", &node_02->next);
}

CLOVE_TEST(a3_get_tail_3node_test)
{
    geg_nodes_t *node_01 = NULL;
    geg_nodes_t *node_02 = NULL;
    geg_nodes_t *node_03 = NULL;
    geg_node_init(node_01);
    geg_node_init(node_02);
    geg_node_init(node_03);
    // geg_nodes_t *node_04 = geg_node_append(node_01, node_02);
    // geg_nodes_t *node_05 = geg_node_append(node_01, node_03);

    // geg_nodes_t *tail = geg_node_tail(node_01);
    
    // CLOVE_PTR_EQ(tail, node_03);

}