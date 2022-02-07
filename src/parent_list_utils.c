#include "../inc/pathfinder.h"

static t_parent *create_parent(int prev_vert_index, int index, char *name, int weight)
{
    t_parent *new_node = malloc(sizeof(t_parent));
    new_node->prev_vert_index = prev_vert_index;
    new_node->index = index;
    new_node->name = mx_strdup(name);
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

void mx_push_back_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight)
{
    t_parent *new_node = create_parent(prev_vert_index, index, name, weight);
    t_parent *last_node = *list;

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

void mx_push_front_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight)
{
    t_parent *new_node = create_parent(prev_vert_index, index, name, weight);

    new_node->next = *list;

    *list = new_node;
}

void mx_pop_back_parent(t_parent **head)
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

    t_parent *tmp = *head;
    while (tmp && tmp->next->next != NULL)
    {
        tmp = tmp->next;
    }
    
    free(tmp->next);
    tmp->next = NULL;
}


void mx_clear_list_of_parent(t_parent **list)
{
    t_parent *node = *list;
    t_parent *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_strdel(&node->name);
        free(node);
        node = next;
    }

    *list = NULL;
}

bool mx_check_parent_dup(t_parent *list, int prev_vert_index, int index, char *name, int weight)
{
    t_parent *node = list;

    while (node != NULL)
    {
        if (node->index == index && !mx_strcmp(node->name, name) && node->weight == weight && node->prev_vert_index == prev_vert_index)
        {
            return true;
        }

        node = node->next;
    }

    return false;
}
