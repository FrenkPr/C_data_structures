#include "dictionary.h"

dict_string_value_node *get_new_dict_string_value(const char *string_value)
{
    dict_string_value_node *item = malloc(sizeof(dict_string_value_node));
    item->string = string_value;

    return item;
}

dict_int_value_node *get_new_dict_int_value(int int_value)
{
    dict_int_value_node *item = malloc(sizeof(dict_int_value_node));
    item->int_val = int_value;

    return item;
}

void init_dict(s_dict **dict_obj)
{
    if (*dict_obj)
    {
        free((*dict_obj)->dict_keys->nodes);
        free((*dict_obj)->dict_keys);
        free((*dict_obj)->dict_values);
        free(*dict_obj);
    }

    s_dict *new_dict = malloc(sizeof(s_dict));
    s_set *new_dict_values = NULL;

    init_set((s_set **)&new_dict_values, DEFAULT_HASHMAP_SIZE);
    new_dict->dict_keys = new_dict_values;

    new_dict->dict_values = calloc(new_dict->dict_keys->hashmap_size, sizeof(dict_value_node *));

    *dict_obj = new_dict;
}

dict_value_node *dict_insert(s_dict *dict_obj, set_node *key_node, dict_value_node *value_node)
{
    if(!dict_obj || !key_node || !value_node)
    {
        return NULL;
    }

    set_node *new_node_key = set_insert(dict_obj->dict_keys, key_node);

    if(!new_node_key)
    {
        free(value_node);
        return NULL;
    }

    size_t hash = djb33x_hash(key_node->key, key_node->key_len);
    size_t index = hash % dict_obj->dict_keys->hashmap_size;

    dict_obj->dict_values[index] = value_node;
    strcpy_s(dict_obj->dict_values[index]->name, sizeof(dict_obj->dict_values[index]->name), key_node->key);

    return dict_obj->dict_values[index];
}

dict_value_node *dict_update(s_dict *dict_obj, set_node *key_node, dict_value_node *value_node)
{
    if(!dict_obj || !key_node || !value_node)
    {
        return NULL;
    }

    size_t hash = djb33x_hash(key_node->key, key_node->key_len);
    size_t index = hash % dict_obj->dict_keys->hashmap_size;

    set_insert(dict_obj->dict_keys, key_node);
    free(dict_obj->dict_values[index]);

    dict_obj->dict_values[index] = value_node;
    strcpy_s(dict_obj->dict_values[index]->name, sizeof(dict_obj->dict_values[index]->name),
             dict_obj->dict_keys->nodes[index]->key);

    printf("element %s updated successfully\n\n", dict_obj->dict_keys->nodes[index]->key);

    return dict_obj->dict_values[index];
}

void dict_remove(s_dict *dict_obj, set_node *key_node_to_remove)
{
    if(!dict_obj || !key_node_to_remove)
    {
        return;
    }

    set_node *node_to_remove = malloc(sizeof(set_node));
    memcpy(node_to_remove, key_node_to_remove, sizeof(*key_node_to_remove));

    if(!dict_find(dict_obj, key_node_to_remove))
    {
        printf("Error deleting %s element.\nThe element doesn't exist\n\n", node_to_remove->key);
        return;
    }

    const size_t hash = djb33x_hash(node_to_remove->key, node_to_remove->key_len);
    const size_t index = hash % dict_obj->dict_keys->hashmap_size;

    set_remove(dict_obj->dict_keys, (set_node **)&node_to_remove);

    //clear dict value
    free(dict_obj->dict_values[index]);
    dict_obj->dict_values[index] = malloc(sizeof(dict_value_node));
}

dict_value_node *dict_find(s_dict *dict_obj, set_node *key_node_to_find)
{
    if(!dict_obj || !key_node_to_find)
    {
        return NULL;
    }

    const size_t hash = djb33x_hash(key_node_to_find->key, key_node_to_find->key_len);
    const size_t index = hash % dict_obj->dict_keys->hashmap_size;

    return set_find(dict_obj->dict_keys, key_node_to_find) ? dict_obj->dict_values[index] : NULL;
}
