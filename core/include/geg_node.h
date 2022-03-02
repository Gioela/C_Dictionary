#pragma once
#include <stdlib.h>

/*
 * Simple node with pointer to previous and follow nodes
 *
 */
typedef struct _geg_nodes
{
    struct _geg_nodes *prev;
    struct _geg_nodes *next;
} geg_nodes_t;

/*
 * Initialize new node
 *
 * @param node Node to init
 * 
 * @return 0 Returns 0 if success; -1 otherwise
 */
int _geg_node_init_core(geg_nodes_t **node);
#define geg_node_init(node) _geg_node_init_core((geg_nodes_t **)&node);

geg_nodes_t *_geg_node_get_tail(const geg_nodes_t **head);
#define geg_node_tail(head) _geg_node_get_tail((geg_nodes_t **)&head);

geg_nodes_t *_geg_node_append_core(geg_nodes_t **head, geg_nodes_t *node);
#define geg_node_append(head, node) _geg_node_append_core((geg_nodes_t **)&head, (geg_nodes_t *)&node);
