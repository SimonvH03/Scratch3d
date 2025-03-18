/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_texture_column.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/03/18 00:13:25 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	select_texture(
		t_column *column,
		t_walls *walls,
		t_ray *ray)
{
	if (ray->hits_door)
		column->texture = walls->door_texture;
	else if (ray->hit_type == ha_horizontal && ray->sign_x >= 0)
		column->texture = walls->east_texture;
	else if (ray->hit_type == ha_horizontal && ray->sign_x < 0)
		column->texture = walls->west_texture;
	else if (ray->hit_type == ha_vertical && ray->sign_y >= 0)
		column->texture = walls->south_texture;
	else if (ray->hit_type == ha_vertical && ray->sign_y < 0)
		column->texture = walls->north_texture;
}

static void
	vertical_boundaries(
		t_column *column,
		t_walls *walls,
		t_ray *ray)
{
	column->height = walls->image->height / ray->distance / 2;
	column->start = (int)(walls->image->height / 2 - column->height);
	if (column->start < 0)
		column->start = 0;
	column->end = (walls->image->height / 2 + column->height);
	if ((uint32_t)column->end >= walls->image->height)
		column->end = walls->image->height;
	column->step = column->texture->height / (float)(column->height * 2);
	column->y = (column->start - (int)walls->image->height / 2
			+ column->height) * column->step;
}

// optimized by removing mlx_put_pixel, and storing wall textures column-major
// 0.0005f offset only functions to remove pixel 'jitter' from the center row
//  where otherwise exactly halfway on all textures the y would be consistently
//	miscalculated half of the time because of floating point inaccuracy
// setting higher causes jitter elsewhere, lower doesn't resolve jitter
void
	draw_texture_column(
		t_ray *ray,
		t_walls *walls,
		uint32_t screen_x)
{
	t_column		column;
	uint32_t		screen_y;
	uint32_t		*texumn_start;

	select_texture(&column, walls, ray);
	vertical_boundaries(&column, walls, ray);
	if (ray->partial >= 1 || ray->partial < 0)
		return ;
	texumn_start = &((uint32_t *)column.texture->pixels)[column.texture->height
			* (int)(ray->partial * column.texture->width)];
	screen_y = (uint32_t)column.start;
	while (screen_y < (uint32_t)column.end)
	{
		((uint32_t *)walls->image->pixels)[screen_x
			+ screen_y * walls->image->width]
			= texumn_start[(int)(column.y + 0.0005f)];
		column.y += column.step;
		screen_y++;
	}
}
