#include "../inc/pathfinder.h"

static t_path *create_path(int weight)
{
    t_path *new_node = malloc(sizeof(t_path));
    new_node->weight = weight;
    new_node->list = NULL;
    new_node->next = NULL;

    return new_node;
}

static void del_path_node(t_path **node)
{
    mx_clear_list_of_vert(&(*node)->list);
    free((*node));
}

void mx_push_front_path(t_path **list, int weight)
{
    t_path *new_node = create_path(weight);

    new_node->next = *list;

    *list = new_node;
}

void mx_clear_list_of_paths(t_path **list)
{
    t_path *node = *list;
    t_path *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        del_path_node(&node);
        node = next;
    }

    *list = NULL;
}

void mx_del_extra_paths(t_path **list, int weight)
{
    t_path *node = (*list)->next;
    t_path *prev = *list;

    if (node == NULL)
    {
        if (prev->weight > weight)
        {
            del_path_node(&prev);
        }
        return;
    }

    while (node->next != NULL)
    {
        if (node->weight > weight)
        {
            prev->next = node->next;
            del_path_node(&node);
            node = prev->next;
            continue;
        }

        prev = prev->next;
        node = node->next;
    }

    //last node
    if (node->weight > weight)
    {
        prev->next = NULL;
        del_path_node(&node);
    }

    //first node
    node = *list;
    if (node->weight > weight)
    {
        (*list) = (*list)->next;
        del_path_node(&node);
    }
}

int mx_list_of_paths_size(t_path *list)
{
    t_path *node = list;
    int size = 0;

    while (node != NULL)
    {
        node = node->next;
        size++;
    }

    return size;
}

void mx_reset_weight_of_path(t_path **path)
{
    t_vertex *node = (*path)->list;
    int new_weight = 0;
    while (node != NULL)
    {
        new_weight += node->weight;
        node = node->next;
    }
    (*path)->weight = new_weight;
}

bool mx_is_path_saved(t_path *paths, t_vertex *new_path)
{
    t_path *path = paths;

    while (path != NULL)
    {
        t_vertex *list = paths->list;
        t_vertex *new_list = new_path;

        bool is_saved = true;

        if (mx_list_of_vert_size(list) != mx_list_of_vert_size(new_list))
        {
            is_saved = false;
        }
        
        while (list != NULL && new_list != NULL && is_saved)
        {
            if (list->index != new_list->index)
            {
                is_saved =  false;
                break;
            }
            
            list = list->next;
            new_list = new_list->next;
        }

        if (is_saved)
        {
            return true;
        }
        

        path = path->next;
    }

    return false;
}


//bubble sorting
static void list_swap(t_vertex **list1, t_vertex **list2)
{
    t_vertex *f_list = NULL;
    mx_copy_list_of_vert(&f_list, (*list1));
    mx_copy_list_of_vert(&(*list1), (*list2));
    mx_copy_list_of_vert(&(*list2), f_list);
    mx_clear_list_of_vert(&f_list);
}

static bool pathcmp(t_vertex *list1, t_vertex *list2)
{
    bool is_greater = false;   
    while (list1 && list2)
    {
        if (list2->index > list1->index)
        {
            is_greater = true;
        }

        if (list1->index > list2->index && !is_greater)
        {
            return true;
        }

        list1 = list1->next;
        list2 = list2->next;
    }
    return false;
}

t_path *mx_sort_paths_list(t_path *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    t_path *node1 = list;
    t_path *node2 = NULL;
    int noSwap = 0;
    int tmp_i;

    while (!noSwap)
    {
        noSwap = 1;
        node1 = list;

        while (node1->next != node2)
        {
            if (pathcmp(node1->list, node1->next->list))
            {
                list_swap(&node1->list, &node1->next->list);

                tmp_i = node1->weight;
                node1->weight = node1->next->weight;
                node1->next->weight = tmp_i;

                noSwap = 0;
            }
            node1 = node1->next;
        }
        node2 = node1;
    }
    return list;
}
