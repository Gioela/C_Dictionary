#pragma once
#include "geg_node.h"

/*
 * Double Linked List. This is the dict element corresponding to a specific key
 *
 */
typedef struct _geg_dbl_value
{
    geg_nodes_t nodes;
    size_t value;
} geg_dbl_value_t;

/*
 * Initialize new geg_dbl_value_t item
 *
 * @param value Value to associate to new geg_dbl_value_t element
 * 
 * @return if success returns the pointer to geg_dbl_value_t structure with size_t value; NULL otherwise
 */
geg_dbl_value_t *geg_dbl_init_item(const size_t *value);

/*
 * Add item to the end of the head geg_dbl_value_t list
 *
 * @param head Head of the dbl_list where item must be added
 * @param item Item which want to append at the end of geg_sbl_value_t list
 * 
 * @return Return 0 if success -1 otherwise
 */
int geg_dbl_append_item(geg_dbl_value_t **head, geg_dbl_value_t *item);

/*
 * Create new geg_dbl_value_t item with given value and add it to the tail of
 * the head dbl_list
 *
 * @param head Head of the dbl_list where item must be added
 * @param value Value to associate to the last new element of head dbl_list
 * 
 * @return Return 0 if success -1 otherwise
 */
int geg_dbl_append_value(geg_dbl_value_t **head, size_t *value);
