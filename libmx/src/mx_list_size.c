#include "../inc/libmx.h"

int mx_list_size(t_list *list)
{
    t_list *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}
