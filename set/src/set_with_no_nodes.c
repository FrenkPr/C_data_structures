#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

struct set_item
{
    const char *key;
    size_t key_len;

} typedef set_item;

struct my_set
{
    set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];

} typedef my_set;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void set_insert(my_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;

            printf("added %s at index %llu slot %llu\n\n", key, index, i);

            return;
        }
    }

    printf("COLLISION! for %s (index %llu)\n\n", key, index);
}

void set_remove(my_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        set->hashmap[index][i].key = NULL;
        set->hashmap[index][i].key_len = 0;

        printf("ELEMENT %s at index %llu slot %llu DELETED\n\n", key, index, i);

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

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("FOUND %s at index %llu slot %llu\n\n", key, index, i);
                return 1;
            }
        }
    }

    printf("%s NOT FOUND\n\n", key);
    return 0;
}

int main(int argc, char **argv)
{
    my_set myset;
    memset(&myset, 0, sizeof(my_set)); // initializes the variable and all of its components to 0 or NULL

    set_insert(&myset, "Hello");
    set_insert(&myset, "Hello2");
    set_insert(&myset, "Test");
    set_insert(&myset, "Foobar");
    set_insert(&myset, "XYZ");
    set_insert(&myset, "AAAAAA");
    set_insert(&myset, "AAAAAa");
    set_insert(&myset, "AAAAAa");
    set_insert(&myset, "AAAAAa");
    set_insert(&myset, "AAAAAa");
    set_insert(&myset, "AAAAAb");
    set_insert(&myset, "AAAAAa");
    set_insert(&myset, "AAAAAb");

    set_find(&myset, "Hello");
    set_find(&myset, "Hello2");
    set_find(&myset, "Hello3");
    set_insert(&myset, "Hello3");
    set_find(&myset, "Hello3");
    set_find(&myset, "XYZ");

    set_remove(&myset, "XYZ");

    set_find(&myset, "XYZ");

    printf("Press Enter key to continue");
    getchar();
    return 0;
}