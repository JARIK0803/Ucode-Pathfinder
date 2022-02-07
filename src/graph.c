#include "../inc/pathfinder.h"

t_graph *mx_create_graph(int V)
{
    t_graph *graph = (t_graph *)malloc(sizeof(t_graph));
    graph->size = V;

    graph->array = (t_adj_list **)malloc(V * sizeof(t_adj_list));

    for (int i = 0; i < V; ++i)
    {
        graph->array[i] = malloc(sizeof(*(graph->array[i])));
        graph->array[i]->list = NULL;
    }

    return graph;
}

void mx_add_edge(t_graph *graph, char *src_name, int src_index, char *dst_name, int dst_index, int weight)
{
    mx_push_back_vertex(&graph->array[src_index]->list, dst_index, dst_name, weight);
    mx_push_back_vertex(&graph->array[dst_index]->list, src_index, src_name, weight);
}

void mx_clear_graph(t_graph **graph)
{
    for (int i = 0; i < (*graph)->size; i++)
    {
        mx_clear_list_of_vert(&(*graph)->array[i]->list);
        free((*graph)->array[i]);
    }

    free((*graph)->array);
    free(*graph);
}
