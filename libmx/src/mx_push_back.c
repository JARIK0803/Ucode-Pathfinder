#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data)
{
    t_list *new_node = mx_create_node(data);
    t_list *last_node = *list;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }

    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }

    last_node->next = new_node;
}
