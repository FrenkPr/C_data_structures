#ifndef SET_H
#define SET_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_HASHMAP_SIZE 64

struct set_node
{
    char key[4096];
    size_t key_len;

} typedef set_node;

struct s_set
{
    set_node **nodes;
    size_t hashmap_size;

} typedef s_set;

struct string_set_node
{
    set_node node;
    const char *string;

} typedef string_set_node;

struct int_set_node
{
    set_node node;
    int int_val;

} typedef int_set_node;

static set_node *node_to_remove = NULL;
static set_node *node_to_find = NULL;
static int node_to_find_result = 0;

// macros insert
#define set_insert_string(set_obj, value) \
    set_insert(set_obj, (set_node *)get_new_string_set_node(value));

#define set_insert_int(set_obj, value) \
    set_insert(set_obj, (set_node *)get_new_int_set_node(value));

// macros remove
#define set_remove_string(set_obj, value)               \
    node_to_remove = (set_node *)get_new_string_set_node(value); \
    set_remove(set_obj, (set_node **)&node_to_remove);

#define set_remove_int(set_obj, value)               \
    node_to_remove = (set_node *)get_new_int_set_node(value); \
    set_remove(set_obj, (set_node **)&node_to_remove);

// macros find
#define set_find_string(set_obj, value)                    \
    node_to_find = (set_node *)get_new_string_set_node(value);      \
    node_to_find_result = set_find(set_obj, node_to_find); \
    free(node_to_find);

#define set_find_int(set_obj, value)               \
    node_to_find = (set_node *)get_new_int_set_node(value); \
    set_find(set_obj, node_to_find);               \
    free(node_to_find);

string_set_node *get_new_string_set_node(const char *string);
int_set_node *get_new_int_set_node(int int_v);
size_t djb33x_hash(const char *key, const size_t keylen);
void init_set(s_set **set_obj, const size_t hashmap_size);
set_node *set_insert(s_set *set_obj, set_node *new_node);
void set_remove(s_set *set_obj, set_node **node_to_remove);
int set_find(s_set *set_obj, set_node *node_to_find);

#endif // SET_H