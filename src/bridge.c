#include "../inc/pathfinder.h"

t_bridge *mx_create_bridge(char *src, char *dst, int weight)
{
    t_bridge *new_node = malloc(sizeof(t_bridge));
    new_node->src = mx_strdup(src);
    new_node->dst = mx_strdup(dst);
    new_node->weight = weight;

    return new_node;
}

static void del_bridge_node(t_bridge **node)
{
    mx_strdel(&(*node)->src);
    mx_strdel(&(*node)->dst);
    free((*node));
}

void mx_clear_bridges(t_bridge ***bridges, int num_of_bridges)
{
    for (int i = 0; i < num_of_bridges; i++)
    {
        del_bridge_node(&(*bridges)[i]);
    }
    free((*bridges));
}

void mx_check_bridge_dup(t_bridge **bridges, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (!mx_strcmp(bridges[i]->src, bridges[j]->src) && !mx_strcmp(bridges[i]->dst, bridges[j]->dst))
            {
                mx_error_duplicate_bridges();
            }
        }
    }
}
