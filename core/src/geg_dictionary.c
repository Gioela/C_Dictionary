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

    // printf("size dict %llu - mem addr %llu\n", sizeof(dict), *dict);

    // TODO ? init sub structures with pre alloc memory for first 4 elements
    // dict->keys[0]->num_values = 0;

    return dict;

    // return geg_new_dict_ha(hashmap_size, &allocators);
}

int geg_add_key(geg_dictionary_t *dict, const char *key, const size_t key_len)
{
    if (!dict)
    {
        return -1;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    geg_key_t *new_key = dict->keys[index];
    // printf("index: %llu - new_key: %llu\n", index, new_key);

    // if new_key is NULL --> index of new key is out of bounds so it's necessary
    //                      allocated new space for this new index (with its objects and values)
    if (!new_key)
    {
        dict->keys[index] = (geg_key_t *)dict->allocators.f_malloc(sizeof(geg_key_t));
        if (!dict->keys[index])
        {
            return -1;
        }

        // dict->keys[index]->key_value = NULL;
        memcpy(&(dict->keys[index]->key_value), key, key_len);
        dict->keys[index]->key_length = key_len;
        dict->keys[index]->num_values = 0;
        ++dict->num_keys;

        // TODO init dict nodes
        // dict->keys[index]->nodes.prev = NULL;
        // dict->keys[index]->nodes.next = NULL;

        // TODO init dict dbl_list values

        // printf("Add new key %s\n", key);
        return 0;
    }

    // verifico univocità della chiave da inserire. SE GIA' ESISTE return NULL
    // if (new_key->key_length == key_len && strcmp(key, (char *)&new_key->key_value) == 0)
    if (new_key->key_length == key_len && memcmp(key, (char *)&new_key->key_value, key_len) == 0)
    {
        // printf("Duplicated Key: %s\n", key);
        return -1;
    }

    // TODO ricalcolare l'hashmap delle chiavi del vecchio nel nuovo dizionario

    printf("nw->key_value: %s - VS - key: %s\n", (char *)&new_key->key_value, key);
    puts(">>> New Zone ==> re-calculate the hashmap size and move all items");

    // index is bounds AND key is new value --> to allocate mem space for new key
    geg_dictionary_t *new_dict = geg_new_dict_with_hashsize(dict->hashmap_size + 4);
    if (!new_dict)
    {
        puts("errore creazione new_dict");
        return -1;
    }
    new_dict->allocators = dict->allocators;
    printf("new_dict->hashmap_size: %llu\n", new_dict->hashmap_size);


    // COPIA DELLE NUOVE CHIAVI NEL NUOVO DIZIONARIO
    // for (size_t i = 0; i < dict->keys; ++i)
    // {
    //     // printf("dict->k[%llu] -> char: %s\n", dict->keys[i], (char*)&dict->keys[i]->key_value);
    //     printf("ptr dict->k[%llu] : %llu\n", i, dict->keys[i]);

    //     if (!dict->keys[i])
    //     {
    //         printf("chiave %llu ancora vuota. Go to next key\n", i);
    //         continue;
    //     }
    //     printf("it needs to add k[%llu]\n", i);
    //     printf("dict->k->char: %s - lunghezza: %llu\n", (char *)&dict->keys[i]->key_value, dict->keys[i]->key_length);

    //     // recalculate the hashmap for old elements and move them into new_dict
    //     if (geg_add_key(new_dict, (char *)&dict->keys[i]->key_value, dict->keys[i]->key_length, dict->keys[i]->values) != 0)
    //     {
    //         // Error while add old key to new dict
    //         printf("Error while add old key to new dict\n");
    //         return -1;
    //     }
    // }

    // puts("add new key to new dict");
    // // geg_add_key(new_dict, key, key_len, value);

    // // geg_key_t *new_item = dict->allocators.f_malloc(sizeof(geg_key_t));
    // // if (!new_item)
    // // {
    // //     puts("esco");
    // //     return -1;
    // // }
    // // puts("sarei dovuto uscire...");

    return 0;
}

int geg_add_key_value(geg_dictionary_t *dict, const char *key, const size_t key_len, size_t *value)
{
    int result = geg_add_key(dict, key, key_len);
    if (result != 0)
    {
        return -1;
    }
    
    printf("key added correctly...\n");

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;
    geg_key_t *new_key = dict->keys[index];

    geg_list_values_t *values_list = dict->keys[index]->values;

    if (!values_list)
    {
        geg_list_values_t *mem_values = (geg_list_values_t *) dict->allocators.f_malloc(sizeof(geg_list_values_t));
        if (!mem_values)
        {
            return -1;
        }

        result = geg_node_init(mem_values->nodes);
        if (result != 0)
        {
            return -1;
        }
        
        mem_values->value = value;

        // printf("\n");

        values_list = mem_values;
        printf("valore aggiunto alla chiave\n");
    }
    else
    {
        printf("values is not null...\n");
    }

    return 0;
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