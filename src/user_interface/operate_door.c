/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operate_door.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/17 22:44:57 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_door_opening(
		t_door *door,
		float shift)
{
	door->position -= shift;
	if (door->position <= 0.0f)
	{
		door->position = 0.0f;
		door->state = ds_open;
		*door->cell &= ~SOLID_MASK;
	}
}

static void
	update_door_closing(
		t_door *door,
		float shift)
{
	door->position += shift;
	if (door->position >= 1.0f)
	{
		door->position = 1.0f;
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

void
	operate_door(
		t_doors *doors,
		t_camera *camera,
		unsigned int index)
{
	t_door		*door;

	door = &doors->list[index];
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
		*door->cell |= SOLID_MASK;
	}
}
