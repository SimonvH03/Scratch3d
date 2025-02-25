/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frametime_variables.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/25 02:27:10 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_fps_image(
		double delta_time,
		mlx_image_t *image)
{
	char	buffer[12];
	int		fps;

	ft_bzero(buffer, 12);
	fps = 1 / delta_time;
	if (fps > 999)
		fps = 999;
	ft_putnbr_ptr(buffer, fps);
	reset_image(image);
	modlx_put_string(image, buffer);
}

void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	t_camera	*camera;

	window = param;
	camera = &window->scene.player.camera;
	update_fps_image(window->mlx->delta_time, window->hud.fps);
	camera->movement_speed = MOVEMENT_SPEED * window->mlx->delta_time;
	if (camera->movement_speed > 0.49)
		camera->movement_speed = 0.49;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * window->mlx->delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * window->mlx->delta_time);
}
