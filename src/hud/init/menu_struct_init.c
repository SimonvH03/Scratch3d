/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_struct_init.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/04 22:26:03 by simon         #+#    #+#                 */
/*   Updated: 2025/02/23 00:06:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short
	init_menu_background(
		mlx_t *mlx,
		t_scalable *background)
{
	background->texture = mlx_load_png(MENU_BACKGROUND_PATH);
	if (background->texture == NULL)
		return (RETURN_FAILURE);
	background->scale = 1;
	background->scale = ft_max_float(
			1.0 * mlx->width / background->texture->width,
			1.0 * mlx->height / background->texture->height);
	return (RETURN_SUCCESS);
}

static short
	init_menu_button(
		mlx_t *mlx,
		t_scalable *button,
		const char *path)
{
	button->texture = &mlx_load_xpm42(path)->texture;
	if (button->texture == NULL)
		return (RETURN_FAILURE);
	button->scale = 1;
	button->scale = ft_min_float(
			1.0 * (mlx->width / 3) / button->texture->width,
			1.0 * (mlx->height / 10) / button->texture->height);
	return (RETURN_SUCCESS);
}

short
	init_menu_structs(
		mlx_t *mlx,
		t_menu *menu)
{
	t_scalable	*tempb;

	if (init_menu_background(mlx, &menu->background)
		!= RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_menu_button(mlx, &menu->buttons[MENU_B_START_INDEX],
			MENU_B_START_PATH) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_menu_button(mlx, &menu->buttons[MENU_B_QUIT_INDEX],
			MENU_B_QUIT_PATH) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_menu_button(mlx, &menu->highlight,
			MENU_B_HIGHLIGHT_PATH) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	tempb = &menu->highlight;
	menu->buttons_x_offset = mlx->width / 2
		- tempb->texture->width * tempb->scale / 2;
	menu->buttons_y_margin = tempb->texture->height * tempb->scale;
	menu->buttons_y_offset = mlx->height / 2
		- menu->buttons_y_margin * MENU_B_COUNT;
	menu->selection = 0;
	return (RETURN_SUCCESS);
}
