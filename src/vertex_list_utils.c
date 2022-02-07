#include "../inc/pathfinder.h"

static t_vertex *create_vertex(int index, char *name, int weight)
{
    t_vertex *new_node = malloc(sizeof(t_vertex));
    new_node->index = index;
    new_node->name = mx_strdup(name);
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

static void del_vertex_node(t_vertex **node)
{
    mx_strdel(&(*node)->name);
    free((*node));
}

void mx_push_back_vertex(t_vertex **list, int index, char *name, int weight)
{
    t_vertex *new_node = create_vertex(index, name, weight);
    t_vertex *last_node = *list;

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

void mx_push_front_vertex(t_vertex **list, int index, char *name, int weight)
{
    t_vertex *new_node = create_vertex(index, name, weight);

    new_node->next = *list;

    *list = new_node;
}

void mx_pop_front_vertex(t_vertex **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    if ((*head)->next == NULL)
    {
        del_vertex_node(&(*head));
        *head = NULL;
        return;
    }

    t_vertex *tmp = *head;
    *head = (*head)->next;

    del_vertex_node(&tmp);
}

void mx_copy_list_of_vert(t_vertex **dest, t_vertex *src)
{
    if (dest != NULL && *dest != NULL)
    {
        mx_clear_list_of_vert(&(*dest));
        *dest = NULL;
    }

    while (src)
    {
        mx_push_back_vertex(dest, src->index, src->name, src->weight);
        src = src->next;
    }
}

int mx_list_of_vert_size(t_vertex *list)
{
    t_vertex *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}

void mx_clear_list_of_vert(t_vertex **list)
{
    t_vertex *node = *list;
    t_vertex *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_strdel(&node->name);
        free(node);
        node = next;
    }

    *list = NULL;
}
