#include "../inc/pathfinder.h"

static void set_path(t_parent *u_node, t_vertex *current_path, t_source *path_tree, t_parent **parents, int dest_index)
{   
    int u_index = u_node->prev_vert_index;

    if (u_index == -1)
    {
        if (!mx_is_path_saved(path_tree->dests[dest_index].paths, current_path))
        {   
            mx_push_front_path(&path_tree->dests[dest_index].paths, 0);
            mx_copy_list_of_vert(&path_tree->dests[dest_index].paths->list, current_path);
            mx_reset_weight_of_path(&path_tree->dests[dest_index].paths);
        }

        return;
    }
    mx_push_front_vertex(&current_path, u_node->index, u_node->name, u_node->weight);
    
    t_parent *parent_node = parents[u_index];
    while (parent_node != NULL)
    {
        set_path(parent_node, current_path, path_tree, parents, dest_index);
        parent_node = parent_node->next;   
    }

    mx_pop_front_vertex(&current_path);
}

void mx_process_path(t_source *path_tree, t_parent **parents, int index, int weight_of_shortest)
{
    t_parent *u = parents[index];
    t_vertex *current_path = NULL;

    while (u != NULL)
    {
        set_path(u, current_path, path_tree, parents, index);
        u = u->next;
    }

    if (mx_list_of_paths_size(path_tree->dests[index].paths) > 1)
    {
        mx_del_extra_paths(&path_tree->dests[index].paths, weight_of_shortest);
    }

    mx_clear_list_of_vert(&current_path);
}
