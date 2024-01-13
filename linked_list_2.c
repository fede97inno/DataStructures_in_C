#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LINKED_LIST(x) &(x.next)      //MACRO to define something in the code

typedef struct linked_int_item                     //list of ints
{
    struct linked_int_item * next;
    int value;   
    int count;                       //int element of the list
}linked_int_item;

linked_int_item* linked_list_get_tail(linked_int_item* head)
{
    if (!head)                          //if it hasn't head can't have tail
    {
        return NULL;
    }

    linked_int_item* current_item = head;
    linked_int_item* last_item = head;

    while(current_item)
    {
        last_item = current_item;               //returned value when current is not NULL
        current_item = current_item -> next;    //access to the struct's field
    }

    return last_item;
}

linked_int_item *int_item_new(const int val)
{
    linked_int_item *item = malloc(sizeof(linked_int_item));
    
    if (!item)
    {
        return NULL;
    }
    
    item->value = val;
    
    return item;
}

linked_int_item* linked_list_append(linked_int_item** head, linked_int_item* item)
{
    struct linked_int_item* tail = linked_list_get_tail(*head);

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

unsigned int linked_list_lenght(linked_int_item* head)
{
    return head->count;
}

int linked_list_is_in_list(linked_int_item** head, int item_to_check)
{
    linked_int_item* current_item = *head;
    
    for (int i = 0; i < (*head)->count; i++)
    {
        if (item_to_check == current_item->value)
        {
            return 1;
        }

        current_item = current_item->next;
    }

    return 0;
}

linked_int_item* linked_list_pop(linked_int_item** head)
{
    if (!(*head))
    {
        return NULL;
    }
    
    struct linked_int_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head) -> next;                                        //new head

    if (*head)
    {
        (*head)->count = current_count - 1;
    }
    
    current_head->next = NULL;                                      //old head
    free(current_head);
    
    return NULL;
}

linked_int_item* linked_list_remove_item(linked_int_item** head, int item_to_remove)
{
    if (!(*head))
    {
        return NULL;
    }

    if (!linked_list_is_in_list(head, item_to_remove))
    {
        return NULL;
    }
    
    linked_int_item* current_item = *head;

    if (current_item->value == item_to_remove)
    {
        return linked_list_pop(head);
    }

    linked_int_item* next_item = current_item->next;

    while (next_item->value != item_to_remove)
    {
        current_item = current_item->next;
        next_item = next_item->next;
    }

    if (*head)
    {
        (*head)->count--;
    }

    current_item->next = next_item->next;
    next_item->next =NULL;

    free(next_item);

    return NULL;
}

void linked_list_print(linked_int_item* head)
{
    printf("--------------------\n");
    struct linked_int_item* current_item = (struct linked_int_item*)head;
    
    while(current_item)
    {
        printf("%d\n", current_item->value);
        current_item = ((struct linked_int_item*)current_item->next);
    }
}

void linked_list_reverse(linked_int_item** head)
{
    linked_int_item* prev_item = NULL;
    linked_int_item* current_item = *head;
    linked_int_item* next_item = current_item->next;
    int counter = 0;

    while(current_item)
    {   
        next_item = current_item->next;
        current_item->next = prev_item;
        prev_item = current_item;
        current_item = next_item;
    }

    *head = prev_item;
}

int main(int argc, char** argv)
{
    linked_int_item* head = NULL;      
    
    linked_list_append(&head, int_item_new(3));
    linked_list_append(&head, int_item_new(3));
    linked_list_append(&head, int_item_new(4));
    linked_list_append(&head, int_item_new(5));
    
    linked_list_print(head);

    //linked_list_reverse(&head);

    linked_list_remove_item(&head, 4);
    
    linked_list_print(head);
    
    linked_int_item* current = head;

    while(current)
    {
        current = current->next;
        free(current);
    }
    
    return 0;
}