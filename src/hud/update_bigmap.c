/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_bigmap.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/02/25 22:52:24 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	project_player_icon_pixel(
		mlx_image_t *player_icon,
		void *param,
		uint32_t img_x,
		uint32_t img_y)
{
	const t_camera		*camera = ((t_bigmap *)param)->r_camera;
	const mlx_texture_t	*texture = ((t_bigmap *)param)->r_player_tex;
	float				prev_x;
	float				x;
	float				y;

	x = img_x;
	y = img_y;
	x -= texture->width / 2.0f;
	y -= texture->height / 2.0f;
	prev_x = x;
	x = prev_x * camera->plane_x + y * camera->plane_y;
	y = prev_x * -camera->plane_y + y * camera->plane_x;
	x *= 1.414213562f;
	y *= 1.414213562f;
	x += texture->width;
	y += texture->height;
	x /= 2;
	y /= 2;
	if ((x < 0 || x >= texture->width || y < 0 || y >= texture->height))
		return (RETURN_SUCCESS);
	((uint32_t *)player_icon->pixels)[img_y * player_icon->width + img_x]
		= ((uint32_t *)texture->pixels)[(int)y * texture->width + (int)x];
	return (RETURN_SUCCESS);
}

void
	draw_bigmap_player(
		t_bigmap *bigmap)
{
	reset_image(bigmap->player_icon);
	image_iteration(bigmap->player_icon, project_player_icon_pixel, bigmap);
	bigmap->player_icon->instances[0].x = bigmap->x_offset
		+ bigmap->r_camera->pos_x * bigmap->block_size;
	bigmap->player_icon->instances[0].y = bigmap->y_offset
		+ bigmap->r_camera->pos_y * bigmap->block_size;
}
