/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_bigmap.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/03/27 22:16:38 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	sample_player(
		mlx_image_t *player_icon,
		uint32_t img_x,
		uint32_t img_y,
		void *param)
{
	const t_camera		*camera = ((t_bigmap *)param)->r_camera;
	const mlx_image_t	*image = ((t_bigmap *)param)->player_icon_src.image;
	float				prev_x;
	float				x;
	float				y;

	x = img_x;
	y = img_y;
	x -= (float)(image->width / 2);
	y -= (float)(image->height / 2);
	prev_x = x;
	x = prev_x * camera->plane_x + y * camera->plane_y;
	y = prev_x * -camera->plane_y + y * camera->plane_x;
	x += (float)(image->width / 2);
	y += (float)(image->height / 2);
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		((uint32_t *)player_icon->pixels)[img_y * player_icon->width + img_x]
			= C_TRANSPARENT;
	else
		((uint32_t *)player_icon->pixels)[img_y * player_icon->width + img_x]
			= ((uint32_t *)image->pixels)[(int)y * image->width + (int)x];
	return (RETURN_SUCCESS);
}

void
	update_bigmap(
		t_bigmap *bigmap)
{
	image_iter(bigmap->player, sample_player, bigmap);
	bigmap->player->instances[0].x = bigmap->x_offset
		+ bigmap->r_camera->pos_x * bigmap->block_size;
	bigmap->player->instances[0].y = bigmap->y_offset
		+ bigmap->r_camera->pos_y * bigmap->block_size;
}
