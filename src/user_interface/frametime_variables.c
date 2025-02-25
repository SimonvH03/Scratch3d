/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frametime_variables.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/26 00:02:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_fps_image(
		double delta_time,
		t_fps *fps)
{
	char		buffer[12];
	uint32_t	output_fps;

	ft_bzero(buffer, 12);
	fps->cum_time += delta_time;
	++fps->no_frames;
	if (fps->cum_time < 0.01)
		return ;
	output_fps = fps->no_frames / fps->cum_time;
	fps->cum_time = 0;
	fps->no_frames = 0;
	if (output_fps > 99999)
		output_fps = 99999;
	ft_putnbr_ptr(buffer, output_fps);
	reset_image(fps->image);
	modlx_put_string(fps->image, buffer);
}

void
	frametime_dependant_variables(
		void *param)
{
	t_window	*window;
	t_camera	*camera;

	window = param;
	camera = &window->scene.player.camera;
	update_fps_image(window->mlx->loop_time, &window->hud.fps);
	camera->movement_speed = MOVEMENT_SPEED * window->mlx->delta_time;
	if (camera->movement_speed > 0.49)
		camera->movement_speed = 0.49;
	camera->rotation_cosin[0] = cosf(ROTATION_SPEED * window->mlx->delta_time);
	camera->rotation_cosin[1] = sinf(ROTATION_SPEED * window->mlx->delta_time);
}
