#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define append_list_string_item(list_header_ref, value) list_append((list_node **)list_header_ref, (list_node *)get_new_string(value))
#define insert_before_string_item(list_header_ref, value, index) insert_before((list_node **)list_header_ref, (list_node *)get_new_string(value), index)
#define insert_after_string_item(list_header_ref, value, index) insert_after((list_node **)list_header_ref, (list_node *)get_new_string(value), index)

struct list_node
{
    struct list_node *prev;
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

    if (!tail) // if is first element to append
    {
        *head = item;
    }

    else
    {
        tail->next = item;
    }

    item->prev = tail;
    item->next = NULL;

    return item;
}

list_node *get_elem_at(list_node *head, int index)
{
    if (!head) // if list is empty
    {
        return NULL;
    }

    list_node *elem = head;

    for (int i = 0; i < index; i++)
    {
        if (!elem)
        {
            return NULL;
        }

        elem = elem->next;
    }

    return elem;
}

int get_list_count(list_node *head)
{
    if (!head) // if list is empty
    {
        return 0;
    }

    list_node *current_elem = head;
    int count = 0;

    while (current_elem)
    {
        current_elem = current_elem->next;
        count++;
    }

    return count;
}

void insert_before(list_node **head, list_node *item, int index)
{
    list_node *elem_before_insert = get_elem_at(*head, index);

    if (!*head && index == 0) // if list is empty and the index specified is 0
    {
        list_append(head, item);
        return;
    }

    else if (!elem_before_insert) // if element next to before insert is not valid
    {
        return;
    }

    else if (elem_before_insert == (*head))
    {
        list_node *old_head = *head;

        *head = item;

        if (old_head)
        {
            (*head)->next = old_head;
            old_head->prev = *head;
        }

        return;
    }

    list_node *elem_before_insert_prev_node = elem_before_insert->prev;

    if (elem_before_insert_prev_node)
    {
        elem_before_insert_prev_node->next = item;
        item->prev = elem_before_insert_prev_node;
    }

    item->next = elem_before_insert;
    elem_before_insert->prev = item;
}

void insert_after(list_node **head, list_node *item, int index)
{
    list_node *elem_next_to_insert_after = get_elem_at(*head, index);

    if (!*head && index == 0) // if list is empty and the index specified is 0
    {
        list_append(head, item);
        return;
    }

    else if (!elem_next_to_insert_after) // if element next to insert after is not valid
    {
        return;
    }

    list_node *elem_insert_after_old_next_node = elem_next_to_insert_after->next;

    elem_next_to_insert_after->next = item;

    item->prev = elem_next_to_insert_after;
    item->next = elem_insert_after_old_next_node;

    if (elem_insert_after_old_next_node)
        elem_insert_after_old_next_node->prev = item;
}

// returns the tail item
// and pops it out from the list
list_node *list_pop_tail(list_node **head)
{
    list_node *last_node = list_get_tail(head);

    if (!last_node) // if list is empty
    {
        return NULL;
    }

    list_node *second_last_node = last_node->prev;

    if (!second_last_node) // if there's only one element in the list
    {
        *head = NULL;
        return last_node;
    }

    second_last_node->next = NULL;
    last_node->prev = NULL;

    return last_node;
}

// returns the head item
// and pops it out from the list
list_node *list_pop_head(list_node **head)
{
    list_node *popped_head = *head;

    if (!popped_head) // if list is empty
    {
        return NULL;
    }

    *head = (*head)->next;

    return popped_head;
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

// Generates a random
// number in range [min, max]
// max is inclusive
int get_random_number_in_range(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void shuffle_list_elements(list_node **head, int rand_elem1_index, int rand_elem2_index)
{
    int list_count = get_list_count(*head);

    if (!*head || list_count <= 1)
    {
        return;
    }

    // int rand_elem1_index = get_random_number_in_range(0, list_count - 1);
    // int rand_elem2_index = get_random_number_in_range(0, list_count - 1);

    // int rand_elem1_index = 3;
    // int rand_elem2_index = 5;

    list_node *rand_elem1;
    list_node *rand_elem2;

    while (rand_elem2_index == rand_elem1_index)
    {
        rand_elem2_index = get_random_number_in_range(0, list_count - 1);
    }

    if (rand_elem2_index < rand_elem1_index)
    {
        int rand_elem_exchange = rand_elem1_index;

        rand_elem1_index = rand_elem2_index;
        rand_elem2_index = rand_elem_exchange;
    }

    rand_elem1 = get_elem_at(*head, rand_elem1_index);
    rand_elem2 = get_elem_at(*head, rand_elem2_index);

    list_node *prev_rand_node1_neighbour = rand_elem1->prev;
    list_node *next_rand_node1_neighbour = rand_elem1->next;

    list_node *prev_rand_node2_neighbour = rand_elem2->prev;
    list_node *next_rand_node2_neighbour = rand_elem2->next;

    rand_elem1->prev = rand_elem2->prev;
    rand_elem1->next = rand_elem2->next;

    rand_elem2->prev = prev_rand_node1_neighbour;
    rand_elem2->next = next_rand_node1_neighbour;

    printf("\nrand1_elem: %s\n", ((string_item *)rand_elem1)->string);
    printf("rand2_elem: %s\n\n", ((string_item *)rand_elem2)->string);

    if (rand_elem1_index == 0)
    {
        *head = rand_elem2;

        if (rand_elem1_index == rand_elem2_index - 1) // if the 2 shuffled elements are neighbours
        {
            (*head)->next = rand_elem1;
            rand_elem1->prev = *head;
        }

        else
        {
            (*head)->next = next_rand_node1_neighbour;
            next_rand_node1_neighbour->prev = *head;

            if (prev_rand_node2_neighbour)
                prev_rand_node2_neighbour->next = rand_elem1;

            if (next_rand_node2_neighbour)
                next_rand_node2_neighbour->prev = rand_elem1;
        }

        (*head)->prev = NULL;
        rand_elem2->prev = NULL;
    }

    // else if (rand_elem2_index == 0)
    // {
    //     *head = rand_elem1;

    //     if (rand_elem2_index == rand_elem1_index - 1) // if the 2 shuffled elements are neighbours
    //     {
    //         (*head)->next = rand_elem2;
    //         rand_elem2->prev = *head;
    //     }

    //     else
    //     {
    //         (*head)->next = next_rand_node2_neighbour;

    //         if (prev_rand_node1_neighbour)
    //             prev_rand_node1_neighbour->next = rand_elem2;

    //         if (next_rand_node1_neighbour)
    //             next_rand_node1_neighbour->prev = rand_elem2;
    //     }
    // }

    // else if (rand_elem1_index == rand_elem2_index - 1 || rand_elem2_index == rand_elem1_index - 1) // if the 2 shuffled elements are neighbours
    // {
    //     if (rand_elem1_index < rand_elem2_index)
    //     {
    //         rand_elem1->prev = rand_elem2;
    //         rand_elem1->next = next_rand_node2_neighbour;

    //         if (next_rand_node2_neighbour)
    //             next_rand_node2_neighbour->prev = rand_elem1;

    //         rand_elem2->prev = prev_rand_node1_neighbour;
    //         rand_elem2->next = rand_elem1;

    //         if (prev_rand_node1_neighbour)
    //             prev_rand_node1_neighbour->next = rand_elem2;
    //     }

    //     else
    //     {
    //         rand_elem1->prev = prev_rand_node2_neighbour;
    //         rand_elem1->next = rand_elem2;

    //         if (prev_rand_node2_neighbour)
    //             prev_rand_node2_neighbour->next = rand_elem1;

    //         rand_elem2->prev = rand_elem1;
    //         rand_elem2->next = next_rand_node1_neighbour;

    //         if (next_rand_node1_neighbour)
    //             next_rand_node1_neighbour->prev = rand_elem2;
    //     }
    // }

    else if (rand_elem1_index == rand_elem2_index - 1) // if the 2 shuffled elements are neighbours
    {
        rand_elem1->prev = rand_elem2;
        rand_elem1->next = next_rand_node2_neighbour;

        if (next_rand_node2_neighbour)
            next_rand_node2_neighbour->prev = rand_elem1;

        rand_elem2->prev = prev_rand_node1_neighbour;
        rand_elem2->next = rand_elem1;

        if (prev_rand_node1_neighbour)
            prev_rand_node1_neighbour->next = rand_elem2;
    }

    else
    {
        if (prev_rand_node1_neighbour)
            prev_rand_node1_neighbour->next = rand_elem2;

        if (next_rand_node1_neighbour)
            next_rand_node1_neighbour->prev = rand_elem2;

        if (prev_rand_node2_neighbour)
            prev_rand_node2_neighbour->next = rand_elem1;

        if (next_rand_node2_neighbour)
            next_rand_node2_neighbour->prev = rand_elem1;
    }

    // printf("rand1_elem shuffled: %s\n", ((string_item *)rand_elem1)->string);
    // printf("rand2_elem shuffled: %s\n\n", ((string_item *)rand_elem2)->string);

    if (rand_elem1->next)
    {
        printf("rand1_elem next: %s\n", ((string_item *)rand_elem1->next)->string);
        next_rand_node1_neighbour = rand_elem1->next;
    }

    else
        next_rand_node1_neighbour = NULL;

    if (rand_elem1->prev)
    {
        printf("rand1_elem prev: %s\n", ((string_item *)rand_elem1->prev)->string);
        prev_rand_node1_neighbour = rand_elem1->prev;
    }

    else
    {
        prev_rand_node1_neighbour = NULL;
    }

    if (rand_elem2->next)
    {
        printf("rand2_elem next: %s\n", ((string_item *)rand_elem2->next)->string);
        next_rand_node2_neighbour = rand_elem2->next;
    }

    else
        next_rand_node2_neighbour = NULL;

    if (rand_elem2->prev)
    {
        printf("rand2_elem prev: %s\n", ((string_item *)rand_elem2->prev)->string);
        prev_rand_node2_neighbour = rand_elem2->prev;
    }

    else
        prev_rand_node2_neighbour = NULL;


    if (next_rand_node1_neighbour)
        printf("next_rand_node1_neighbour: %s\n", ((string_item *)next_rand_node1_neighbour)->string);

    if (prev_rand_node1_neighbour)
        printf("prev_rand_node1_neighbour: %s\n", ((string_item *)prev_rand_node1_neighbour)->string);

    if (next_rand_node2_neighbour)
        printf("next_rand_node2_neighbour: %s\n", ((string_item *)next_rand_node2_neighbour)->string);

    if (prev_rand_node2_neighbour)
        printf("prev_rand_node2_neighbour: %s\n", ((string_item *)prev_rand_node2_neighbour)->string);
}

int main()
{
    srand(time(0));

    string_item *string_elems_header = NULL;

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

    string_item *popped_elem = (string_item *)list_pop_head((list_node **)&string_elems);
    if (popped_elem)
        popped_elem->node.next = NULL;

    popped_elem = (string_item *)list_pop_tail((list_node **)&string_elems);

    string_elems_header = string_elems;

    // if (popped_elem)
    //     printf("Popped elem: %s\n", popped_elem->string);
    // if (popped_elem->node.next)
    //     printf("Popped elem next node: %s\n", ((string_item *)popped_elem->node.next)->string);
    // if (popped_elem->node.prev)
    //     printf("Popped elem prev node: %s\n", ((string_item *)popped_elem->node.prev)->string);

    printf("\nPOPPED HEAD & TAIL LIST:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;

    // string_item *elem_at = (string_item *)get_elem_at((list_node *)string_elems, 0);

    // if (elem_at)
    //     printf("Elem at: %s\n", elem_at->string);

    // string_elems = string_elems_header;

    // insert_before_string_item(&string_elems, "Hello", 1);
    // insert_before_string_item(&string_elems, "Hell o", 2);
    // insert_before_string_item(&string_elems, "Hallo", 3);
    // insert_before_string_item(&string_elems, "Hallooooooooooooooo", 0);
    // insert_before_string_item(&string_elems, "Halo 5", 3);
    // insert_before_string_item(&string_elems, "Rebel Yell", 0);
    // insert_before_string_item(&string_elems, "Rebel Yellllllllllllooooooo", 0);
    // insert_before_string_item(&string_elems, "Rebel Yellllllll", 0);
    // insert_before_string_item(&string_elems, "Scream!", 1);

    insert_after_string_item(&string_elems, "Avenged Sevenfold", 0);
    insert_after_string_item(&string_elems, "The Offspring", 1);
    insert_after_string_item(&string_elems, "BVB", 11);
    insert_after_string_item(&string_elems, "Falling In Reverse", 11);
    insert_after_string_item(&string_elems, "Trivium", 13);

    insert_before_string_item(&string_elems, "Scream", 0);
    insert_before_string_item(&string_elems, "Scream scream scream", 1);

    string_elems_header = string_elems;

    printf("\nINSERT BEFORE & AFTER:\n");

    while (string_elems)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
    }

    string_elems = string_elems_header;

    // int num_of_shuffles = get_random_number_in_range(3, 5);

    // for (int i = 0; i < num_of_shuffles; i++)
    // {
    //     shuffle_list_elements((list_node **)&string_elems);
    // }

    shuffle_list_elements((list_node **)&string_elems, 1, 3);
    shuffle_list_elements((list_node **)&string_elems, 1, 4);
    shuffle_list_elements((list_node **)&string_elems, 2, 3);
    shuffle_list_elements((list_node **)&string_elems, 0, 3);
    shuffle_list_elements((list_node **)&string_elems, 1, 4);
    shuffle_list_elements((list_node **)&string_elems, 0, 1);
    shuffle_list_elements((list_node **)&string_elems, 0, 1);
    shuffle_list_elements((list_node **)&string_elems, 0, 5);
    shuffle_list_elements((list_node **)&string_elems, 1, 5);
    shuffle_list_elements((list_node **)&string_elems, 1, 3);
    shuffle_list_elements((list_node **)&string_elems, 0, 5);
    shuffle_list_elements((list_node **)&string_elems, 1, 4);

    string_elems_header = string_elems;

    printf("\nSHUFFLED ELEMENTS:\n");

    int count = 0;
    // int list_count = get_list_count((list_node *)string_elems);

    while (string_elems && count < 8)
    {
        printf("%s\n", string_elems->string);
        string_elems = (string_item *)string_elems->node.next;
        count++;
    }

    return 0;
}