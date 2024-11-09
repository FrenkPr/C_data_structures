#include "set.h"

string_set_node *get_new_string_set_node(const char *string)
{
    string_set_node *item = malloc(sizeof(string_set_node));

    item->string = string;
    strcpy_s(item->node.key, sizeof(item->node.key), string);
    item->node.key_len = strlen(item->node.key);

    return item;
}

int_set_node *get_new_int_set_node(int int_v)
{
    int_set_node *item = malloc(sizeof(int_set_node));

    item->int_val = int_v;

    _itoa_s(int_v, item->node.key, sizeof(item->node.key), 10);
    item->node.key_len = strlen(item->node.key);

    return item;
}

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void init_set(s_set **set_obj, const size_t hashmap_size)
{
    if (*set_obj)
    {
        free((*set_obj)->nodes);
        free(*set_obj);
    }

    s_set *new_set = malloc(sizeof(s_set));

    if (!new_set) // if there's not enough memory to init the set
    {
        return;
    }

    new_set->hashmap_size = hashmap_size;
    new_set->nodes = calloc(new_set->hashmap_size, sizeof(set_node *));

    *set_obj = new_set;
}

set_node *set_insert(s_set *set_obj, set_node *new_node)
{
    if (!set_obj || !new_node)
    {
        return NULL;
    }

    size_t hash = djb33x_hash(new_node->key, new_node->key_len);
    size_t index = hash % set_obj->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", new_node->key, hash, index);

    if (!set_obj->nodes[index])
    {
        // set_obj->nodes[index] = malloc(sizeof(set_node));
        set_obj->nodes[index] = new_node;

        if (!set_obj->nodes[index])
        {
            return NULL;
        }

        printf("string node key: %s\n", new_node->key);

        // set_obj->nodes[index]->key = new_node->key;
        // set_obj->nodes[index]->key_len = new_node->key_len;

        printf("added %s at index %llu\n\n", new_node->key, index);

        return set_obj->nodes[index];
    }

    printf("COLLISION! for %s (index %llu)\n\n", new_node->key, index);

    free(new_node);

    return NULL;
}

void set_remove(s_set *set_obj, set_node **node_to_remove)
{
    if (!set_obj || !*node_to_remove)
    {
        return;
    }

    const size_t hash = djb33x_hash((*node_to_remove)->key, (*node_to_remove)->key_len);
    const size_t index = hash % set_obj->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", (*node_to_remove)->key, hash, index);

    if (set_obj->nodes[index])
    {
        printf("ELEMENT %s at index %llu DELETED\n\n", (*node_to_remove)->key, index);

        free(set_obj->nodes[index]);
        set_obj->nodes[index] = NULL;

        if (*node_to_remove)
        {
            free(*node_to_remove);
            *node_to_remove = NULL;
        }

        return;
    }

    printf("Error deleting element %s (index %llu)\nThe element doesn't exist\n\n", (*node_to_remove)->key, index);

    if (*node_to_remove)
    {
        free(*node_to_remove);
        *node_to_remove = NULL;
    }
}

int set_find(s_set *set_obj, set_node *node_to_find)
{
    if (!set_obj || !node_to_find)
    {
        return 0;
    }

    const size_t hash = djb33x_hash(node_to_find->key, node_to_find->key_len);
    const size_t index = hash % set_obj->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", node_to_find->key, hash, index);

    if (set_obj->nodes[index] && set_obj->nodes[index]->key_len > 0)
    {
        if (set_obj->nodes[index]->key_len == node_to_find->key_len &&
            memcmp(set_obj->nodes[index]->key, node_to_find->key, node_to_find->key_len) == 0)
        {
            printf("%s FOUND at index %llu\n\n", node_to_find->key, index);
            free(node_to_find);

            return 1;
        }
    }

    printf("%s NOT FOUND\n\n", node_to_find->key);
    free(node_to_find);

    return 0;
}