#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

typedef struct s_vertex
{
    int index;
    char *name;
    int weight;
    struct s_vertex *next;
}              t_vertex;

typedef struct s_adj_list
{
    t_vertex *list;
}              t_adj_list;

typedef struct s_graph
{
    int size;
    t_adj_list **array;
}              t_graph;

typedef struct s_bridge
{
    char *src;
    char *dst;
    int weight;
}              t_bridge;

typedef struct s_parent
{
    int prev_vert_index;
    int index;
    char *name;
    int weight;
    struct s_parent *next;
}              t_parent;

typedef struct s_path
{
    int weight;
    t_vertex *list;
    struct s_path *next;
}              t_path;

typedef struct s_destination
{
    char *name;
    t_path *paths;
}              t_destination;

typedef struct s_source
{
    char *src_name;
    int size;
    t_destination *dests;
}              t_source;

//errors
void mx_error_file_not_exist(const char *filename);
void mx_error_file_empty(const char *filename);
void mx_error_line_not_valid(int index);
void mx_error_invalid_num_of_islands();
void mx_error_duplicate_bridges();
void mx_error_sum_of_bridges_len_is_too_big();

//vertex_list_utils
void mx_push_back_vertex(t_vertex **list, int index, char *name, int weight);
void mx_push_front_vertex(t_vertex **list, int index, char *name, int weight);
void mx_pop_front_vertex(t_vertex **head);
int mx_list_of_vert_size(t_vertex *list);
void mx_copy_list_of_vert(t_vertex **dest, t_vertex *src);
void mx_clear_list_of_vert(t_vertex **list);

//parent_list_utils
void mx_push_back_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight);
void mx_push_front_parent(t_parent **list, int prev_vert_index, int index, char *name, int weight);
void mx_pop_back_parent(t_parent **head);
void mx_clear_list_of_parent(t_parent **list);
bool mx_check_parent_dup(t_parent *list, int prev_vert_index, int index, char *name, int weight);

//path_list_utils
void mx_push_front_path(t_path **list, int weight);
void mx_del_extra_paths(t_path **list, int weight);
int mx_list_of_paths_size(t_path *list);
void mx_reset_weight_of_path(t_path **path);
bool mx_is_path_saved(t_path *paths, t_vertex *new_path);
t_path *mx_sort_paths_list(t_path *list);
void mx_clear_list_of_paths(t_path **list);

//bridge
t_bridge *mx_create_bridge(char *src, char *dst, int weight);
void mx_clear_bridges(t_bridge ***bridges, int num_of_bridges);
void mx_check_bridge_dup(t_bridge **bridges, int size);

//graph
t_graph *mx_create_graph(int V);
void mx_add_edge(t_graph *graph, char *src_name, int src_index, char *dst_name, int dst_index, int weight);
void mx_clear_graph(t_graph **graph);

//paht_tree
t_source *mx_create_path_tree(int size, char **islands_names, int src_index);
void mx_sort_path_tree(t_source *path_tree);
void mx_clear_path_tree(t_source **path_tree);

char **mx_parse_file(char *src, t_graph **graph);
void mx_pathfinder(t_graph *graph, char **islands_names);
void mx_dijkstra(t_graph *graph, int src_index, char *src_name, t_source **path_tree);
void mx_process_path(t_source *path_tree, t_parent **parents, int index, int weight);
void mx_print_paths(t_source *path_tree, int src);

static const char* TEXT_USAGE = "usage: ./pathfinder [filename]\n";

#endif
