#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_map_info 
{
    int row;
    int col;
    char empty;
    char obstacle;
    char full;
    int **matrix;
} 
t_map_info;

#pragma region [INITIALIZE MAP]

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

#pragma endregion

#pragma region [READ MAP]

int look_around(t_map_info *map, int row, int col, int nbr)
{
    int i;
    int j;

    i = row - 1;
    while (i <= row + 1)
    {
        j = col - 1;
        while (j <= col + 1)
        {
            if (i >= 0 && i < map->row && j >= 0 && j < map->col)
                if(!(i == row && j == col) && map->matrix[i][j] == nbr)
                    return 1;
            j++;
        }
        i++;
    }
    return 0;
}

void put_corner(t_map_info *map)
{
    int row;
    int col;

    row = 0;
    while (row < map->row)
    {
        col = 0;
        while (col < map->col)
        {
            if((row == 0 || col == 0 || row == map->row - 1 || col == map->col - 1) && map->matrix[row][col] == -1)
                map->matrix[row][col] = 1;
            col++;
        }
        row++;
    }
}

void put_obstacle_around(t_map_info *map)
{
    int row;
    int col;

    row = 1;
    while (row < map->row)
    {
        col = 1;
        while (col < map->col)
        {
            if(look_around(map, row, col, -2) && map->matrix[row][col] == -1)
                map->matrix[row][col] = 1;
            col++;
        }
        row++;
    }
}

int check_empty_cell(t_map_info *map)
{   
    int row;
    int col;

    row = 1;
    while (row < map->row)
    {
        col = 1;
        while (col < map->col)
        {
            if(map->matrix[row][col] == -1)
                return 1;
            col++;
        }
        row++;
    }
    return 0;
}

void put_numbers(t_map_info *map)
{
    int row;
    int col;
    int nbr;

    nbr = 2;
    put_corner(map);
    put_obstacle_around(map);
    while (check_empty_cell(map))
    {
        row = 1;
        while (row < map->row - 1)
        {
            col = 1;
            while (col < map->col - 1)
            {
                if (map->matrix[row][col] == -1 && look_around(map, row, col, nbr - 1) == 1) 
                    map->matrix[row][col] = nbr;
                col++;
            }
            row++;
        }
        nbr++;
    }
}

#pragma endregion

#pragma region [DRAW SQUARE]

int ft_find_max(t_map_info *map, int *center)
{
    int row;
    int col;
    int current;

    current = 0;
    row = 1;
    while (row < map->row)
    {
        col = 1;
        while (col < map->col)
        {
            if(map->matrix[row][col] > current)
            {
                current = map->matrix[row][col];
                center[0] = row;
                center[1] = col;
            }
            col++;
        }
        row++;
    }
    return current;
}

int odd_or_even(t_map_info *map, int *center, int max)
{
    int row;
    int col;

    row = 0;
    while (row < map->row)
    {
        col = 0;
        while (col < map->col)
        {
            if(map->matrix[row][col] == max && map->matrix[row + 1][col] == max &&
                map->matrix[row][col + 1] == max && map->matrix[row + 1][col + 1] == max)
            {
                center[0] = row;
                center[1] = col;
                return 1;
            }
            col++;
        } 
        row++;
    }
    return 0;
}

void draw_square(t_map_info *map)
{
    int row;
    int col;
    int center[2];
    int max_nbr;
    int start;
    int end;

    max_nbr = ft_find_max(map, center);
    start = max_nbr - 1;
    end = max_nbr - 1;
    if(odd_or_even(map, center, max_nbr))
        end++;
    row = center[0] - start;
    while(row <= center[0] + end) {
        col = center[1] - start;
        while(col <= center[1] + end) {
            map->matrix[row][col] = -3;
            col++;
        }
        row++;
    }
}

#pragma endregion

#pragma region [MAIN]

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

#pragma endregion