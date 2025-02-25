/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_texture_column.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/02/25 02:25:44 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_column(
		t_walls *walls,
		t_camera *camera,
		t_ray *ray,
		t_column *column)
{
	if (ray->hit_type == HORIZONTAL && ray->sign_x >= 0)
		column->texture = walls->east_texture;
	else if (ray->hit_type == HORIZONTAL && ray->sign_x < 0)
		column->texture = walls->west_texture;
	else if (ray->hit_type == VERTICAL && ray->sign_y >= 0)
		column->texture = walls->south_texture;
	else if (ray->hit_type == VERTICAL && ray->sign_y < 0)
		column->texture = walls->north_texture;
	if (ray->hit_type == HORIZONTAL)
		column->x = camera->pos_y + ray->distance * ray->dir_y;
	else
		column->x = camera->pos_x + ray->distance * ray->dir_x;
	column->x -= (int)column->x;
	column->height = walls->image->height / ray->distance;
	column->start = (int)(walls->image->height - column->height) / 2;
	if (column->start < 0)
		column->start = 0;
	column->end = (walls->image->height + column->height) / 2;
	if ((uint32_t)column->end >= walls->image->height)
		column->end = walls->image->height;
	column->step = column->texture->height / (float)column->height;
	column->y = (column->start - (int)walls->image->height / 2
			+ column->height / 2) * column->step;
}

// slightly optimized
void
	draw_texture_column(
		t_walls *walls,
		t_camera *camera,
		t_ray *ray,
		uint32_t screen_x)
{
	t_column		column;
	uint32_t		screen_y;
	uint8_t			*texumn_start;

	init_column(walls, camera, ray, &column);
	texumn_start = &column.texture->pixels[(int)(column.x
			* column.texture->width) * column.texture->height * BPP];
	screen_y = (uint32_t)column.start;
	while (screen_y < (uint32_t)column.end)
	{
		*((uint32_t *)&walls->image->pixels[(screen_y
			* walls->image->width + screen_x)* BPP])
			= *((uint32_t *)&texumn_start[(int)column.y * BPP]);
		column.y += column.step;
		++screen_y;
	}
}

// uses mlx_put_pixel
// void
// 	draw_texture_column(
// 		t_scene *scene,
// 		t_ray *ray,
// 		uint32_t screen_x)
// {
// 	t_column		column;
// 	uint32_t		screen_y;
// 	uint32_t		colour;
// 	uint8_t			*texumn_start;
// 	uint8_t			*texel;

// 	init_column(scene, ray, &column);
// 	texumn_start = &column.texture->pixels[(int)(column.x
// 			* column.texture->width) * column.texture->height * BPP];
// 	screen_y = (uint32_t)column.start;
// 	while (screen_y < (uint32_t)column.end)
// 	{
// 		texel = &texumn_start[(int)column.y * BPP];
// 		colour = texel[0] << 24 | texel[1] << 16 | texel[2] << 8 | texel[3];
// 		mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
// 		column.y += column.step;
// 		++screen_y;
// 	}
// }
