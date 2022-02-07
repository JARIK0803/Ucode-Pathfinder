#include "../inc/libmx.h"

void mx_pop_front(t_list **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }
    
    t_list *tmp = *head;
    *head = (*head)->next;

    free(tmp);
}
