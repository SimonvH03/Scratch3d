/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:30 by simon         #+#    #+#                 */
/*   Updated: 2025/03/26 22:18:07 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	init_minimap_struct(
		t_hud *hud,
		t_minimap *minimap,
		mlx_t *mlx,
		t_scene *scene)
{
	minimap->enabled = true;
	minimap->player_icon.texture = hud->player_icon;
	minimap->r_camera = &scene->player.camera;
	minimap->r_grid = &scene->grid;
	minimap->side = ft_min_float(mlx->height, mlx->width) / 3;
	minimap->block_size = (minimap->side / 6)
		* scene->player.camera.aspect_ratio;
	minimap->radius = minimap->side / 2;
	minimap->circle_overlay = malloc(sizeof(uint32_t)
			* (pow(minimap->side, 2) + 1) + 1);
	if (minimap->circle_overlay == NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static int
	init_bigmap_struct(
		t_hud *hud,
		t_bigmap *bigmap,
		mlx_t *mlx,
		t_scene *scene)
{
	bigmap->enabled = false;
	bigmap->player_icon_src.texture = hud->player_icon;
	bigmap->r_camera = &scene->player.camera;
	bigmap->r_grid = &scene->grid;
	bigmap->block_size = ft_min_float(
			mlx->height / (scene->grid.y_max + 2),
			mlx->width / (scene->grid.x_max + 2));
	bigmap->x_offset = mlx->width - scene->grid.x_max * bigmap->block_size;
	bigmap->y_offset = mlx->height - scene->grid.y_max * bigmap->block_size;
	bigmap->x_offset /= 2;
	bigmap->y_offset /= 2;
	return (RETURN_SUCCESS);
}

int
	init_hud(
		mlx_t *mlx,
		t_hud *hud,
		t_scene *scene)
{
	hud->player_icon = &mlx_load_xpm42(PLAYER_ICON_PATH)->texture;
	if (hud->player_icon == NULL)
		return (RETURN_FAILURE);
	add_to_clear_list(hud->player_icon);
	if (init_bigmap_struct(hud, &hud->bigmap, mlx, scene)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_minimap_struct(hud, &hud->minimap, mlx, scene)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_bigmap(mlx, &hud->bigmap, scene)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (new_images_minimap(mlx,	&hud->minimap)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	ft_bzero(&hud->fps, sizeof(t_fps));
	hud->fps.image = mlx_put_string(mlx, "00000",
		(mlx->width / 2) - (MLX_FONT_WIDTH * 1.5),
		mlx->height / 42);
	return (RETURN_SUCCESS);
}
