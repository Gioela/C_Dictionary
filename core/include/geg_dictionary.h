#pragma once
#include <stdlib.h>

/*
 * Struct wich specify the malloc, realloc and free functions
 */
typedef struct _geg_allocator
{
    void *(*f_malloc)(size_t);
    void *(*f_realloc)(void *, size_t);
    void *(*f_free)(void *);
} geg_object_allocator_t;

/*
 * List of nodes
 *
 */
typedef struct _geg_nodes
{
    struct _geg_nodes *prev;
    struct _geg_nodes *next;
} geg_nodes_t;

/*
 * List of values
 *
 */
typedef struct _geg_values
{
    size_t value;
    struct geg_nodes_t *nodes;
} geg_values_list_t;

/*
 * Set of unique dictionary key.
 */
typedef struct _geg_key_set
{
    size_t key_value;
    struct geg_node_t *nodes;
    struct geg_values_list_t **values;

} geg_key_t;

/*
 * Custom dictionary implementation
 */
typedef struct _geg_dictionary_table
{
    size_t hashmap_size;
    unsigned int key_len;
    geg_key_t key_set;
    geg_object_allocator_t allocators;
} geg_dictionary_t;

/*
 * Given key and its length, calculate the djb33x hash
 *
 * @param key The hash key
 * @param keylen The length of the key. How many elements define the key
 *
 * @return Returns the calculated hash
 */
size_t djb33x_hash(const char *key, const size_t keylen);

/*
 * Initialize new allocator type
 *
 * @param f_malloc The malloc function. It takes the memory size to instantiate (block)
 * @param f_realloc The realloc function. It takes the block of memory and the size of new memory
 * @param f_free The free function. It takes the memory size to be free (block)
 *
 * @return Returns new allocator type
 */
geg_object_allocator_t init_allocator(void *(*f_malloc)(size_t), void *(*f_realloc)(void *, size_t), void *(*f_free)(void *));

/*
 * Initialize a new geg_dictionary item with default properties
 *
 */
geg_dictionary_t *new_dict();

/*
 * Initialize a new geg_dictionary item with given hashmap size
 *
 * @param hashmap_size The hashmap size indica il numero di elementi previsti. Al raggiungimento del limite viene incrementato automaticamente.
 */
geg_dictionary_t *new_dict_with_hashsize(const size_t hashmap_size);

/*
 * Initialize a new geg_dictionary item with given hashmap size and allocator type
 *
 * @param hashmap_size The hashmap size indica il numero di elementi previsti. Al raggiungimento del limite viene incrementato automaticamente.
 * @param allocator
 */
geg_dictionary_t *new_dict_with_hashsize_allocator(const size_t hashmap_size, geg_object_allocator_t *allocators);

geg_key_t *add_key(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);
geg_key_t *add_key_value(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);
geg_key_t *add_value2key(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);

geg_key_t *add_node(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);
geg_dictionary_t *set_table_search(geg_dictionary_t *table, const char *key, const size_t key_len);
geg_dictionary_t *set_table_remove(geg_dictionary_t *table, const char *key, const size_t key_len);
int set_table_clear(geg_dictionary_t *table);

int increase_hashmapsize(geg_dictionary_t **table);