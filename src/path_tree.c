#include "../inc/pathfinder.h"

t_source *mx_create_path_tree(int size, char **islands_names, int src_index)
{
    t_source *path_tree = (t_source *)malloc(sizeof(t_source));
    path_tree->size = size;
    path_tree->src_name = mx_strdup(islands_names[src_index]);

    path_tree->dests = (t_destination *)malloc(size * sizeof(*(path_tree->dests)));
    for (int i = 0, j = 0; i < size; i++, j++)
    {
        path_tree->dests[i].name = mx_strdup(islands_names[i]);
        path_tree->dests[i].paths = NULL;
        // path_tree->dests[i] = malloc(sizeof(*(path_tree->dests[i])));
    }

    return path_tree;
}

void mx_sort_path_tree(t_source *path_tree)
{
    for (int i = 0; i < path_tree->size; i++)
    {
        mx_sort_paths_list(path_tree->dests[i].paths);
    }
}

void mx_clear_path_tree(t_source **path_tree)
{
    for (int i = 0; i < (*path_tree)->size; i++)
    {
        mx_clear_list_of_paths(&(*path_tree)->dests[i].paths);
        mx_strdel(&(*path_tree)->dests[i].name);
    }

    mx_strdel(&(*path_tree)->src_name);
    free((*path_tree)->dests);
    free((*path_tree));
}
