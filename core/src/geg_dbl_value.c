#include <stdio.h>
#include <string.h>
#include "geg_dbl_value.h"
#include "geg_node.h"

geg_dbl_value_t *geg_dbl_init_item(const size_t *value)
{
    geg_dbl_value_t *item = malloc(sizeof (geg_dbl_value_t));
    if (!item)
    {
        return NULL;
    }

    // init item nodes to NULL
    int result_node_init = geg_node_init(item->nodes);
    if (result_node_init != 0)
    {
        return NULL;
    }
    
    item->value = *value;
    return item;
}

int geg_dbl_append_item(geg_dbl_value_t **head, geg_dbl_value_t *item)
{
    // if item is NULL return error
    if (!item)
    {
        return -1;
    }
    
    // get tail of head to append item
    // NOTE: cast head to geg_node_t to evaluate only nodes
    geg_dbl_value_t *tail = (geg_dbl_value_t *) geg_node_tail( (geg_nodes_t*)*head);

    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->nodes.next = item->nodes.prev;
        
    }

    printf("\ntest...\n");
    return 0;
}

int geg_dbl_append_value(geg_dbl_value_t **head, size_t *value)
{
    if (!value)
    {
        return -1;
    }
    
    geg_dbl_value_t *item = geg_dbl_init_item(value);

    int result = geg_dbl_append_item(head, item);

    return result;
}