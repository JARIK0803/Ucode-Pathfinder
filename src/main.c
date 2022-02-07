#include "../inc/pathfinder.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        mx_printerr(TEXT_USAGE);
        exit(0);
    }

    char const *filename = argv[1];
    char *str_file = mx_file_to_str(filename);
    char **islands_names;
    t_graph *graph = NULL;

    if (str_file == NULL)
    {
        mx_error_file_not_exist(filename);
    }

    if (mx_strlen(str_file) == 0)
    {
        mx_error_file_empty(filename);
    }

    islands_names = mx_parse_file(str_file, &graph);

    mx_pathfinder(graph, islands_names);

    mx_strdel(&str_file);
    mx_del_strarr(&islands_names);
    mx_clear_graph(&graph);

    return 0;
}
