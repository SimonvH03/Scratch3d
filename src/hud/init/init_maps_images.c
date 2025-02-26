/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_maps_images.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/26 18:59:55 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	sample_bigmap(
		mlx_image_t *dest,
		void *param,
		uint32_t img_x,
		uint32_t img_y)
{
	const t_bigmap	*bigmap = (t_bigmap *)param;
	const t_grid	*grid = bigmap->r_grid;
	float			x;
	float			y;

	x = img_x;
	y = img_y;
	x -= dest->width / (float)2;
	y -= dest->height / (float)2;
	x /= bigmap->block_size;
	y /= bigmap->block_size;
	x += grid->x_max / (float)2;
	y += grid->y_max / (float)2;
	if (x < 0 || x >= grid->x_max || y < 0 || y >= grid->y_max)
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_TRANSLUCENT;
	else if (grid->walls[(int)y][(int)x] < 0)
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_TRANSLUCENT;
	else if (grid->walls[(int)y][(int)x] > 0)
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_WALL;
	else
		((uint32_t *)dest->pixels)[img_y * dest->width + img_x] = C_FLOOR;
	return (RETURN_SUCCESS);
}

// for illustrative purposes, set outer circle pixel colour to C_TRANSLUCENT
static int
	sample_overlay(
		mlx_image_t *dest,
		void *param,
		uint32_t x,
		uint32_t y)
{
	const uint32_t	radius = *(uint32_t *)param;
	const int		xcoord = (int)(x - radius);
	const int		ycoord = (int)(y - radius);

	if (!ft_is_in_circle(xcoord, ycoord, radius))
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_TRANSPARENT;
	else if (!ft_is_in_circle(xcoord, ycoord, radius * 39 / 42))
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_TRANSLUCENT;
	else
		((uint32_t *)dest->pixels)[y * dest->width + x] = C_WALL;
	return (RETURN_SUCCESS);
}

int
	new_images_minimap(
		mlx_t *mlx,
		t_minimap *minimap,
		mlx_texture_t *player)
{
	minimap->walls = mlx_new_image(mlx, minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (RETURN_FAILURE);
	minimap->player_icon = mlx_texture_to_image(mlx, player);
	if (minimap->player_icon == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, minimap->walls,
			mlx->width - (minimap->side * 1.2),
			mlx->height - (minimap->side * 1.2)) < 0)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, minimap->player_icon,
			minimap->walls->instances[0].x
			+ minimap->radius - (minimap->player_icon->width / 2),
			minimap->walls->instances[0].y
			+ minimap->radius - (minimap->player_icon->height / 2)) < 0)
		return (RETURN_FAILURE);
	image_iteration(minimap->walls, sample_overlay, &minimap->radius);
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
	return (RETURN_SUCCESS);
}

int
	new_images_bigmap(
		mlx_t *mlx,
		t_bigmap *bigmap,
		t_scene *scene)
{
	const t_camera	*camera = &scene->player.camera;

	bigmap->walls = mlx_new_image(mlx, mlx->width, mlx->height);
	if (bigmap->walls == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, bigmap->walls, 0, 0) < 0)
		return (RETURN_FAILURE);
	bigmap->player_icon = mlx_new_image(mlx,
			(uint32_t)bigmap->block_size, (uint32_t)bigmap->block_size);
	if (bigmap->player_icon == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, bigmap->player_icon,
			bigmap->x_offset + camera->pos_x * bigmap->block_size,
			bigmap->y_offset + camera->pos_y * bigmap->block_size) < 0)
		return (RETURN_FAILURE);
	bigmap->player_icon->enabled = false;
	bigmap->walls->enabled = false;
	image_iteration(bigmap->walls, sample_bigmap, bigmap);
	return (RETURN_SUCCESS);
}
