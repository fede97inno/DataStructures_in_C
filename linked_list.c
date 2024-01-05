#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LINKED_LIST(x) &(x.list_item)      //MACRO to define something in the code

typedef struct linked_list_item                    //generic list pointer
{
    struct linked_list_item* next;         //pointer at next item of the list
    unsigned int count;    
}linked_list_item;

typedef struct linked_int_item                     //list of ints
{
    linked_list_item list_item;
    int value;                          //int element of the list
}linked_int_item;

linked_list_item* linked_list_get_tail(linked_list_item* head)
{
    if (!head)                          //if it hasn't head can't have tail
    {
        return NULL;
    }

    linked_list_item* current_item = head;
    linked_list_item* last_item = head;

    while(current_item)
    {
        last_item = current_item;               //returned value when current is not NULL
        current_item = current_item -> next;    //access to the struct's field
    }

    return last_item;
}

linked_list_item* linked_list_append(linked_list_item** head, linked_list_item* item)
{
    struct linked_list_item* tail = linked_list_get_tail(*head);

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

unsigned int linked_list_lenght(linked_list_item* head)
{
    return head->count;
}

linked_list_item* linked_list_pop(linked_list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }
    
    struct linked_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head) -> next;                                        //new head

    if (*head)
    {
        (*head)->count = current_count - 1;
    }
    
    current_head->next = NULL;                                      //old head
    return current_head;
}

linked_list_item* linked_list_remove_item(linked_list_item** head, linked_list_item* item_to_remove)
{
    if (!(*head))
    {
        return NULL;
    }

    linked_list_item* current_item = *head;

    if (current_item == item_to_remove)
    {
        return linked_list_pop(head);
    }

    linked_list_item* next_item = current_item->next;

    while (next_item != item_to_remove)
    {
        current_item = current_item->next;
        next_item = next_item->next;
    }

    current_item->next = next_item->next;
    next_item->next =NULL;

    return next_item;
}

void linked_list_print(linked_list_item* head)
{
    printf("--------------------\n");
    struct linked_int_item* current_item = (struct linked_int_item*)head;
    
    while(current_item)
    {
        printf("%d\n", current_item->value);
        current_item = ((struct linked_int_item*)current_item->list_item.next);
    }
}

void linked_list_reverse(linked_list_item** head)
{
    linked_list_item* current_item = *head;
    current_item->next = NULL;
    linked_list_item* next_item = (*head)->next;
    printf("hey");

    while(current_item)
    {
        next_item->next = current_item;
        current_item = current_item->next;
        printf("hey");
    }

    //head = *next_item;
}

int main(int argc, char** argv)
{
    linked_list_item* head = NULL;      
    
    linked_int_item int_item0;
    int_item0.value = 100;
    linked_list_append(&head,  LINKED_LIST(int_item0));   

    linked_int_item int_item1;
    int_item1.value = 101;
    linked_list_append(&head, LINKED_LIST(int_item1));             

    linked_int_item int_item2;
    int_item2.value = 102;
    linked_list_append(&head, LINKED_LIST(int_item2));                 

    linked_int_item int_item3;
    int_item3.value = 103;
    linked_list_append(&head, LINKED_LIST(int_item3));                 

    linked_int_item int_item4;
    int_item4.value = 104;
    linked_list_append(&head, LINKED_LIST(int_item4));                 
    
    linked_list_print(head);

    //linked_list_pop(&head);

    //linked_list_remove_item(&head, LINKED_LIST(int_item4));

    //linked_list_print(head);

    linked_list_reverse(&head);
    
    linked_list_print(head);

    return 0;
}