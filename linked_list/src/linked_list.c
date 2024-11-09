#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define append_list_string_item(linked_list_ref, value) list_append((list_node **)linked_list_ref, (list_node *)get_new_string(value))

struct list_node
{
    struct list_node *next;

} typedef list_node;

struct string_item
{
    list_node node;
    const char *string;

} typedef string_item;

list_node *list_get_tail(list_node **head)
{
    list_node *current_node = *head;
    list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

list_node *list_append(list_node **head, list_node *item)
{
    list_node *tail = list_get_tail(head);

    if (!tail) // if the linked list has no elements
    {
        *head = item;
    }

    else
    {
        tail->next = item;
    }

    item->next = NULL;

    return item;
}

// returns the tail item
// and pops it out from the linked list
list_node *list_pop_tail(list_node **head)
{
    list_node *current_node = *head;
    list_node *last_node = NULL;

    if (current_node && current_node->next == NULL)  //if there's only one list element
    {
        last_node = current_node;
        *head = NULL;

        return last_node;
    }

    while (current_node)
    {
        last_node = current_node;

        if (current_node->next->next == NULL)
        {
            last_node = current_node->next;
            current_node->next = NULL;

            break;
        }

        current_node = current_node->next;
    }

    return last_node;
}

list_node *list_pop_head(list_node **head)
{
    list_node *current_head = *head;

    if (!current_head) // if linked_list is empty
    {
        return NULL;
    }

    *head = (*head)->next;
    current_head->next = NULL;

    return current_head;
}

void reverse_list(list_node **head)
{
    list_node *reversed_list = NULL;
    list_node *reversed_list_head = NULL;
    int is_first_popped_elem = 1;

    while (*head)
    {
        list_node *popped_item = list_pop_tail(head);

        if(is_first_popped_elem == 1)
        {
            reversed_list_head = popped_item;
            is_first_popped_elem = 0;
        }

        list_append((list_node **)&reversed_list, popped_item);
    }

    *head = reversed_list_head;
}

string_item *get_new_string(const char *string)
{
    string_item *item = malloc(sizeof(string_item));

    if (!item) // if no memory is available
    {
        return NULL;
    }

    item->string = string;

    return item;
}

int main()
{
    string_item *string_elems_header = NULL;

    // list_append((list_node **)&string_elems_header, (list_node *)get_new_string("Hello World"));
    // list_append((list_node **)&string_elems_header, (list_node *)get_new_string("Test001"));
    // list_append((list_node **)&string_elems_header, (list_node *)get_new_string("Test002"));
    // list_append((list_node **)&string_elems_header, (list_node *)get_new_string("Last Item of the Linked List"));

    append_list_string_item(&string_elems_header, "Hello World");
    append_list_string_item(&string_elems_header, "Test001");
    append_list_string_item(&string_elems_header, "Test002");
    append_list_string_item(&string_elems_header, "Last Item of the Linked List");

    string_item *string_elems = string_elems_header;

    printf("LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;
    reverse_list((list_node **)&string_elems);
    string_elems_header = string_elems;

    printf("\nREVERSED LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;

    list_pop_tail((list_node **)&string_elems);
    list_pop_tail((list_node **)&string_elems);
    // list_pop_tail((list_node **)&string_elems);
    // list_pop_tail((list_node **)&string_elems);
    // list_pop_tail((list_node **)&string_elems);

    printf("\nPOPPED TAIL LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;
    reverse_list((list_node **)&string_elems);
    string_elems_header = string_elems;

    printf("\nREVERSED LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;

    list_pop_tail((list_node **)&string_elems);

    printf("\nPOPPED TAIL LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    // while (string_elems_header)
    // {
    //     printf("%s\n", string_elems_header->string);
    //     string_elems_header = (string_item *)string_elems_header->node.next;
    // }

    printf("\nPress Enter key to continue");
    getchar();
    return 0;
}