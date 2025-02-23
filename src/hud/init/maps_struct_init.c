/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maps_struct_init.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/22 23:23:44 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short
	minimap_init(
		t_minimap *minimap,
		mlx_t *mlx)
{
	minimap->side = ft_min_float(mlx->height, mlx->width) / 3;
	minimap->radius = minimap->side / 2;
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (RETURN_FAILURE);
	minimap->block_size = (minimap->side / 6)
		* minimap->r_scene->camera.aspect_ratio;
	minimap->enabled = true;
	return (RETURN_SUCCESS);
}

static short
	map_init(
		t_bigmap *map,
		mlx_t *mlx)
{
	map->enabled = false;
	map->block_size = ft_min_float(
			mlx->height / (map->r_scene->y_max + 2),
			mlx->width / (map->r_scene->x_max + 2));
	return (RETURN_SUCCESS);
}
