#include <string.h>
#include "geg_dictionary.h"

size_t djb33x_hash(const char *key, const size_t key_len)
{
    size_t hash = 5381;

    for (size_t i = 0; i < key_len; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

geg_dictionary_t *geg_new_dict()
{
    return geg_new_dict_with_hashsize(4);
}

geg_dictionary_t *geg_new_dict_with_hashsize(const size_t hashmap_size)
{
    geg_object_allocator_t allocators = init_allocator();

    geg_dictionary_t *dict = (geg_dictionary_t *)allocators.f_malloc(sizeof(geg_dictionary_t));
    if (!dict)
    {
        return NULL;
    }

    // dict->keys = (geg_key_t *)calloc(dict->hashmap_size, sizeof(geg_key_t));
    dict->keys = (geg_key_t *)allocators.f_malloc(sizeof(geg_key_t));
    if (!dict->keys)
    {
        free(dict);
        return NULL;
    }

    dict->allocators = allocators;
    dict->hashmap_size = hashmap_size;
    dict->num_keys = 0;

    printf("size dict %llu - mem addr %llu\n", sizeof(dict), *dict);

    // TODO ? init sub structures with pre alloc memory for first 4 elements
    // dict->keys[0]->num_values = 0;

    return dict;

    // return geg_new_dict_ha(hashmap_size, &allocators);
}

geg_dictionary_t *_geg_new_dict_with_hashsize_allocator(const size_t hashmap_size, geg_object_allocator_t *allocators)
{
    geg_dictionary_t *dict = (geg_dictionary_t *)(*allocators).f_malloc(sizeof(geg_dictionary_t));
    puts("TEST_01");
    // dict->allocators = *((geg_object_allocator_t *) (*allocators).f_malloc(sizeof(allocators)));
    // dict->allocators = *allocators;
    dict->allocators = *allocators;
    puts("TEST_02");
    dict->hashmap_size = hashmap_size;
    puts("TEST_03");
    dict->keys = calloc(dict->hashmap_size, sizeof(geg_key_t));
    puts("TEST_04");
    dict->num_keys = 0;

    return dict;
}

geg_key_t *geg_add_key(geg_dictionary_t *dict, const size_t *key, const size_t key_len, size_t *value)
{
    if (!dict)
    {
        return NULL;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    geg_key_t *new_key = dict->keys[index];
    printf("index: %llu - new_key: %llu\n", index, new_key);

    // if new_key is NULL --> index of new key is out of bounds so it's necessary
    //                      allocated new space for this new index (with its objects and values)
    if (!new_key)
    {
        dict->keys[index] = (geg_key_t *)dict->allocators.f_malloc(sizeof(geg_key_t));
        if (!dict->keys[index])
        {
            return NULL;
        }

        dict->keys[index]->key_value = *key;
        dict->keys[index]->num_values = 0;
        // TODO init dict nodes
        // dict->keys[index]->nodes.prev = NULL;
        // dict->keys[index]->nodes.next = NULL;

        // TODO init dict dbl_list values

        printf("Add new key %s\n", key);
        return dict->keys[index];
    }

    // verifico univocità della chiave da inserire. SE GIA' ESISTE return NULL
    if (new_key->key_length == key_len && strcmp(key, new_key->key_value) == 0)
    {
        printf("Duplicated Key: %s\n", key);
        return NULL;
    }

    printf(">>> New Zone...\n");
    // index is bounds AND key is new value --> to allocate mem space for new key
    geg_key_t *new_item = dict->allocators.f_malloc(sizeof(geg_key_t));
    if (!new_item)
    {
        return NULL;
    }

    // inserisco la nuova chiave sull'hashmap già presente
    new_item->key_value = key;
    new_item->key_length = key_len;
    new_item->num_values = 0;
    // new_item->nodes->prev = NULL;
    // new_item->nodes->next = NULL;
    // geg_nodes_t *nodes = NULL;
    // geg_node_init(nodes);
    // nodes->prev = NULL;
    // nodes->next = NULL;

    // new_item->value = value;

    // tail->next = new_item;
    return new_key;
}

void null_test()
{
    int b = 0;
    if (b == 1)
    {
        // geg_dictionary_t *new_dict()
        // {
        //     geg_dictionary_t *table = malloc(sizeof(geg_dictionary_t));

        //     if (!table)
        //     {
        //         return NULL;
        //     }

        //     table->hashmap_size = sizeof(unsigned long long);
        //     table->nodes = calloc(table->hashmap_size, sizeof(geg_node_t *));
        //     table->key_len = 0;

        //     // geg_object_allocator_t allocators;
        //     // allocators.f_malloc = malloc;
        //     // allocators.f_realloc = realloc;
        //     // allocators.f_free = free;

        //     table->allocators = init_allocator((*malloc), realloc, free);

        //     if (!table->nodes)
        //     {
        //         free(table);
        //         return NULL;
        //     }
        //     return table;
        // }
    }

    int a = 0;
    if (a == 1)
    {
        // geg_dictionary_t *new_dict_with_hashsize(const size_t hashmap_size)
        // {
        //     geg_dictionary_t *table = malloc(sizeof(geg_dictionary_t));

        //     if (!table)
        //     {
        //         return NULL;
        //     }

        //     table->hashmap_size = hashmap_size;
        //     table->nodes = calloc(table->hashmap_size, sizeof(geg_node_t *));
        //     table->key_len = 0;

        //     if (!table->nodes)
        //     {
        //         free(table);
        //         return NULL;
        //     }
        //     return table;
        // }

        // geg_node_t *add_node(geg_dictionary_t * table, const char *key, const size_t key_len, const char *value)
        // {
        //     size_t hash = djb33x_hash(key, key_len);
        //     size_t index = hash % table->hashmap_size;
        //     geg_node_t *head = table->nodes[index];

        //     if (!head)
        //     {
        //         table->nodes[index] = malloc(sizeof(geg_node_t));
        //         if (!table->nodes[index])
        //         {
        //             return NULL;
        //         }

        //         table->nodes[index]->key = key;
        //         table->nodes[index]->key_len = key_len;
        //         table->nodes[index]->value = value;
        //         table->key_len++;

        //         return table->nodes[index];
        //     }

        //     // verifico univocità della chiave da inserire
        //     geg_node_t *tail = head;
        //     while (head)
        //     {
        //         if (head->key_len == key_len && strcmp(key, head->key) == 0)
        //         {
        //             return NULL;
        //         }
        //         tail = head;
        //         head = head->next;
        //     }

        //     // alloco spazio per la nuova chiave
        //     geg_node_t *new_item = malloc(sizeof(geg_node_t));
        //     if (!new_item)
        //     {
        //         return NULL;
        //     }

        //     // inserisco la nuova chiave sull'hashmap già presente
        //     new_item->key = key;
        //     new_item->key_len = key_len;
        //     new_item->next = NULL;
        //     new_item->value = value,

        //     tail->next = new_item;

        //     // CREAZIONE DEL NUOVO DIZIONARIO PER IL NUOVO HASHMAP
        //     // geg_dictionary_t *largest_table = set_dictionary_new(table->hashmap_size + 10);
        //     geg_dictionary_t *largest_table = new_dict_with_hashsize(table->hashmap_size + 10);

        //     // sposta il vecchio table sul nuovo
        //     for (size_t i = 0; i < table->hashmap_size; i++)
        //     {
        //         geg_node_t *current_node = table->nodes[i];

        //         while (current_node)
        //         {
        //             // dictionary_insert_node(largest_table,
        //             add_node(largest_table,
        //                      current_node->key,
        //                      current_node->key_len,
        //                      current_node->value);

        //             // TODO ANNULLARE IL NEXT
        //             if (current_node->next)
        //             {
        //                 table->nodes[i]->next = NULL;
        //                 puts("PROBLEMI DI IDENTITA...");
        //                 current_node = current_node->next;
        //             }
        //         }
        //     }

        //     table = largest_table;
        //     free(largest_table);
        // }
    }
}