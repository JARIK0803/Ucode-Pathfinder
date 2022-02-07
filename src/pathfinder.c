#include "../inc/pathfinder.h"

void mx_pathfinder(t_graph *graph, char **islands_names)
{
    for (int i = 0; i < graph->size; i++)
    {
        t_source *path_tree = mx_create_path_tree(graph->size, islands_names, i);

        mx_dijkstra(graph, i, islands_names[i], &path_tree);
        mx_sort_path_tree(path_tree);
        mx_print_paths(path_tree, i);

        mx_clear_path_tree(&path_tree);
    }
}
