#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

struct set_node
{
    const char *key;
    size_t key_len;
    struct set_node *next;

} typedef set_node;

struct my_set
{
    set_node **nodes;
    size_t hashmap_size;

} typedef my_set;

struct string_elem
{
    set_node node;
    const char *string;

} typedef string_elem;

void init_set(my_set **set_obj, const size_t hashmap_size)
{
    my_set *new_set = malloc(sizeof(my_set));

    if (!new_set) // if there's not enough memory to init the set
    {
        return;
    }

    new_set->hashmap_size = hashmap_size;
    new_set->nodes = calloc(new_set->hashmap_size, sizeof(set_node *));

    if (!new_set->nodes) // not enough memory or error allocating memory
    {
        free(new_set);
        return;
    }

    *set_obj = new_set;
}

set_node *set_insert(my_set *set_obj, const char *key)
{
    // my_set *set_obj = *set;

    const size_t key_len = strlen(key);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % set_obj->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (!set_obj->nodes[index])
    {
        set_obj->nodes[index] = malloc(sizeof(set_node));

        if (!set_obj->nodes[index])
        {
            return NULL;
        }

        set_obj->nodes[index]->key = key;
        set_obj->nodes[index]->key_len = key_len;
        set_obj->nodes[index]->next = NULL;

        printf("added %s at index %llu\n\n", key, index);

        return set_obj->nodes[index];
    }

    printf("COLLISION! for %s (index %llu)\n\n", key, index);

    return NULL;
}

void set_remove(my_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (set->nodes[index])
    {
        set->nodes[index]->key = NULL;
        set->nodes[index]->key_len = 0;
        set->nodes[index] = NULL;

        free(set->nodes[index]);

        printf("ELEMENT %s at index %llu DELETED\n\n", key, index);

        return;
    }

    printf("Error deleting element %s (index %llu)\n\n", key, index);
}

int set_find(my_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    if (set->nodes[index] && set->nodes[index]->key_len > 0)
    {
        if (set->nodes[index]->key_len == key_len && !memcmp(set->nodes[index]->key, key, key_len))
        {
            printf("FOUND %s at index %llu\n\n", key, index);
            return 1;
        }
    }

    printf("%s NOT FOUND\n\n", key);
    return 0;
}

int main()
{
    my_set *string_set_header = NULL;

    init_set((my_set **)&string_set_header, 64);

    set_find(string_set_header, "Ciao");
    set_find(string_set_header, "Ciaooooooooooo");
    set_find(string_set_header, "Ciauuuuuuuuuuu");

    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciaooooooooooo");
    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciaooooooooooo");
    set_insert(string_set_header, "Ciaooooooooooo");
    set_insert(string_set_header, "Ciaooooooooooo");
    set_insert(string_set_header, "Ciaooooooooooo");

    set_remove(string_set_header, "Ciauuuuuuuuuuu");

    set_remove(string_set_header, "Ciao");
    set_remove(string_set_header, "Ciao");
    set_remove(string_set_header, "Ciao");

    set_find(string_set_header, "Ciaooooooooooo");
    set_remove(string_set_header, "Ciaooooooooooo");
    set_find(string_set_header, "Ciaooooooooooo");

    set_remove(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciao");
    set_insert(string_set_header, "Ciao");
    set_remove(string_set_header, "Ciao");
    set_remove(string_set_header, "Ciao");

    set_remove(string_set_header, "Ciaooooooooooo");
    set_find(string_set_header, "Ciaooooooooooo");

    return 0;
}