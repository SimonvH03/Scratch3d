/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_images_minimap.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/03/26 21:03:18 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int
	init_minimap_player_icon(
		mlx_t *mlx,
		t_scalable *player_icon,
		t_minimap *minimap)
{
	player_icon->scale = minimap->block_size / player_icon->texture->height / 2;
	player_icon->scale = nearest_power_of_2(player_icon->scale);
	if (new_scaled_image(mlx, player_icon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, player_icon->image,
			minimap->walls->instances[0].x + minimap->radius
			- (player_icon->image->width / 2),
			minimap->walls->instances[0].y + minimap->radius
			- (player_icon->image->height / 2)) < 0)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int
	new_images_minimap(
		mlx_t *mlx,
		t_minimap *minimap)
{
	minimap->walls = mlx_new_image(mlx, minimap->side, minimap->side);
	if (minimap->walls == NULL)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, minimap->walls,
			(minimap->side * 0.2), mlx->height - (minimap->side * 1.2)) < 0)
		return (RETURN_FAILURE);
	if (init_minimap_player_icon(mlx, &minimap->player_icon, minimap)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	image_iter(minimap->walls, sample_overlay, &minimap->radius);
	ft_memcpy(minimap->circle_overlay, minimap->walls->pixels,
		minimap->walls->width * minimap->walls->height * sizeof(uint32_t));
	return (RETURN_SUCCESS);
}
