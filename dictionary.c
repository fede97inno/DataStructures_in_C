#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 8          // Bigger size, fewer collisions
#define HASHMAP_SIZE_LIST 1

struct aiv_dict_item
{
    const char* key;
    int* value; //void*
    size_t key_len;
};

struct aiv_dict
{
    struct aiv_dict_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];    // Three elements hashmap, can be dynamic
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

void aiv_dict_insert(struct aiv_dict* dict, const char* key,const int* value /*, size_t value_size*/)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len == 0)
        {
            dict->hashmap[index][i].key = key;
            dict->hashmap[index][i].value = malloc(sizeof(int));
            memcpy(dict->hashmap[index][i].value, value, sizeof(int));
            dict->hashmap[index][i].key_len = key_len;
            printf("Added (%s, %d) at index %llu slot %llu\n", key, *value, index, i);
            return;
        }
    }

    printf("COLLISION for %s (index %llu)\n", key, index);
}

void* aiv_dict_find(struct aiv_dict* dict, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len > 0)
        {
            if (dict->hashmap[index][i].key_len == key_len && !memcmp(dict->hashmap[index][i].key, key, key_len))
            {
                printf("Found value for key %s at index %llu slot %llu\n", key, index, i);
                return dict->hashmap[index][i].value;
            }
        }
    }

    printf("Key %s not found\n", key);
    return NULL;
}

void aiv_dict_remove(struct aiv_dict* dict, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (dict->hashmap[index][i].key_len > 0)
        {
            if (dict->hashmap[index][i].key_len == key_len && !memcmp(dict->hashmap[index][i].key, key, key_len))
            {
                free(dict->hashmap[index][i].value);
                dict->hashmap[index][i].key = NULL;
                dict->hashmap[index][i].value = NULL;
                dict->hashmap[index][i].key_len = 0;
                printf("Removed key %s at index %llu slot %llu\n", key, index, i);
                return;
            }
        }
    }

    printf("Key %s not found for removal\n", key);
}

int main()
{
    struct aiv_dict my_dict;
    memset(&my_dict, 0, sizeof(struct aiv_dict));

    int int_value = 32;
    aiv_dict_insert(&my_dict, "Pollo", &int_value);
    aiv_dict_insert(&my_dict, "Palla", 32);
    return 0;
}