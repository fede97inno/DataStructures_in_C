#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOUBLY_LINKED_LIST(x) &(x.list_item)      //MACRO to define something in the code

typedef struct doubly_linked_list_item                    //generic list pointer
{
    struct doubly_linked_list_item* prev;
    struct doubly_linked_list_item* next;         //pointer at next item of the list
    unsigned int count;    
}doubly_linked_list_item;

typedef struct doubly_linked_int_item                     //list of ints
{
    doubly_linked_list_item list_item;
    int value;                          //int element of the list
}doubly_linked_int_item;

doubly_linked_int_item* doubly_linked_list_new_int_item(int new_value)
{
    doubly_linked_int_item* item = malloc(sizeof(struct doubly_linked_int_item));

    if (!item)
    {
        return NULL;
    }
    
    item->value = new_value;

    return item;
}

doubly_linked_list_item* doubly_linked_list_get_tail(doubly_linked_list_item* head)
{
    if (!head)                          //if it hasn't head can't have tail
    {
        return NULL;
    }

    doubly_linked_list_item* current_item = head;
    doubly_linked_list_item* last_item = head;

    while(current_item)
    {
        last_item = current_item;               //returned value when current is not NULL
        current_item = current_item -> next;    //access to the struct's field
    }

    return last_item;
}

doubly_linked_list_item* doubly_linked_list_append(doubly_linked_list_item** head, doubly_linked_list_item* item)
{
    doubly_linked_list_item* tail = doubly_linked_list_get_tail(*head);

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
    
    item->prev = tail;
    item->next = NULL;
    return item;
}

doubly_linked_list_item* doubly_linked_list_pop(doubly_linked_list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }
    
    struct doubly_linked_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head) -> next;
    (*head)->prev = NULL;                                        //new head

    if (*head)
    {
        (*head)->count--;
    }
    
    current_head->next = NULL;                                      //old head
    return current_head;
}

doubly_linked_list_item* doubly_linked_is_in_list(doubly_linked_list_item** head, doubly_linked_list_item* item_to_check)
{
    if (!(*head))
    {
        return NULL;
    }

    doubly_linked_list_item* current_item = *head;
    
    for (int i = 0; i < (*head)->count; i++)
    {
        if (item_to_check == current_item)
        {
            //printf("IS IN THE LIST\n");
            return item_to_check;
        }
        current_item = current_item->next;
    }

    //printf("IT'S NOT IN THE LIST\n");
    return NULL;
}

doubly_linked_list_item* doubly_linked_list_remove_item(doubly_linked_list_item** head, doubly_linked_list_item* item_to_remove)
{
    if (!(*head))
    {
        return NULL;
    }

    if (!doubly_linked_is_in_list(head, item_to_remove))
    {
        return NULL;
    }

    doubly_linked_list_item* current_item = *head;

    if (current_item == item_to_remove)
    {
        return doubly_linked_list_pop(head);
    }

    doubly_linked_list_item* next_item = current_item->next;

    while (next_item != item_to_remove)
    {
        current_item = current_item->next;
        next_item = next_item->next;
    }

    current_item->next = next_item->next;
    (current_item->next)->prev = current_item;
    
    next_item->prev = NULL;
    next_item->next = NULL;
    (*head)->count--;

    return next_item;
}

doubly_linked_list_item* doubly_linked_list_insert_item_after_a(doubly_linked_list_item** head, doubly_linked_list_item* new_item, doubly_linked_list_item* a)
{
    if (!(*head))
    {
        return NULL;
    }

    if (!doubly_linked_is_in_list(head, a))
    {
        return NULL;
    }

    if (!a->next)
    {
        new_item->next = NULL;
        new_item->prev = a;
        a->next = new_item;

        return new_item;
    }
    
    
    doubly_linked_list_item* old_next = a->next;
    
    a->next = new_item;
    old_next->prev = new_item;

    new_item->prev = a;
    new_item->next = old_next;
    (*head)->count++;

    return new_item;
}

doubly_linked_list_item* doubly_linked_list_insert_item_before_a(doubly_linked_list_item** head, doubly_linked_list_item* new_item, doubly_linked_list_item* a)
{
    if (!(*head))
    {
        return NULL;
    }

    if (!doubly_linked_is_in_list(head, a))
    {
        return NULL;
    }
    
    if (!a->prev)
    {
        new_item->prev = NULL;
        new_item->next = a;
        a->prev = new_item;
        *head = new_item;

        return new_item;
    }
    

    doubly_linked_list_item* old_prev = a->prev;
    
    a->prev = new_item;
    old_prev->next = new_item;

    new_item->prev = old_prev;
    new_item->next = a;
    (*head)->count++;

    return new_item;
}

void doubly_linked_list_print(doubly_linked_list_item* head)
{
    printf("--------------------\n");
    doubly_linked_int_item* current_item = (doubly_linked_int_item*)head;
    
    while(current_item)
    {
        printf("- %d\n", current_item->value);
        current_item = ((doubly_linked_int_item*)current_item->list_item.next);
    }
}

void doubly_linked_list_shuffle(doubly_linked_list_item** head)
{
    printf("----------------\nshuffling\n----------------\n");
    srand(time(NULL));

    for (int i = (*head)->count - 1; i > 0; i--)
    {
        printf("shuffle algh\n");
    }
}

int main(int argc, char** argv)
{
    doubly_linked_list_item* head = NULL;      

    doubly_linked_int_item int_item0;
    int_item0.value = 100;
    doubly_linked_list_append(&head, DOUBLY_LINKED_LIST(int_item0));   

    doubly_linked_int_item int_item1;
    int_item1.value = 101;
    doubly_linked_list_append(&head, DOUBLY_LINKED_LIST(int_item1));             

    doubly_linked_int_item int_item2;
    int_item2.value = 102;
    doubly_linked_list_append(&head, DOUBLY_LINKED_LIST(int_item2));                 

    doubly_linked_int_item int_item3;
    int_item3.value = 103;
    doubly_linked_list_append(&head, DOUBLY_LINKED_LIST(int_item3)); 

    doubly_linked_list_print(head);
    
    doubly_linked_int_item int_item4;
    int_item4.value = 104;

    doubly_linked_list_insert_item_after_a(&head, DOUBLY_LINKED_LIST(int_item4), DOUBLY_LINKED_LIST(int_item3));

    doubly_linked_list_print(head);

    // doubly_linked_int_item* current_item = (doubly_linked_int_item*)head;
    // while (current_item)
    // {
    //     doubly_linked_int_item* node_to_free = current_item;
    //     current_item = (doubly_linked_int_item*)(current_item->list_item.next);

    //     free(node_to_free);
    // }

    doubly_linked_list_shuffle(&head);

    return 0;
}