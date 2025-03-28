/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/28 01:29:04 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(
		t_window *window)
{
	uint32_t	width;
	uint32_t	height;
	mlx_t		*mlx;

	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_MAXIMIZED, FULLSCREEN);
	mlx_set_setting(MLX_DECORATED, !FULLSCREEN);
	mlx_set_setting(MLX_HEADLESS, false);
	mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (mlx == NULL)
		return (RETURN_FAILURE);
	if (FULLSCREEN == true)
	{
		mlx_get_monitor_size(MONITOR_ID, &width, &height);
		mlx_set_window_size(mlx, width, height);
	}
	mlx_set_cursor_mode(mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(mlx, mlx->width / 2, mlx->height / 2);
	window->mlx = mlx;
	window->view = wv_menu;
	return (RETURN_SUCCESS);
}
