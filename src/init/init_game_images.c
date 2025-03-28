/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game_images.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/03/28 00:49:10 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	draw_scene_background(
		mlx_image_t *background,
		uint32_t x,
		uint32_t y,
		void *param)
{
	const t_scene	*scene = param;

	if (y <= background->height / 2)
		mlx_put_pixel(background, x, y, scene->ceiling_clr);
	else
		mlx_put_pixel(background, x, y, scene->floor_clr);
	return (RETURN_SUCCESS);
}

int
	init_game_images(
		mlx_t *mlx,
		t_scene	*scene)
{
	scene->background = mlx_new_image(mlx, mlx->width, mlx->height);
	if (scene->background == NULL)
		return (RETURN_FAILURE);
	scene->walls.image = mlx_new_image(mlx, mlx->width, mlx->height);
	if (scene->walls.image == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, scene->background, 0, 0) < 0)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, scene->walls.image, 0, 0) < 0)
		return (RETURN_FAILURE);
	image_iter(scene->background, draw_scene_background, scene);
	return (RETURN_SUCCESS);
}
