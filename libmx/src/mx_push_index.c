#include "../inc/libmx.h"

void mx_push_index(t_list **list, void *data, int index)
{
    if (index <= 0)
    {
        mx_push_front(list, data);
        return;
    }

    t_list *node = *list;
    for (int i = 0; i <= index; i++)
    {
        if (node == NULL)
        {
            mx_push_back(list, data);
            return;
        }
        if (i == index - 1)
        {
            t_list *next = node->next;
            node->next = mx_create_node(data);
            node->next->next = next;
            return;
        }
        
        node = node->next;
    }
}
