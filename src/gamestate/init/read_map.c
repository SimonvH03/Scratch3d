/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/15 23:09:27 by simon         ########   odam.nl         */
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
	map_fill_space(
		t_grid	*grid,
		const uint32_t y,
		const uint32_t x,
		const int token)
{
	if (ft_strchr(STANDARD_TOKENS, token) == NULL
		&& ft_isalnum(token) == false)
	{
		printf("invalid map: only letters, digits and spaces allowed\n");
		return (RETURN_FAILURE);
	}
	if (token == ' ')
		grid->walls[y][x] = -1;
	else if (ft_isdigit(token))
		grid->walls[y][x] = token - 48;
	else if (token == 'd' || token == 'D')
	{
		grid->walls[y][x] = token;
		grid->doors[y][x] = 1.0f;
	}
	else if (ft_isalpha(token))
		grid->sprites[y][x] = token;
	return (RETURN_SUCCESS);
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
		if (map_fill_space(grid, y, x, (int)line[x]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++x;
	}
	while (x < grid->x_max)
	{
		grid->walls[y][x] = -1;
		grid->sprites[y][x] = -1;
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
	grid->walls = (int **)ft_calloc(grid->y_max + 1, sizeof(int *));// why y_max +1? (no null termination?)
	if (grid->walls == NULL)
		return (RETURN_FAILURE);
	grid->sprites = (int **)ft_calloc(grid->y_max + 1, sizeof(int *));
	if (grid->sprites == NULL)
		return (RETURN_FAILURE);
	grid->doors = (float **)ft_calloc(grid->y_max + 1, sizeof(float *));
	if (grid->doors == NULL)
		return (RETURN_FAILURE);
	y = 0;
	while (y < grid->y_max)
	{
		grid->walls[y] = (int *)ft_calloc(grid->x_max, sizeof(int));
		if (grid->walls[y] == NULL)
			return (RETURN_FAILURE);
		grid->sprites[y] = (int *)ft_calloc(grid->x_max, sizeof(int));
		if (grid->sprites[y] == NULL)
			return (RETURN_FAILURE);
		grid->doors[y] = (float *)ft_calloc(grid->x_max, sizeof(float));
		if (grid->doors[y] == NULL)
			return (RETURN_FAILURE);
		if (map_fill_row(grid, y, content[y]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		++y;
	}
	return (RETURN_SUCCESS);
}
