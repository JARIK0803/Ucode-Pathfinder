#include "../inc/libmx.h"

void mx_pop_index(t_list **list, int index)
{
    if (index <= 0)
    {
        mx_pop_front(list);
        return;
    }

    t_list *node = *list;
    t_list *prev = NULL;
    for (int i = 0; i <= index; i++)
    {
        if (node == NULL)
        {
            mx_pop_back(list);
            return;
        }
        if (i == index - 1)
        {
            prev = node;
        }
        if (i == index)
        {
            t_list *next = node->next;
            prev->next = next;
            free(node);
            return;
        }
        node = node->next;
    }
}
