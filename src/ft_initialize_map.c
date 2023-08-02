/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:16:10 by ivar              #+#    #+#             */
/*   Updated: 2023/08/02 19:07:19 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	set_map_size(int input_fd, t_map_info *map)
{
	char	ch;
	int		col;
	int		row;

	map->col = 0;
	col = 0;
	row = 0;
	while (read(input_fd, &ch, sizeof(ch)) == sizeof(ch))
	{
		if (ch == '\n')
		{
			row++;
			if (col > map->col)
				map->col = col;
			col = 0;
		}
		else
			col++;
	}
	if (map->col == 0 || map->row == 0 || row != map->row)
	{
		write(1, "Map Error!\n", 11);
		return (0);
	}
	return (1);
}

int	set_matrix_element(t_map_info *map, char ch, int row, int col)
{
	if (ch == map->empty)
		map->matrix[row][col] = -1;
	else if (ch == map->obstacle)
		map->matrix[row][col] = -2;
	else
	{
		write(1, "Map Error!\n", 11);
		return (0);
	}
	if (!(map->empty != map->full && map->empty != map->obstacle && map->obstacle != map->full && map->empty > 31 && map->obstacle > 31 && map->full > 31))
	{
		write(1, "Map Error!\n", 11);
		return (0);
	}
	return (1);
}

void	set_map_info(int input_fd, t_map_info *map)
{
	char	ch;
	char	str[64];
	int		i;

	i = 0;
	while (read(input_fd, &ch, sizeof(ch)))
	{
		if (ch == '\n')
			break ;
		else
			str[i++] = ch;
	}
	i = -1;
	map->row = 0;
	while (str[i] <= '9' && str[++i] >= '0')
		map->row = (str[i] - '0') + (map->row * 10);
	map->empty = str[i];
	map->obstacle = str[i + 1];
	map->full = str[i + 2];
}

int	set_map_matrix(int input_fd, t_map_info *map)
{
	int		row;
	int		col;
	char	ch;

	row = 0;
	col = 0;
	set_map_info(input_fd, map);
	map->matrix = (int **)malloc(map->row * sizeof(int *));
	while (row < map->row)
	{
		map->matrix[row] = (int *)malloc(map->col * sizeof(int));
		col = 0;
		while (col < map->col)
		{
			read(input_fd, &ch, sizeof(ch));
			if (!set_matrix_element(map, ch, row, col))
				return (0);
			col++;
		}
		read(input_fd, &ch, sizeof(ch));
		row++;
	}
	return (1);
}

int	initialize_map(t_map_info *map, char *file_name)
{
	int	input_fd;

	input_fd = open(file_name, 0x0000);
	if (input_fd == -1)
	{
		write(2, "Open Error\n", 13);
		return (0);
	}
	set_map_info(input_fd, map);
	if (!set_map_size(input_fd, map))
		return (0);
	close(input_fd);
	input_fd = open(file_name, 0x0000);
	if (input_fd == -1)
	{
		write(2, "Open Error\n", 13);
		return (0);
	}
	if (!set_map_matrix(input_fd, map))
		return (0);
	return (1);
}
