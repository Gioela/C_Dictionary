#pragma once
#include <stdlib.h>
#include "geg_allocators.h"
#include "geg_node.h"

typedef struct _geg_list_values
{
    size_t value; 
    const geg_nodes_t *nodes;
} geg_list_values_t;

/*
 * Set of unique dictionary key.
 */
typedef struct _geg_key
{
    unsigned int num_values; 
    char *key_value;
    size_t key_length;
    geg_list_values_t *values;
} geg_key_t;

/*
 * Custom Dictionary Datastructure
 *
 */
typedef struct _geg_dictionary
{
    unsigned int num_keys;
    size_t hashmap_size;
    geg_key_t **keys;
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
 * Initialize a new geg_dictionary item with default properties
 *
 * @return Pointer to memory where new geg_dictionary object is instantiated
 */
geg_dictionary_t *geg_new_dict();

/*
 * Initialize a new geg_dictionary item with given hashmap size
 *
 * @param hashmap_size The hashmap size indica il numero di elementi previsti.
 *  Al raggiungimento del limite viene incrementato automaticamente.
 * 
 * @return Pointer to memory where new geg_dictionary object is instantiated
 */
geg_dictionary_t *geg_new_dict_with_hashsize(const size_t hashmap_size);

/*
 * Add key to keys set in dictionary.
 *
 * @param dict Dictionary where add key
 * @param key Key value to add
 * @param key_len Size of the key
 * 
 * @return Returns 0 if success; -1 otherwise (also if key is duplicated)
 */
int geg_add_key(geg_dictionary_t *dict, const char *key, const size_t key_len);

/*
 * Add value to tail of given key.
 * If key doesn't exist in dictionary, before add its and after associate value
 *
 * @param dict Dictionary where search key and add value
 * @param key Dictionary's key where add value
 * @param key_len Size of the key
 * @param value Value to add to the value's tail 
 * 
 * @return Returns 0 if success; -1 otherwise
 */
int geg_add_key_value(geg_dictionary_t *dict, const char *key, const size_t key_len, size_t *value);

// geg_key_t *geg_add_key(geg_dictionary_t *dict, const size_t *key, const size_t key_len, const size_t *value);
// geg_key_t *add_value2key(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);
// geg_key_t *add_node(geg_dictionary_t *table, const char *key, const size_t key_len, const char *value);
// geg_dictionary_t *set_table_search(geg_dictionary_t *table, const char *key, const size_t key_len);
// geg_dictionary_t *set_table_remove(geg_dictionary_t *table, const char *key, const size_t key_len);
// int set_table_clear(geg_dictionary_t *table);
// int increase_hashmapsize(geg_dictionary_t **table);