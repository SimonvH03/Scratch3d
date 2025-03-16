/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 02:31:24 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(
		t_window *window)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_set_setting(MLX_DECORATED, true);
	mlx_set_setting(MLX_HEADLESS, false);
	window->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (window->mlx == NULL)
		return (RETURN_FAILURE);
	window->view = wv_menu;
	return (RETURN_SUCCESS);
}
