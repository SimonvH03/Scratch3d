/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/17 00:11:09 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	tilemap_size(
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

static void
	set_tilemap_cell(
		t_grid *grid,
		int16_t *dest,
		int	token)
{
	if (!ft_isalnum(token))
		error_exit(0, EINVAL,
			"invalid map: only letters, digits and spaces allowed\n");
	if (token == ' ')
		*dest = -1;
	else if (ft_isdigit(token))
	{
		if (token == '0')
			*dest = set_cell(false, 0, token);
		else
			*dest = set_cell(true, (token - '0'), token);
	}
	else
	{
		if (is_door(token))
			*dest = set_cell(true, grid->doors.count++, token);
		else
			*dest = set_cell(true, 0, token);
	}
}

static int
	tilemap_fill_row(
		t_grid *grid,
		const int y,
		const char *line)
{
	unsigned int	x;

	x = 0;
	while (line[x])
	{
		set_tilemap_cell(grid, &grid->tilemap[y][x], line[x]);
		++x;
	}
	while (x < grid->x_max)
	{
		set_tilemap_cell(grid, &grid->tilemap[y][x], -1);
		++x;
	}
	return (RETURN_SUCCESS);
}

int
	read_tilemap(
		t_grid *grid,
		char *const *content)
{
	unsigned int	y;

	tilemap_size(grid, content);
	grid->tilemap = (int16_t **)ft_calloc(grid->y_max + 1, sizeof(int16_t *));// why y_max +1? (no null termination?)
	if (grid->tilemap == NULL)
		return (RETURN_ERROR);
	y = 0;
	while (y < grid->y_max)
	{
		grid->tilemap[y] = (int16_t *)ft_calloc(grid->x_max, sizeof(int16_t));
		if (grid->tilemap[y] == NULL)
			return (RETURN_ERROR);
		if (tilemap_fill_row(grid, y, content[y]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++y;
	}
	return (RETURN_SUCCESS);
}
