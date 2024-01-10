#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 8          //bigger less collisions
#define HASHMAP_SIZE_LIST 1

struct aiv_set_item
{
    const char* key;
    size_t key_len;    
};

struct aiv_set
{
    struct aiv_set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];    //three elements hashmap, should be dynamic
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

void aiv_set_insert(struct aiv_set* set, const char* key)
{
    const size_t key_len = strlen(key);
    
    const size_t hash = djb33x_hash(key, key_len);      //first thing hash the key, we use strlen cause if we use size of will give the size of the pointer that is 8

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index : %llu)\n", key, hash, index);                 //llu = long long unsigned = size_t

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            printf("added %s at index %llu slot %llu\n",key, index, i);
            return;
        }
    }

    printf("COLLISION for %s (index %llu)\n", key, index);
}

void aiv_set_find(struct aiv_set* set, const char* key)
{
    const size_t key_len = strlen(key);
    
    const size_t hash = djb33x_hash(key, key_len);      //first thing hash the key, we use strlen cause if we use size of will give the size of the pointer that is 8

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index : %llu)\n", key, hash, index);                 //llu = long long unsigned = size_t

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len) )
            {
                printf("FOUND %s at index %llu slot %llu\n",key, index, i);
                return;
            }
        }
    }
}

int main(int argc, char** argv)
{
    struct aiv_set my_set;

    memset(&my_set, 0, sizeof(struct aiv_set));  //zeros in the 3 element memory, do what is under it
    
    // myset.hashmap[0].key = NULL;
    // myset.hashmap[0].key_len = 0;    
    // myset.hashmap[1].key = NULL;
    // myset.hashmap[1].key_len = 0;   
    // myset.hashmap[2].key = NULL;
    // myset.hashmap[2].key_len = 0;

    aiv_set_insert(&my_set, "Hello");
    aiv_set_insert(&my_set, "Hello2");
    aiv_set_insert(&my_set, "Test");
    aiv_set_insert(&my_set, "Foobar");

    aiv_set_find(&my_set, "Hello2");
    return 0;
}