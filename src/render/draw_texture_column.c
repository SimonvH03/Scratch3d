/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_column.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:36:33 by simon             #+#    #+#             */
/*   Updated: 2024/09/23 01:35:19 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// ...else if ((CASE) || 1)... against braindead -Werror=maybe-uninitialized
static void
	init_column(
		t_scene *scene,
		t_ray *ray,
		t_column *column)
{
	if (ray->hit_type == HORIZONTAL && ray->sign_x > 0)
		column->texture = scene->east_texture;
	else if (ray->hit_type == HORIZONTAL && ray->sign_x < 0)
		column->texture = scene->west_texture;
	else if (ray->hit_type == VERTICAL && ray->sign_y > 0)
		column->texture = scene->south_texture;
	else if ((ray->hit_type == VERTICAL && ray->sign_y < 0) || 1)
		column->texture = scene->north_texture;
	if (ray->hit_type == HORIZONTAL)
		column->x = scene->camera.pos_y + ray->distance * ray->dir_y;
	else
		column->x = scene->camera.pos_x + ray->distance * ray->dir_x;
	column->x -= (int)column->x;
	column->height = scene->walls->height / ray->distance;
	column->start = (int)(scene->walls->height - column->height) / 2;
	if (column->start < 0)
		column->start = 0;
	column->end = (scene->walls->height + column->height) / 2;
	if ((uint32_t)column->end >= scene->walls->height)
		column->end = scene->walls->height;
	column->step = column->texture->height / (float)column->height;
	column->y = (column->start - (int)scene->walls->height / 2
			+ column->height / 2) * column->step;

}

void
	draw_texture_column(
		t_scene *scene,
		t_ray *ray,
		uint32_t screen_x)
{
	t_column		column;
	uint32_t		screen_y;
	uint32_t		index;
	uint32_t		colour;
	uint8_t			*texumn_start;
	uint8_t			*texel;

	init_column(scene, ray, &column);

	texumn_start = &column.texture->pixels[
		(int)(column.x * column.texture->width) * column.texture->height * 4];
	screen_y = (uint32_t)column.start;
	while (screen_y < (uint32_t)column.end)
	{
		column.y += column.step;
		texel = &texumn_start[(int)(column.y) * 4];
		colour = texel[0] << 24 | texel[1] << 16 | texel[2] << 8 | texel[3];
		mlx_put_pixel(scene->walls, screen_x, screen_y, colour);
		++screen_y;
	}
}
