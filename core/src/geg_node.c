#include <stdio.h>
#include <stdlib.h> // required for malloc
#include "geg_node.h"

int _geg_node_init_core(geg_nodes_t **node)
{
    geg_nodes_t *_node = (geg_nodes_t *)malloc(sizeof(geg_nodes_t));

    if (!_node)
    {
        return -1;
    }

    _node->prev = NULL;
    _node->next = NULL;

    *node = _node;

    return 0;
}

geg_nodes_t *_geg_node_get_tail(const geg_nodes_t **head)
{
    geg_nodes_t *current_node = *head;
    geg_nodes_t *tail = NULL;

    while (current_node)
    {
        tail = current_node;
        current_node = current_node->next;
    }

    printf("tail node: %llu", *tail);

    return tail;
}

geg_nodes_t *_geg_node_append_core(geg_nodes_t **head, geg_nodes_t *node)
{
    geg_nodes_t *tail = geg_node_tail(head);
    if (!tail)
    {
        *head = node;
    }
    else
    {
        tail->next = node;
    }
    node->prev = tail;
    node->next = NULL;
    return node;
}