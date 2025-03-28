/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_controls.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 23:30:28 by simon         #+#    #+#                 */
/*   Updated: 2025/03/28 01:38:17 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	mouse_buttons(
		mouse_key_t button,
		action_t action,
		modifier_key_t mods,
		void* param)
{
	t_window *window;

	window = (t_window *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT
		&& (action == MLX_PRESS || action == MLX_RELEASE))
	{
		start_fire_animation(&window->scene.player.weapon);
	}
}

void
	mouse_pan(
		mlx_t *mlx,
		t_camera *camera)
{
	float		camera_x;
	uint32_t	x_pos;
	uint32_t	y_pos;

	mlx_get_mouse_pos(mlx, &x_pos, &y_pos);
	if (x_pos != mlx->width / 2)
	{
		camera_x = ((x_pos / (float)mlx->width) - 0.5f) * camera->cursor_rot_speed;
		camera->dir_x += camera->plane_x * camera_x;
		camera->dir_y += camera->plane_y * camera_x;
		normalize_vector2(&camera->dir_x, &camera->dir_y);
		camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
		camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
	}
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
}
