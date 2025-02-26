/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_minimap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:15 by simon         #+#    #+#                 */
/*   Updated: 2025/02/26 19:19:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t		pixel_count;
	const uint32_t	limit = minimap->side * minimap->side;
	uint8_t			*src;
	uint8_t			*dst;

	src = minimap->circle_overlay;
	dst = minimap->walls->pixels;
	pixel_count = 0;
	while (pixel_count < limit)
	{
		if (src[3] % 0x42 == 0)
			dst[3] = src[3];
		++pixel_count;
		src += sizeof(uint32_t);
		dst += sizeof(uint32_t);
	}
}

static int
	sample_wall(
		mlx_image_t *walls,
		void *param,
		uint32_t img_x,
		uint32_t img_y)
{
	const t_minimap		*minimap = param;
	const t_camera		*camera = minimap->r_camera;
	float				prev_x;
	float				x;
	float				y;

	x = img_x;
	x -= minimap->radius;
	y = img_y;
	y -= minimap->radius;
	prev_x = x;
	x = prev_x * camera->plane_x + y * -camera->plane_y;
	y = prev_x * camera->plane_y + y * camera->plane_x;
	x = x / minimap->block_size + camera->pos_x;
	y = y / minimap->block_size + camera->pos_y;
	if (x < 0 || x >= minimap->r_grid->x_max
		|| y < 0 || y >= minimap->r_grid->y_max)
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x] = C_CEILING;
	else if (minimap->r_grid->walls[(int)y][(int)x] < 0)
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x] = C_CEILING;
	else if (minimap->r_grid->walls[(int)y][(int)x] > 0)
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x] = C_WALL;
	else
		((uint32_t *)walls->pixels)[img_y * walls->width + img_x] = C_FLOOR;
	return (RETURN_SUCCESS);
}

void
	update_minimap(
		t_minimap	*minimap)
{
	image_iteration(minimap->walls, sample_wall, minimap);
	overlay_border(minimap);
}
