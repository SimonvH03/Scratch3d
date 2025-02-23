/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_window.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/22 23:23:44 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(
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
	window->view = MENU;
	return (RETURN_SUCCESS);
}
