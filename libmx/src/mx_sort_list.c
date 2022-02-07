#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *))
{
    if (lst == NULL)
    {
        return NULL;
    }

    t_list *node1 = lst;
    t_list *node2 = NULL;
    int noSwap = 0;
    void *tmp;

    while(!noSwap)
    {
        noSwap = 1;
        node1 = lst;

        while (node1->next != node2)
        {
            if (cmp(node1->data, node1->next->data))
            {
                tmp = node1->data;
                node1->data = node1->next->data;
                node1->next->data = tmp;
                noSwap = 0;
            }
            node1 = node1->next;
        }
        node2 = node1;
    }

    return lst;
}
