/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu_images.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 01:21:59 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t
	get_scaled_pixel_colour(
		t_scalable *scalable,
		float x,
		float y)
{
	mlx_texture_t	*texture;
	uint32_t		index;
	uint8_t			*pixelstart;

	texture = scalable->texture;
	x /= scalable->scale;
	y /= scalable->scale;
	if (x < 0 || x >= texture->width
		|| y < 0 || y >= texture->height)
		return (0x00000000);
	index = ((int)y * texture->width + (int)x) * sizeof(uint32_t);
	pixelstart = &texture->pixels[index];
	return ((uint32_t)(pixelstart[0] << 24 | pixelstart[1] << 16
		| pixelstart[2] << 8 | pixelstart[3]));
}

void
	draw_scaled_image(
		t_scalable *scalable)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	colour;

	y = 0;
	while (y < scalable->image->height)
	{
		x = 0;
		while (x < scalable->image->width)
		{
			colour = get_scaled_pixel_colour(scalable, x, y);
			mlx_put_pixel(scalable->image, x, y, colour);
			++x;
		}
		++y;
	}
}

static int
	new_scaled_image(
		mlx_t *mlx,
		t_scalable *dest)
{
	dest->image = mlx_new_image(mlx,
			dest->texture->width * dest->scale,
			dest->texture->height * dest->scale);
	if (dest->image == NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int
	create_menu_images(
		mlx_t *mlx,
		t_menu *menu)
{
	size_t	i;

	if (new_scaled_image(mlx, &menu->background) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, menu->background.image, 0, 0) < 0)
		return (RETURN_FAILURE);
	i = 0;
	while (i < MENU_B_COUNT)
	{
		if (new_scaled_image(mlx, &menu->buttons[i]) != RETURN_SUCCESS)
			return (RETURN_FAILURE);
		if (mlx_image_to_window(mlx, menu->buttons[i].image,
				menu->buttons_x_offset, menu->buttons_y_offset
				+ menu->buttons_y_margin * i * 2) < 0)
			return (RETURN_FAILURE);
		++i;
	}
	if (new_scaled_image(mlx, &menu->highlight) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (mlx_image_to_window(mlx, menu->highlight.image, 0, 0) < 0)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
