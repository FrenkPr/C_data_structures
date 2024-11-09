// #include "set.h"
#include "dictionary.h"

void set_test()
{
    s_set *string_set = NULL;
    s_set *int_set = NULL;

    init_set((s_set **)&string_set, DEFAULT_HASHMAP_SIZE);
    init_set((s_set **)&int_set, DEFAULT_HASHMAP_SIZE);

    // set_insert_string(string_set, "ciao");
    // set_insert_string(string_set, "ciaoo");

    // set_find_string(string_set, "ciaoo");
    // set_find_string(string_set, "ciao");

    // set_remove_string(string_set, "ciaoo");

    // set_find_string(string_set, "ciao");
    // set_find_string(string_set, "ciaoo");

    set_insert_string(string_set, "ciaoo");

    set_find_string(string_set, "ciaoo");
    set_find_string(string_set, "ciao");

    set_find_int(int_set, 10);

    set_insert_int(int_set, 10);

    set_find_int(int_set, 10);

    // set_insert_int(string_set, 10);
    // set_insert_int(string_set, 10);

    // set_insert_int(string_set, 20);
    // set_insert_int(string_set, 1);

    // set_insert_int(string_set, 10);

    // set_find_int(string_set, 10);

    // set_remove_int(string_set, 10);

    // set_find_int(string_set, 10);

    // set_insert_int(string_set, 10);

    // set_find_int(string_set, 10);

    // set_remove_int(string_set, 10);

    // set_find_int(string_set, 10);
    // set_find_int(string_set, 20);
    // set_find_int(string_set, 1);
}

void dict_test()
{
    s_dict *weapons_dict = NULL;
    s_dict *tacticals_dict = NULL;
    dict_value_node *val = NULL;

    init_dict((s_dict **)&weapons_dict);
    init_dict((s_dict **)&tacticals_dict);

    // dict_value_node *val = dict_insert(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(200));
    // // val = dict_insert(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(100));
    // val = dict_update(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(100));

    dict_update(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(100));
    dict_update(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(200));
    dict_update(weapons_dict, (set_node *)get_new_string_set_node("ice"), (dict_value_node *)get_new_dict_int_value(200));
    dict_update(weapons_dict, (set_node *)get_new_string_set_node("storm"), (dict_value_node *)get_new_dict_int_value(500));

    dict_find(weapons_dict, (set_node *)get_new_string_set_node("fire"));
    dict_find(weapons_dict, (set_node *)get_new_string_set_node("fire"));

    dict_remove(weapons_dict, (set_node *)get_new_string_set_node("fire"));

    dict_update(weapons_dict, (set_node *)get_new_string_set_node("electricity"), (dict_value_node *)get_new_dict_int_value(400));

    dict_find(weapons_dict, (set_node *)get_new_string_set_node("fire"));
    val = dict_find(weapons_dict, (set_node *)get_new_string_set_node("fire"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    dict_update(weapons_dict, (set_node *)get_new_string_set_node("fire"), (dict_value_node *)get_new_dict_int_value(200));

    //print weapon values
    val = dict_find(weapons_dict, (set_node *)get_new_string_set_node("fire"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(weapons_dict, (set_node *)get_new_string_set_node("ice"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(weapons_dict, (set_node *)get_new_string_set_node("storm"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(weapons_dict, (set_node *)get_new_string_set_node("electricity"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }
    //end print weapon values

    //insert tactical elements
    dict_insert(tacticals_dict, (set_node *)get_new_string_set_node("grenade"), (dict_value_node *)get_new_dict_int_value(100));
    dict_insert(tacticals_dict, (set_node *)get_new_string_set_node("flashbang"), (dict_value_node *)get_new_dict_int_value(100));
    dict_insert(tacticals_dict, (set_node *)get_new_string_set_node("semtex"), (dict_value_node *)get_new_dict_int_value(200));
    dict_insert(tacticals_dict, (set_node *)get_new_string_set_node("molotov"), (dict_value_node *)get_new_dict_int_value(500));

    //print weapon values
    val = dict_find(tacticals_dict, (set_node *)get_new_string_set_node("grenade"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(tacticals_dict, (set_node *)get_new_string_set_node("flashbang"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(tacticals_dict, (set_node *)get_new_string_set_node("semtex"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }

    val = dict_find(tacticals_dict, (set_node *)get_new_string_set_node("molotov"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }
    //end print weapon values

    dict_remove(tacticals_dict, (set_node *)get_new_string_set_node("molotov"));
    dict_remove(tacticals_dict, (set_node *)get_new_string_set_node("molotov"));

    //checks if finds molotov element, after it has been removed
    val = dict_find(tacticals_dict, (set_node *)get_new_string_set_node("molotov"));

    if (val)
    {
        printf("%s: %d\n\n", val->name, ((dict_int_value_node *)val)->int_val);
    }
}

int main()
{
    // set_test();
    dict_test();

    printf("Press Enter key to continue");
    getchar();
    return 0;
}