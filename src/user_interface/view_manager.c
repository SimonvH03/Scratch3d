/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/05 00:03:46 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	if (window->view == GAME)
	{
		wasd_move(window, &window->scene.player.camera);
		arrowkey_turn(window, &window->scene.player.camera);
		if (window->scene.walls.recast == true || 1)
		{
			raycast(&window->scene);
			if (window->hud.minimap.enabled == true)
				update_minimap(&window->hud.minimap);
			if (window->hud.bigmap.enabled == true)
				update_bigmap(&window->hud.bigmap);
			window->scene.walls.recast = false;
		}
	}
}

void
	toggle_maps(
		t_window *window,
		t_minimap *minimap,
		t_bigmap *bigmap)
{
	minimap->player_icon.image->enabled = !minimap->player_icon.image->enabled;
	minimap->walls->enabled = !minimap->walls->enabled;
	minimap->enabled = !minimap->enabled;
	bigmap->player->enabled = !bigmap->player->enabled;
	bigmap->walls->enabled = !bigmap->walls->enabled;
	bigmap->enabled = !bigmap->enabled;
	window->scene.walls.recast = true;
}

void
	toggle_view(
		t_window *window)
{
	size_t	i;

	if (window->view == MENU)
		window->view = GAME;
	else if (window->view == GAME)
		window->view = MENU;
	window->menu.background.image->enabled
		= !window->menu.background.image->enabled;
	window->menu.highlight.image->enabled
		= !window->menu.highlight.image->enabled;
	i = 0;
	while (i < MENU_B_COUNT)
	{
		window->menu.buttons[i].image->enabled
			= !window->menu.buttons[i].image->enabled;
		++i;
	}
}
