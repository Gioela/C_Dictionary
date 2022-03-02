#pragma once
#include "geg_node.h"

/*
 * Double Linked List. This is the dict element corresponding to a specific key
 *
 */
typedef struct _geg_dbl_value
{
    size_t value;
    struct geg_nodes_t *nodes;
} geg_dbl_value_t;

