/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:30 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 01:32:51 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short
	init_minimap_struct(
		t_minimap *minimap,
		mlx_t *mlx,
		t_camera *camera)
{
	minimap->side = ft_min_float(mlx->height, mlx->width) / 3;
	minimap->radius = minimap->side / 2;
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (RETURN_FAILURE);
	minimap->block_size = (minimap->side / 6)
		* camera->aspect_ratio;
	minimap->enabled = true;
	return (RETURN_SUCCESS);
}

static int
	init_bigmap_struct(
		t_bigmap *bigmap,
		mlx_t *mlx,
		t_grid *grid)
{
	bigmap->enabled = false;
	bigmap->block_size = ft_min_float(
			mlx->height / (grid->y_max + 2),
			mlx->width / (grid->x_max + 2));
	bigmap->x_offset = (mlx->width - (grid->x_max * bigmap->block_size)) / 2;
	bigmap->y_offset = (mlx->height - (grid->y_max * bigmap->block_size)) / 2;
}

int
	init_hud(
		mlx_t *mlx,
		t_hud *hud,
		t_scene *scene)
{
	init_bigmap_struct(&hud->bigmap, mlx, &scene->grid);
	if (init_minimap_struct(&hud->minimap, mlx, &scene->player.camera)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_bigmap(mlx, &hud->bigmap, &scene->player.camera)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	hud->player_icon = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (hud->player_icon == NULL)
		return (RETURN_FAILURE);
	if (new_images_minimap(mlx,	&hud->minimap, hud->player_icon)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	draw_minimap_circle_overlay(&hud->minimap);
	draw_bigmap_walls(&hud->bigmap, &scene->grid);
	hud->fps = mlx_put_string(mlx, "0000", WIDTH / 2 - 50, 100);
	return (RETURN_SUCCESS);
}
