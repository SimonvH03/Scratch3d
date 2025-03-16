/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_interaction.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:57:26 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_door_opening(
		t_door *door,
		float shift)
{
	door->position += shift;
	if (door->position >= 1.0f)
	{
		door->position = 1.0f;
		door->state = ds_open;
	}
}

static void
	update_door_closing(
		t_door *door,
		float shift)
{
	door->position -= shift;
	if (door->position <= 0.0f)
	{
		door->position = 0.0f;
		door->state = ds_closed;
	}
}

void
	update_doors(
		t_doors *doors)
{
	unsigned int	index;
	t_door			*door;

	index = 0;
	while (index < doors->count)
	{
		door = &doors->list[index];
		if (door->state == ds_opening)
			update_door_opening(door, doors->frame_shift);
		else if (door->state == ds_closing)
			update_door_closing(door, doors->frame_shift);
		index++;
	}
}

static void
	operate_door(
		t_doors *doors,
		t_camera *camera,
		unsigned int index)
{
	t_door		*door = &doors->list[index];

	if (door->state == ds_closed || door->state == ds_closing)
	{
		door->state = ds_opening;
	}
	else if (door->state == ds_open || door->state == ds_opening)
	{
		if (door->pos_y == (unsigned int)camera->pos_y
			&& door->pos_x == (unsigned int)camera->pos_x)
			return ;
		door->state = ds_closing;
	}
}

void
	door_interaction(
		t_grid *grid,
		t_camera *camera)
{
	int		interaction_cell;

	interaction_cell = grid->tilemap
	[(int)(float)(camera->pos_y + camera->dir_y)]
	[(int)(float)(camera->pos_x + camera->dir_x)];
	if (!((interaction_cell & TYPE_MASK) == 'd'
		|| (interaction_cell & TYPE_MASK) == 'D'))
		return ;
	operate_door(&grid->doors, camera,
		(interaction_cell & ID_MASK) >> ID_SHIFT);
}
