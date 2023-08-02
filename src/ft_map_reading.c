/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:16:15 by ivar              #+#    #+#             */
/*   Updated: 2023/08/02 19:02:05 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	look_around(t_map_info *map, int row, int col, int nbr)
{
	int	i;
	int	j;

	i = row - 1;
	while (i <= row + 1)
	{
		j = col - 1;
		while (j <= col + 1)
		{
			if (i >= 0 && i < map->row && j >= 0 && j < map->col)
				if (!(i == row && j == col) && map->matrix[i][j] == nbr)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	put_corner(t_map_info *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->row)
	{
		col = 0;
		while (col < map->col)
		{
			if(map->matrix[row][col] == -1)
				if ((row == 0 || col == 0 || row == map->row - 1 || col == map->col- 1))
					map->matrix[row][col] = 1;
			col++;
		}
		row++;
	}
}

void	put_obstacle_around(t_map_info *map)
{
	int	row;
	int	col;

	row = 1;
	while (row < map->row)
	{
		col = 1;
		while (col < map->col)
		{
			if (map->matrix[row][col] == -1)
				if(look_around(map, row, col, -2))
					map->matrix[row][col] = 1;
			col++;
		}
		row++;
	}
}

int	check_empty_cell(t_map_info *map)
{
	int	row;
	int	col;

	row = 1;
	while (row < map->row)
	{
		col = 1;
		while (col < map->col)
		{
			if (map->matrix[row][col] == -1)
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

void	put_numbers(t_map_info *map)
{
	int	row;
	int	col;
	int	nbr;

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
				if (map->matrix[row][col] == -1)
					if(look_around(map, row, col,nbr - 1) == 1)
						map->matrix[row][col] = nbr;
				col++;
			}
			row++;
		}
		nbr++;
	}
}
