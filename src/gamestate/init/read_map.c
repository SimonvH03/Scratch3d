/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:35:08 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	map_size(
		t_grid *grid,
		char *const *content)
{
	int	x;
	int	y;
	int	max_x;

	x = 0;
	y = 0;
	max_x = 0;
	while (content[y])
	{
		x = ft_strlen(content[y]);
		if (x > max_x)
			max_x = x;
		++y;
	}
	grid->x_max = max_x;
	grid->y_max = y;
}

static int
	map_fill_row(
		t_grid *grid,
		const int y,
		const char *line)
{
	unsigned int	x;

	x = 0;
	while (line[x])
	{
		grid->tilemap[y][x] = -1;
		if (!ft_isalnum(line[x]) && line[x] != ' ')
		{
			printf("invalid map: only letters, digits and spaces allowed\n");
			return (RETURN_ERROR);
		}
		if (line[x] == ' ')
			grid->tilemap[y][x] = -1;
		if (ft_isdigit(line[x]))
			grid->tilemap[y][x] = line[x] - '0';
		else
			grid->tilemap[y][x] = line[x];
		++x;
	}
	while (x < grid->x_max)
	{
		grid->tilemap[y][x] = -1;
		++x;
	}
	return (RETURN_SUCCESS);
}

int
	read_map(
		t_grid *grid,
		char *const *content)
{
	unsigned int	y;

	map_size(grid, content);
	grid->tilemap = (int **)ft_calloc(grid->y_max + 1, sizeof(int *));// why y_max +1? (no null termination?)
	if (grid->tilemap == NULL)
		return (RETURN_ERROR);
	y = 0;
	while (y < grid->y_max)
	{
		grid->tilemap[y] = (int *)ft_calloc(grid->x_max, sizeof(int));
		if (grid->tilemap[y] == NULL)
			return (RETURN_ERROR);
		if (map_fill_row(grid, y, content[y]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++y;
	}
	return (RETURN_SUCCESS);
}
