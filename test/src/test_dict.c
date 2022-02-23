#define CLOVE_SUITE_NAME geg_hardrock_dict
#include "clove.h"
#include "geg_dictionary.h"

CLOVE_TEST(geg_create_node)
{
    geg_nodes_t node_01;
    geg_nodes_t node_02;
}

// CLOVE_TEST(InsertOneElement)
// {
//     geg_dictionary_t *dictionary = new_dict_with_hashsize(4);
// }

// CLOVE_TEST(IncreaseHashMapSize)
// {
//     geg_dictionary_t *dictionary = set_dictionary_new(2);

//     geg_node_t *node_01 = dictionary_insert_node(dictionary, "pippo", 5, "ciao pippo");
//     geg_node_t *node_02 = dictionary_insert_node(dictionary, "pluto", 5, "ciao pluto");
//     geg_node_t *node_03 = dictionary_insert_node(dictionary, "topolino", 5, "ciao topolino");

//     // CLOVE_UINT_EQ(3, dictionary->elements_inserted);
//     // CLOVE_UINT_EQ(4, dictionary->hashmap_size);
// }