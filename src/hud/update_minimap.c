/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_minimap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:15 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 04:32:30 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	overlay_border(
		t_minimap *minimap)
{
	uint32_t	pixel_count;
	uint8_t		*src;
	uint8_t		*dst;
	uint32_t	limit;

	pixel_count = 0;
	src = minimap->circle_overlay;
	dst = minimap->walls->pixels;
	limit = minimap->side * minimap->side;
	while (pixel_count < limit)
	{
		if (src[3] % C_TRANSLUCENT == 0)
			dst[3] = src[3];
		++pixel_count;
		src += sizeof(uint32_t);
		dst += sizeof(uint32_t);
	}
}

static int
	project_wall_pixel(
		mlx_image_t *walls,
		void *param,
		uint32_t img_x,
		uint32_t img_y)
{
	const t_minimap		*minimap = param;
	const t_camera		*camera = minimap->r_camera;
	const t_grid		*grid = minimap->r_grid;
	float				prev_x;
	float				x;
	float				y;

	x -= minimap->radius;
	y -= minimap->radius;
	prev_x = x;
	x = prev_x * camera->plane_x + y * -camera->plane_y;
	y = prev_x * camera->plane_y + y * camera->plane_x;
	x /= minimap->block_size;
	y /= minimap->block_size;
	x += camera->pos_x;
	y += camera->pos_y;
	if (x < 0 || x >= grid->x_max || y < 0 || y >= grid->y_max)
		mlx_put_pixel(walls, img_x, img_y, C_CEILING);
	if (grid->walls[(int)y][(int)x] < 0)
		mlx_put_pixel(walls, img_x, img_y, C_CEILING);
	if (grid->walls[(int)y][(int)x] > 0)
		mlx_put_pixel(walls, img_x, img_y, C_WALL);
	mlx_put_pixel(walls, img_x, img_y, C_FLOOR);
	return (RETURN_SUCCESS);
}

void
	draw_minimap_walls(
		t_minimap	*minimap)
{
	reset_image(minimap->walls);
	image_iteration(minimap->walls, project_wall_pixel, minimap);
	overlay_border(minimap);
}
