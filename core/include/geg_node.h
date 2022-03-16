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
 * Initialize new node structure
 *
 * @param node Node to init
 * 
 * @return 0 Returns 0 if success; -1 otherwise
 */
int _geg_node_init_core(geg_nodes_t **node);
#define geg_node_init(node) _geg_node_init_core((geg_nodes_t **)&node);

/*
 * Get the last node of the given head geg_node_t list
 *
 * @param head Double pointer which points to the head of the geg_nodes_t node
 * 
 * @return If success, returns the tail of the geg_nodes_t element with given head.
 * Otherwise returns NULL.
 */
geg_nodes_t *_geg_node_get_tail(const geg_nodes_t **head);
#define geg_node_tail(head) _geg_node_get_tail((geg_nodes_t **)&head);

/*
 * Append the given geg_nodes_t struct at the end of the geg_nodes_t head element
 *
 * @param head Head of the geg_nodes_t list elements
 * @param node Element which want to append at the end of the list of head geg_nodes_t
 * 
 * @return In case of success, it returns the pointer to the added geg_nodes_t node,
 * otherwise it returns NULL.
 */
geg_nodes_t *_geg_node_append_core(geg_nodes_t **head, geg_nodes_t *node);
#define geg_node_append(head, node) _geg_node_append_core((geg_nodes_t **)&head, (geg_nodes_t *)&node);
