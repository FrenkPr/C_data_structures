#include "set.h"

struct dict_value_node
{
    char name[4096];

} typedef dict_value_node;

struct dict_string_value_node
{
    dict_value_node node;
    const char *string;

} typedef dict_string_value_node;

struct dict_int_value_node
{
    dict_value_node node;
    int int_val;

} typedef dict_int_value_node;

struct s_dict
{
    s_set *dict_keys;
    dict_value_node **dict_values;
    
} typedef s_dict;

dict_string_value_node *get_new_dict_string_value(const char *string);
dict_int_value_node *get_new_dict_int_value(int int_v);
void init_dict(s_dict **dict_obj);
dict_value_node *dict_insert(s_dict *dict_obj, set_node *key_node, dict_value_node *value_node);
dict_value_node *dict_update(s_dict *dict_obj, set_node *key_node, dict_value_node *value_node);
void dict_remove(s_dict *dict_obj, set_node *key_node_to_remove);
dict_value_node *dict_find(s_dict *dict_obj, set_node *key_node_to_find);