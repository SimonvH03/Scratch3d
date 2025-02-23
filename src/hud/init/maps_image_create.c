/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps_image_create.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/23 00:06:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short
	new_images_minimap(
		mlx_t *mlx,
		mlx_texture_t *player,
		t_minimap *minimap)
{
	minimap->walls = mlx_new_image(mlx, minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (RETURN_FAILURE);
	minimap->player = mlx_texture_to_image(mlx, player);
	if (minimap->player == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, minimap->walls,
			mlx->width - minimap->side * 1.2,
			mlx->height - minimap->side * 1.2) < 0)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, minimap->player,
			minimap->walls->instances[0].x + minimap->radius
			- minimap->player->width / 2,
			minimap->walls->instances[0].y + minimap->radius
			- minimap->player->height / 2) < 0)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static short
	new_images_bigmap(
		mlx_t *mlx,
		t_bigmap *map)
{
	map->walls = mlx_new_image(mlx, mlx->width, mlx->height);
	if (map->walls == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, map->walls, 0, 0) < 0)
		return (RETURN_FAILURE);
	map->player = mlx_new_image(mlx,
			(uint32_t)map->block_size, (uint32_t)map->block_size);
	if (map->player == NULL)
		return (RETURN_FAILURE);
	map->x_offset = mlx->width - map->r_scene->x_max * map->block_size;
	map->y_offset = mlx->height - map->r_scene->y_max * map->block_size;
	map->x_offset -= map->player->width;
	map->y_offset -= map->player->height;
	map->x_offset /= 2;
	map->y_offset /= 2;
	if (mlx_image_to_window(mlx, map->player,
			map->x_offset + map->r_scene->camera.pos_x * map->block_size,
			map->y_offset + map->r_scene->camera.pos_y * map->block_size) < 0)
		return (RETURN_FAILURE);
	map->player->enabled = false;
	map->walls->enabled = false;
	return (RETURN_SUCCESS);
}

short
	init_hud_images(
		mlx_t *mlx,
		t_hud *hud)
{
	hud->player_icon = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (hud->player_icon == NULL)
		return (RETURN_FAILURE);
	if (new_images_minimap(mlx, hud->player_icon,
			&hud->minimap) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_bigmap(mlx, &hud->bigmap) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	draw_minimap_circle_overlay(&hud->minimap);
	draw_map_walls(&hud->bigmap);
	hud->fps = mlx_put_string(mlx, "0000", WIDTH / 2 - 50, 100);
	return (RETURN_SUCCESS);
}
