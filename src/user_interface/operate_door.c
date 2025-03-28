/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operate_door.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/28 01:35:10 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	operate_door(
		t_door *door,
		t_camera *camera)
{
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
		*door->r_cell |= SOLID_MASK;
	}
}
