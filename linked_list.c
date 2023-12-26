#include <stddef.h>

#define AIV_LIST(x) &(x.list_item)      //MACRO to define something in the code

struct aiv_list_item                    //generic list pointer
{
    struct aiv_list_item* next;         //pointer at next item of the list
    unsigned int count;    
};

struct aiv_int_item                     //list of ints
{
    struct aiv_list_item list_item;
    int value;                          //int element of the list
};

struct aiv_c_sharp_list
{
    struct aiv_list_item* head;
    unsigned int counter;
};

struct aiv_list_item* aiv_list_get_tail(struct aiv_list_item* head)
{
    if (!head)                          //if it hasn't head can't have tail
    {
        return NULL;
    }

    struct aiv_list_item* current_item = head;
    struct aiv_list_item* last_item = head;

    while(current_item)
    {
        last_item = current_item;               //returned value when current is not NULL
        current_item = current_item -> next;    //access to the struct's field
    }

    return last_item;
}

struct aiv_list_item* aiv_list_append(struct aiv_list_item** head, struct aiv_list_item* item)
{
    struct aiv_list_item* tail = aiv_list_get_tail(*head);

    if (!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail -> next = item;
        (*head)->count++;
    }
    
    item->next = NULL; 
    return item;
}

unsigned int aiv_list_lenght(struct aiv_list_item* head)
{
    // unsigned int counter = 0;
    // struct aiv_list_item* current_item = head;

    // while(current_item)
    // {
    //     counter++;
    //     current_item = current_item->next;

    //     return counter;
    // }

    return head->count;
}

struct aiv_list_item* aiv_list_pop(struct aiv_list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }
    
    struct aiv_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head) -> next;                                        //new head

    if (*head)
    {
        (*head)->count = current_count - 1;
    }
    
    current_head->next = NULL;                                      //old head
    return current_head;
}

struct aiv_list_item* aiv_remove_item_by_addres(struct aiv_list_item** head, struct aiv_list_item* address)
{
    if (!(*head))
    {
        return NULL;
    }

    struct aiv_list_item* current_head = *head;

}

int main(int argc, char** argv)
{
    struct aiv_list_item* head = NULL;      //exemple : value = 0 address 0x4000

    struct aiv_int_item int_item;
    int_item.value = 100;
    aiv_list_append(&head, (struct aiv_list_item*)&int_item);   //casts don't change OPCODES, it just shut up the warnings, C is a waekly typed 
                                                                //language, you can cast if the first item address correspond to the actual address
    struct aiv_int_item int_item2;
    int_item.value = 101;
    aiv_list_append(&head, &(int_item2.list_item));             //you can also do this

    struct aiv_int_item int_item3;
    int_item.value = 102;
    aiv_list_append(&head, AIV_LIST(int_item));                 //you can also do this
    return 0;
}