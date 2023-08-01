#include "bsq.h"

int set_map_size(int input_fd, t_map_info *map)
{
    char ch;
    int col;

    map->col = 0;
    col = 0;
    while (read(input_fd, &ch, sizeof(ch)) == sizeof(ch)) 
    {
        if (ch == '\n') 
        {
            if (col > map->col) 
            {
                map->col = col;
            }
            col = 0;
        } else {
            col++;
        }
    }
    if(map->col == 0)
    {
        write(1, "Map Error!\n", 11);
        return 0;
    }
    return 1;
}

int set_matrix_element(t_map_info *map, char ch, int row, int col) 
{
    if (ch == map->empty)
        map->matrix[row][col] = -1;
    else if (ch == map->obstacle)
        map->matrix[row][col] = -2;
    else {
        write(1, "Map Error!\n", 11);
        return 0;
    }
    return 1;
}

void set_map_info(int input_fd, t_map_info *map)
{
    char ch;
    char str[64];
    int i = 0;

    while (read(input_fd, &ch, sizeof(ch))) 
    {
        if (ch == '\n') 
        {
            break;
        }
        else
        {
            str[i] = ch;
            i++;
        }
    }
    map->empty = str[i - 3];
    map->obstacle = str[i - 2];
    map->full = str[i - 1];
    map->row = atoi(str);
}

int set_map_matrix(int input_fd, t_map_info *map)
{
    int row;
    int col;
    char ch;

    row = 0;
    col = 0;
    set_map_info(input_fd, map);
    map->matrix = (int **)malloc(map->row * sizeof(int *));
    
    while(row < map->row)
    {
        map->matrix[row] = (int *)malloc(map->col * sizeof(int));
        col = 0;
        while(col < map->col)
        {
            read(input_fd, &ch, sizeof(ch));
            if(!set_matrix_element(map, ch, row, col))
                return 0;
            col++;
        }
        read(input_fd, &ch, sizeof(ch));
        row++;
    }
    return 1;
}

int initialize_map(t_map_info *map, char *file_name)
{
    int input_fd;

    input_fd = open(file_name, 0x0000);
    if (input_fd == -1) 
    {
        write(2, "Open Error\n", 13);
        return 0;
    }
    set_map_info(input_fd ,map);
    if(!set_map_size(input_fd ,map))
        return 0;
    close(input_fd);
    input_fd = open(file_name, 0x0000);
    if (input_fd == -1) 
    {
        write(2, "Open Error\n", 13);
        return 0;
    }
    if(!set_map_matrix(input_fd, map))
        return 0;
    return 1;
}