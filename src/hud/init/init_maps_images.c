/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_maps_images.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 04:27:53 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	get_bigmap_pixel_colour(
		t_bigmap *bigmap,
		t_grid *grid,
		float x,
		float y)
{
	x -= bigmap->walls->width / (float)2;
	y -= bigmap->walls->height / (float)2;
	x /= bigmap->block_size;
	y /= bigmap->block_size;
	x += grid->x_max / (float)2;
	y += grid->y_max / (float)2;
	if (x < 0 || x >= grid->x_max
		|| y < 0 || y >= grid->y_max)
		return (C_TRANSLUCENT);
	if (grid->walls[(int)y][(int)x] < 0)
		return (C_TRANSLUCENT);
	if (grid->walls[(int)y][(int)x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_bigmap_walls(
		t_bigmap *bigmap,
		t_grid *grid)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < bigmap->walls->height)
	{
		x = 0;
		while (x < bigmap->walls->width)
		{
			colour = get_bigmap_pixel_colour(bigmap, grid, x, y);
			mlx_put_pixel(bigmap->walls, x, y, colour);
			++x;
		}
		++y;
	}
}

// for illustrative purposes, set outer circle pixel colour to C_TRANSLUCENT
static int
	project_overlay_pixel(
		mlx_image_t *walls,
		void *param,
		uint32_t x,
		uint32_t y)
{
	const	uint32_t radius = *(uint32_t *)param;

	if (!ft_is_in_circle(x - radius, y - radius, radius))
		mlx_put_pixel(walls, x, y, C_TRANSPARENT);
	else if (!ft_is_in_circle(x - radius, y - radius, radius * 39 / 42))
		mlx_put_pixel(walls, x, y, C_TRANSLUCENT);
	else
		mlx_put_pixel(walls, x, y, C_WALL);
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
	image_iteration(minimap->walls, project_overlay_pixel, &minimap->radius);
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
	bigmap->x_offset -= bigmap->player_icon->width / 2;
	bigmap->y_offset -= bigmap->player_icon->height / 2;
	if (mlx_image_to_window(mlx, bigmap->player_icon,
			bigmap->x_offset + camera->pos_x * bigmap->block_size,
			bigmap->y_offset + camera->pos_y * bigmap->block_size) < 0)
		return (RETURN_FAILURE);
	bigmap->player_icon->enabled = false;
	bigmap->walls->enabled = false;
	draw_bigmap_walls(bigmap, &scene->grid);
	return (RETURN_SUCCESS);
}
