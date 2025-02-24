/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   select_button.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 23:36:30 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/24 01:19:11 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	select_button(
		t_menu *menu)
{
	menu->highlight.image->instances[0].x
		= menu->buttons[menu->selection].image->instances[0].x;
	menu->highlight.image->instances[0].y
		= menu->buttons[menu->selection].image->instances[0].y;
}

void
	confirm_selection(
		t_menu *menu,
		t_window *window)
{
	if (menu->selection == MENU_B_START_INDEX)
		toggle_view(window);
	if (menu->selection == MENU_B_QUIT_INDEX)
		mlx_close_window(window->mlx);
}
