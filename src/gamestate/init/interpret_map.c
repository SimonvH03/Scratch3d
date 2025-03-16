/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpret_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:53:18 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	count_and_flag_doors(
		t_grid *grid)
{
	unsigned int	y;
	unsigned int	x;
	int				*cell;

	y = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			cell = &grid->tilemap[y][x];
			if (*cell == 'd' || *cell == 'D')
				*cell = (grid->doors.count++ << ID_SHIFT) | *cell;
			x++;
		}
		y++;
	}
}

static void
	init_door(
		t_door *dest,
		unsigned int pos_y,
		unsigned int pos_x)
{
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
	int				cell;

	y = 0;
	door = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			cell = (grid->tilemap[y][x] & TYPE_MASK);
			if (cell == 'd' || cell == 'D')
			{
				printf("D%d (%d, %d)\n", door, y, x);
				init_door(&list[door++], y, x);
			}
			x++;
		}
		y++;
	}
}

int
	interpret_map(
		t_grid *grid)
{
	count_and_flag_doors(grid);
	if (!grid->doors.count)
		return (RETURN_SUCCESS);
	grid->doors.list = (t_door *)malloc(grid->doors.count * sizeof(t_door));
	if (grid->doors.list == NULL)
		return (RETURN_ERROR);
	fill_door_list(grid, grid->doors.list);
	return (RETURN_SUCCESS);
}
