/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps_image_draw.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/23 19:53:26 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// for illustrative purposes, set outer circle pixel colour to C_TRANSLUCENT
void
	draw_minimap_circle_overlay(
		t_minimap *minimap)
{
	uint32_t	y;
	uint32_t	x;

	x = 0;
	while (x < minimap->side)
	{
		y = 0;
		while (y < minimap->side)
		{
			if (!ft_is_in_circle(x - (float)minimap->radius,
					y - (float)minimap->radius,
					minimap->radius))
				mlx_put_pixel(minimap->walls, x, y, C_TRANSPARENT);
			else if (!ft_is_in_circle(x - (float)minimap->radius,
					y - (float)minimap->radius,
					minimap->radius * 39 / 42))
				mlx_put_pixel(minimap->walls, x, y, C_TRANSLUCENT);
			else
				mlx_put_pixel(minimap->walls, x, y, C_WALL);
			++y;
		}
		++x;
	}
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
}

static uint32_t
	get_bigmap_pixel_colour(
		t_bigmap *map,
		float x,
		float y)
{
	t_scene		*scene;

	scene = map->r_scene;
	x -= map->walls->width / (float)2;
	y -= map->walls->height / (float)2;
	x /= map->block_size;
	y /= map->block_size;
	x += scene->x_max / (float)2;
	y += scene->y_max / (float)2;
	if (x < 0 || x >= scene->x_max
		|| y < 0 || y >= scene->y_max)
		return (C_TRANSLUCENT);
	if (scene->map[(int)y][(int)x] < 0)
		return (C_TRANSLUCENT);
	if (scene->map[(int)y][(int)x] > 0)
		return (C_WALL);
	return (C_FLOOR);
}

void
	draw_map_walls(
		t_bigmap *map)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < map->walls->height)
	{
		x = 0;
		while (x < map->walls->width)
		{
			colour = get_bigmap_pixel_colour(map, x, y);
			mlx_put_pixel(map->walls, x, y, colour);
			++x;
		}
		++y;
	}
}
