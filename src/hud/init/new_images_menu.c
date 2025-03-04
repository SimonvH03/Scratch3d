/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_images_menu.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/03/04 21:59:16 by svan-hoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	sample_scalable(
		mlx_image_t *dest,
		void *param,
		uint32_t img_x,
		uint32_t img_y)
{
	const t_scalable	*scalable = (t_scalable *)param;
	const mlx_texture_t	*texture = scalable->texture;
	const float			x = img_x / scalable->scale;
	const float			y = img_y / scalable->scale;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (RETURN_SUCCESS);
	((uint32_t *)dest->pixels)[img_y * dest->width + img_x]
		= ((uint32_t *)texture->pixels)[(int)y * texture->width + (int)x];
	return (RETURN_SUCCESS);
}

int
	new_scaled_image(
		mlx_t *mlx,
		t_scalable *dest)
{
	dest->image = mlx_new_image(mlx,
			dest->texture->width * dest->scale,
			dest->texture->height * dest->scale);
	if (dest->image == NULL)
		return (RETURN_FAILURE);
	image_iteration(dest->image, sample_scalable, dest);
	return (RETURN_SUCCESS);
}

int
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
	return (RETURN_SUCCESS);
}
