/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/27 22:12:17 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_door(
		t_door *dest,
		t_grid *grid,
		unsigned int pos_y,
		unsigned int pos_x)
{
	dest->r_cell = &grid->tilemap[pos_y][pos_x];
	dest->position = 1.0f;
	dest->state = ds_closed;
	dest->pos_y = pos_y;
	dest->pos_x = pos_x;
}

static void
	fill_door_list(
		t_grid *grid,
		t_door *list)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	door;
	char			type;

	y = 0;
	door = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			type = get_type(grid->tilemap[y][x]);
			if (type == 'd' || type == 'D')
			{
				// printf("%coor at (%d, %d)\n", type, y, x);
				init_door(&list[door++], grid, y, x);
			}
			x++;
		}
		y++;
	}
}

int
	init_doors(
		t_grid *grid)
{
	if (!grid->door_count)
		return (RETURN_SUCCESS);
	grid->door_list = (t_door *)malloc(grid->door_count * sizeof(t_door));
	if (grid->door_list == NULL)
		return (RETURN_ERROR);
	fill_door_list(grid, grid->door_list);
	return (RETURN_SUCCESS);
}
