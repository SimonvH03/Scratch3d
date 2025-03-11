/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frametime_variables.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/10 18:45:44 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	t_camera	*camera;

	window = param;
	camera = &window->scene.player.camera;
	camera->movement_speed = MOVEMENT_SPEED * window->mlx->delta_time;
	if (camera->movement_speed > 0.49)
		camera->movement_speed = 0.49;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * window->mlx->delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * window->mlx->delta_time);
}
