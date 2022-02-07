#include "../inc/pathfinder.h"

static void print_boundary()
{
    for (size_t i = 0; i < 40; i++)
    {
        mx_printchar('=');
    }
    mx_printchar('\n');
}

void mx_print_paths(t_source *path_tree, int src)
{
    for (int i = src + 1; i < path_tree->size; i++)
    {
        t_path *paths = path_tree->dests[i].paths;

        while (paths != NULL)
        {
            print_boundary();

            mx_printstr("Path: ");
            mx_printstr(path_tree->src_name);
            mx_printstr(" -> ");
            mx_printstr(path_tree->dests[i].name);
            mx_printstr("\n");

            mx_printstr("Route: ");
            mx_printstr(path_tree->src_name);
            mx_printstr(" -> ");
            t_vertex *vert = paths->list;
            while (vert != NULL)
            {
                mx_printstr(vert->name);
                if (vert->next != NULL)
                {
                    mx_printstr(" -> ");
                }
                vert = vert->next;
            }
            mx_printstr("\n");

            mx_printstr("Distance: ");
            vert = paths->list;
            if (vert->next != NULL)
            {
                while (vert != NULL)
                {
                    mx_printint(vert->weight);

                    if (vert->next != NULL)
                    {
                        mx_printstr(" + ");
                    }
                    vert = vert->next;
                }
                mx_printstr(" = ");
            }
            mx_printint(paths->weight);

            mx_printstr("\n");

            print_boundary();

            paths = paths->next;
        }
    }
}
