/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_drawing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:16:30 by ivar              #+#    #+#             */
/*   Updated: 2023/08/01 20:16:31 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_find_max(t_map_info *map, int *center)
{
	int	row;
	int	col;
	int	current;

	current = 0;
	row = 1;
	while (row < map->row)
	{
		col = 1;
		while (col < map->col)
		{
			if (map->matrix[row][col] > current)
			{
				current = map->matrix[row][col];
				center[0] = row;
				center[1] = col;
			}
			col++;
		}
		row++;
	}
	return (current);
}

int	odd_or_even(t_map_info *map, int *center, int max)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->row)
	{
		col = 0;
		while (col < map->col)
		{
			if (map->matrix[row][col] == max && map->matrix[row + 1][col] == max
				&& map->matrix[row][col + 1] == max && map->matrix[row + 1][col
				+ 1] == max)
			{
				center[0] = row;
				center[1] = col;
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}

void	draw_square(t_map_info *map)
{
	int	row;
	int	col;
	int	center[2];
	int	start;
	int	end;

	start = ft_find_max(map, center) - 1;
	end = ft_find_max(map, center) - 1;
	if (odd_or_even(map, center, ft_find_max(map, center)))
		end++;
	row = center[0] - start;
	while (row <= center[0] + end)
	{
		col = center[1] - start;
		while (col <= center[1] + end)
		{
			map->matrix[row][col] = -3;
			col++;
		}
		row++;
	}
}
