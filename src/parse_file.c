#include "../inc/pathfinder.h"

static bool is_number_valid(char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        if (!mx_isdigit(str[i]))
        {
            return false;
        }
        i++;
    }

    if (i == 0)
    {
        return false;
    }

    return true;
}

static void check_number_valid(char *line, int line_index)
{
    if (!is_number_valid(line) || mx_atoi(line) == 0)
    {
        mx_error_line_not_valid(line_index);
        exit(-1);
    }
}

static bool is_name_valid(char *str, int length)
{
    int i = 0;
    while (i < length)
    {
        if (!mx_isalpha(str[i]))
        {
            return false;
        }
        i++;
    }

    if (i == 0)
    {
        return false;
    }

    return true;
}

static void check_name_valid(char *line, char to_ch, int line_index)
{
    if (!is_name_valid(line, mx_get_char_index(line, to_ch)))
    {
        mx_error_line_not_valid(line_index);
        exit(-1);
    }
}

static bool is_new_island(char **islands, int num_of_islands, int islands_counter, char *island)
{
    for (int i = 0; i < islands_counter && i < num_of_islands; i++)
    {
        if (!mx_strcmp(islands[i], island))
        {
            return false;
        }
    }
    return true;
}

static void check_new_island(char **islands, int num_of_islands, int *islands_counter, char *island)
{
    if (is_new_island(islands, num_of_islands, *islands_counter, island))
    {
        if (*islands_counter < num_of_islands)
        {
            islands[*islands_counter] = mx_strdup(island);
        }
        (*islands_counter)++;
    }
}

static void add_len_of_bridge(int *sum_bridges_len, int bridge_len, bool *sum_overload)
{
    int tmp = *sum_bridges_len;
    *sum_bridges_len += bridge_len;

    if (tmp > *sum_bridges_len)
    {
        *sum_overload = true;
    }
}

static int count_bridges(char **lines)
{
    int i = 1;
    while (lines[i] != NULL)
    {
        i++;
    }
    return i - 1;
}

static int find_index(char **islands, char *island)
{
    for (int i = 0; islands[i] != NULL; i++)
    {
        if (!mx_strcmp(island, islands[i]))
        {
            return i;
        }
    }
    return -1;
}

static void build_graph(t_graph **graph, t_bridge **bridges, int num_of_bridges, char **islands, int num_of_islands)
{
    *graph = mx_create_graph(num_of_islands);

    for (int i = 0; i < num_of_bridges; i++)
    {
        int src_index = find_index(islands, bridges[i]->src);
        int dst_index = find_index(islands, bridges[i]->dst);

        mx_add_edge(*graph, bridges[i]->src, src_index, bridges[i]->dst, dst_index, bridges[i]->weight);
    }
}

char **mx_parse_file(char *src, t_graph **graph)
{
    char **lines = mx_strsplit(src, '\n');
    int num_of_bridges = count_bridges(lines);

    check_number_valid(lines[0], 1);

    int num_of_islands = mx_atoi(lines[0]);

    if (num_of_islands < 0)
    {
        mx_error_invalid_num_of_islands();
    }

    char **islands = malloc(sizeof(islands) * (num_of_islands + 1));
    islands[num_of_islands] = NULL;
    int islands_counter = 0;
    char *island1 = NULL;
    char *island2 = NULL;
    int bridge_len;

    int sum_bridges_len = 0;
    bool sum_overload = false;

    t_bridge **bridges = malloc(sizeof(bridges) * num_of_bridges);

    for (size_t i = 1; lines[i] != NULL; i++)
    {
        if (mx_count_substr(lines[i], "-") != 1)
        {
            mx_error_line_not_valid(i + 1);
        }

        char *line = lines[i];

        check_name_valid(line, '-', i + 1);
        island1 = mx_strndup(line, mx_get_char_index(line, '-'));
        line += mx_get_char_index(line, '-') + 1;

        check_name_valid(line, ',', i + 1);
        island2 = mx_strndup(line, mx_get_char_index(line, ','));
        line += mx_get_char_index(line, ',') + 1;

        check_number_valid(line, i + 1);
        bridge_len = mx_atoi(line);
        add_len_of_bridge(&sum_bridges_len, bridge_len, &sum_overload);

        if (!mx_strcmp(island1, island2))
        {
            mx_error_line_not_valid(i + 1);
        }

        bridges[i - 1] = mx_create_bridge(island1, island2, bridge_len);

        check_new_island(islands, num_of_islands, &islands_counter, island1);
        check_new_island(islands, num_of_islands, &islands_counter, island2);

        mx_strdel(&island1);
        mx_strdel(&island2);
    }

    if (islands_counter != num_of_islands)
    {
        mx_error_invalid_num_of_islands();
    }

    mx_check_bridge_dup(bridges, num_of_bridges);

    if (sum_overload)
    {
        mx_error_sum_of_bridges_len_is_too_big();
    }

    build_graph(graph, bridges, num_of_bridges, islands, num_of_islands);
    mx_clear_bridges(&bridges, num_of_bridges);

    mx_del_strarr(&lines);

    return islands;
}
