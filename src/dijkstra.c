#include "../inc/pathfinder.h"

static void clear_parents(t_parent **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        mx_clear_list_of_parent(&arr[i]);
    }
    free(arr);
}

void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree)
{
    int graph_size = graph->size;

    t_adj_list *pq = (t_adj_list *)malloc(sizeof(t_adj_list));
    pq->list = NULL;

    t_parent **parents = malloc(graph_size * sizeof(*parents));
    long path_weight[graph_size];

    for (int i = 0; i < graph_size; i++)
    {
        path_weight[i] = __INT_MAX__;
        parents[i] = NULL;
    }
    mx_push_back_parent(&parents[src_index], -1, src_index, src_name, 0);
    path_weight[src_index] = 0;

    mx_push_back_vertex(&pq->list, src_index, src_name, 0);

    while (pq->list != NULL)
    {
        int u = pq->list->index;
        mx_pop_front_vertex(&pq->list);

        t_vertex *adj_vertex = graph->array[u]->list;

        while (adj_vertex != NULL)
        {
            int v = adj_vertex->index;
            if (path_weight[u] != __INT_MAX__ && adj_vertex->weight + path_weight[u] <= path_weight[v])
            {
                if (path_weight[v] == path_weight[u] + adj_vertex->weight)
                {
                    path_weight[v] = path_weight[u] + adj_vertex->weight;
                } 
                else
                {
                    path_weight[v] = path_weight[u] + adj_vertex->weight;
                    mx_pop_back_parent(&parents[v]);
                }
                

                if (!mx_check_parent_dup(parents[v], u, adj_vertex->index, adj_vertex->name, adj_vertex->weight))
                {
                    mx_push_front_parent(&parents[v], u, adj_vertex->index, adj_vertex->name, adj_vertex->weight);
                }

                mx_push_back_vertex(&pq->list, v, adj_vertex->name, path_weight[v]);
            }
            adj_vertex = adj_vertex->next;
        }
    }

    for (int i = 0; i < graph_size; i++)
    {
        mx_process_path(*path_tree, parents, i, path_weight[i]);
    }

    clear_parents(parents, graph_size);
    mx_clear_list_of_vert(&pq->list);
    free(pq);
}
