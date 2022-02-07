#include "../inc/pathfinder.h"

void mx_error_file_not_exist(const char *filename)
{
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
    exit(-1);
}

void mx_error_file_empty(const char *filename)
{
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
    exit(-1);
}

void mx_error_line_not_valid(int index)
{
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(index));
    mx_printerr(" is not valid\n");
    exit(-1);
}

void mx_error_invalid_num_of_islands()
{
    mx_printerr("error: invalid number of islands\n");
    exit(-1);
}

void mx_error_duplicate_bridges()
{
    mx_printerr("error: duplicate bridges\n");
    exit(-1);
}

void mx_error_sum_of_bridges_len_is_too_big()
{
    mx_printerr("error: sum of bridges lengths is too big\n");
    exit(-1);
}
