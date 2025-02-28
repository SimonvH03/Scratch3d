/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_texture_column.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 01:36:33 by simon         #+#    #+#                 */
/*   Updated: 2025/02/28 01:07:45 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_texumn
{
	uint32_t	*pixels;
	uint32_t	height;
}	t_texumn;

typedef struct s_texel
{
	uint32_t	colour;
	uint32_t	len;
}	t_texel;

typedef struct s_colourmap
{
	t_texel		*buffer;
	uint32_t	index;
	uint32_t	size;
	int			start;
}	t_colour_map;

static void
	init_texumn(
		t_texumn *texumn,
		const t_ray *ray,
		const t_walls *walls,
		const t_camera *camera)
{
	mlx_texture_t	*texture;
	float			x;

	if (ray->hit_type == VERTICAL && ray->sign_y < 0)
		texture = walls->north_texture;
	else if (ray->hit_type == VERTICAL && ray->sign_y >= 0)
		texture = walls->south_texture;
	else if (ray->hit_type == HORIZONTAL && ray->sign_x >= 0)
		texture = walls->east_texture;
	else if (ray->hit_type == HORIZONTAL && ray->sign_x < 0)
		texture = walls->west_texture;
	if (ray->hit_type == HORIZONTAL)
		x = camera->pos_y + ray->distance * ray->dir_y;
	else
		x = camera->pos_x + ray->distance * ray->dir_x;
	x -= (int)x;
	texumn->pixels = &((uint32_t *)texture->pixels)
	[(int)(x * texture->width) * texture->height];
	texumn->height = texture->height;
}

static void
	fill_colour_map(
		t_colour_map *map,
		const t_texumn texumn,
		uint32_t column_height)
{
	const float	scale = 2 * column_height / (float)texumn.height;
	float		leftover;
	uint32_t	i;

	leftover = 0;
	i = 0;
	while (i < texumn.height)
	{
		map->buffer[i].colour = texumn.pixels[i];
		map->buffer[i].len = scale + leftover;
		leftover += scale - map->buffer[i].len;
		i++;
	}
	while (map->start < 0 && map->index < map->size)
	{
		while (map->start < 0 && map->buffer[map->index].len)
		{
			map->buffer[map->index].len--;
			map->start++;
		}
		if (map->start >= 0)
			break ;
		map->index++;
	}
}

static void
	fill_screen_column(
		mlx_image_t	*walls,
		const t_colour_map map,
		uint32_t screen_x_index)
{
	uint32_t	screen_y_index;
	uint32_t	map_index;
	uint32_t	texel_index;

	screen_y_index = (uint32_t)map.start;
	map_index = map.index;
	while (map_index < map.size)
	{
		texel_index = 0;
		while (texel_index < map.buffer[map_index].len)
		{
			((uint32_t *)walls->pixels)[screen_y_index * walls->width
				+ screen_x_index] = map.buffer[map_index].colour;
			screen_y_index++;
			if (screen_y_index >= walls->height)
				return ;
			texel_index++;
		}
		map_index++;
	}
}

void
	draw_texture_column(
		t_ray *ray,
		t_walls *walls,
		t_camera *camera,
		uint32_t screen_x)
{
	static t_colour_map	map = (t_colour_map){NULL, 0, 0, 0};
	t_texumn			texumn;
	uint32_t			column_height;

	column_height = (walls->image->height / ray->distance / 2);
	map.start = (int)(walls->image->height / 2 - column_height);
	map.index = 0;
	init_texumn(&texumn, ray, walls, camera);
	if (texumn.height != map.size)
	{
		map.buffer = (t_texel *)malloc(texumn.height * sizeof(t_texel));
		if (map.buffer == NULL)
			error_exit(0, errno, "colour_map buffer allocation failed");
		map.size = texumn.height;
	}
	fill_colour_map(&map, texumn, column_height);
	fill_screen_column(walls->image, map, screen_x);
}
