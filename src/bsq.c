#include "bsq.h"

void put_map_char(t_map_info *map ,int c)
{
    if(c == -1)
        write(1, &map->empty, 1);
    else if(c == -2)
        write(1, &map->obstacle, 1);
    else if(c == -3)
        write(1, &map->full, 1);
    else
    {
        char a = c + '0';
        write(1, &a, 1);
    }
}

void print_map(t_map_info *map)
{
    int row;
    int col;

    row = 0;
    while (row < map->row){
        col = 0;
        while (col < map->col){
            put_map_char(map, map->matrix[row][col]);
            col++;
        }
        row++;
        write(1, "\n", 1);
    }
}

void remove_numbers(t_map_info *map)
{
    int row;
    int col;
    
    row = 0;
    while (row < map->row)
    {
        col = 0;
        while (col < map->col)
        {
            if(map->matrix[row][col] > 0)
                map->matrix[row][col] = -1;
            col++;
        }
        row++;
    }
}

int handle_map(t_map_info *map)
{
    (void)map;
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    t_map_info map;

    i = 1;
    if(argc == 1)
    {
        if(handle_map(&map))
        {
            put_numbers(&map);
            draw_square(&map);
            remove_numbers(&map);
            print_map(&map);
        }
    }
    while (i < argc)
    {
        if(initialize_map(&map, argv[i]))
        {
            put_numbers(&map);
            draw_square(&map);
            remove_numbers(&map);
            print_map(&map);
        }
        i++;
        if(i < argc)
            write(1,"\n",1);
    }
}