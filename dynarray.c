#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct aiv_dynarray
{
    size_t count;           //how many elements i have in the array
    size_t capacity;        //how mamy elements i can have in the array
    size_t item_size;       //dimension of a single element
    void *data;             //data, array content
};

struct aiv_dynarray* aiv_dynarray_init(const size_t initial_capacity, const size_t item_size)
{
    struct aiv_dynarray* dynarray = malloc(sizeof(struct aiv_dynarray));
    if (!dynarray)
    {
        return NULL;
    }
    
    dynarray->count = 0;
    dynarray->capacity = initial_capacity;
    dynarray->item_size = item_size;
    dynarray->data = malloc(item_size * initial_capacity);

    if (!dynarray->data)            //if i fail the malloc i need to free the memory
    {
        free(dynarray);
        return NULL;
    }

    return dynarray;
}

long long aiv_dynarray_add(struct aiv_dynarray* dynarray, const void* value)
{
    if (dynarray->count + 1 > dynarray->capacity)      //i control if it's not full
    {
        printf("Reached capacity\n");
        //REALLOC
        dynarray->capacity *= 2;
        void * new_data = realloc(dynarray->data, dynarray->item_size * dynarray->capacity);                     //copy in auto new datas in the new place, (what to realloc, how much i want to allocate for new memory)
        if (!new_data)
        {
            printf("UNABLE TO REALLOCATE\n");
            return -1;
        }
        
        dynarray->data = new_data;          //realloc take care of this: if it's the same address ok, if it changes with realloc will move the datas at the new address

        printf("Increased memory\n");
    }
    else
    {
        memcpy(((char*)dynarray->data) + (dynarray->item_size * dynarray->count), value, dynarray->item_size);        //memcpy(((cast to char*, i will be sure to foward to byte to byte)destination where i wanna write data + dim of a item * how many item in the array,value = data to copy,  ))
    }

    printf("ADDED\n");
    dynarray->count++;

    return dynarray->count-1;
}

int main(int argc, char** argv)
{
    struct aiv_dynarray* my_array = aiv_dynarray_init(2, sizeof(int));
    if (!my_array)
    {
        printf("Unable to create dynamic array\n");
        return -1;
    }
    
    printf("dynamic array created at %p (data at %p)\n", my_array, my_array->data); 

    int value = 100;
    aiv_dynarray_add(my_array, &value);
    aiv_dynarray_add(my_array, &value);
    aiv_dynarray_add(my_array, &value);
    aiv_dynarray_add(my_array, &value);
    aiv_dynarray_add(my_array, &value);

    return 0;
}