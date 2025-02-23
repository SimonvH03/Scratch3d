/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_image_create.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/23 00:06:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short
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

static short
	new_images_menu(
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
	up_down_select(menu);
	return (RETURN_SUCCESS);
}

short
	init_menu_images(
		mlx_t *mlx,
		t_menu *menu)
{
	if (new_images_menu(mlx, menu) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	draw_scaled_image(&menu->background);
	draw_scaled_image(&menu->highlight);
	draw_scaled_image(&menu->buttons[MENU_B_START_INDEX]);
	draw_scaled_image(&menu->buttons[MENU_B_QUIT_INDEX]);
	return (RETURN_SUCCESS);
}
