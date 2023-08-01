#ifndef BSQ_H
#define BSQ_H
#include <fcntl.h> //Dosya kontrol islemleri icin kullanilir .(open , close)
#include <unistd.h> //write , read
#include <stdlib.h> //malloc ,free

typedef struct s_map_info 
{
    int row;
    int col;
    char empty;
    char obstacle;
    char full;
    int **matrix;
} t_map_info;

int set_map_size(int input_fd, t_map_info *map);
int set_matrix_element(t_map_info *map, char ch, int row, int col);
void set_map_info(int input_fd, t_map_info *map);
int set_map_matrix(int input_fd, t_map_info *map);
int initialize_map(t_map_info *map, char *file_name);
int look_around(t_map_info *map, int row, int col, int nbr);
void put_corner(t_map_info *map);
void put_obstacle_around(t_map_info *map);
int check_empty_cell(t_map_info *map);
void put_numbers(t_map_info *map);
int ft_find_max(t_map_info *map, int *center);
int odd_or_even(t_map_info *map, int *center, int max);
void draw_square(t_map_info *map);

#endif