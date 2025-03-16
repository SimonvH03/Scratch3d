/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frametime_variables.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:10:55 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	double		delta_time;
	t_camera	*camera;
	t_doors		*doors;

	window = (t_window *)param;
	delta_time = window->mlx->delta_time;
	camera = &window->scene.player.camera;
	doors = &window->scene.grid.doors;
	camera->movement_speed = MOVEMENT_SPEED * delta_time;
	if (camera->movement_speed > 0.49)
		camera->movement_speed = 0.49;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * delta_time);
	doors->frame_shift = DOOR_SHIFT_SPEED * delta_time;
}
