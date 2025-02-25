/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/25 22:50:42 by simon         ########   odam.nl         */
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
		if (window->scene.walls.recast == true)
		{
			raycast(&window->scene);
			if (window->hud.minimap.enabled == true)
				draw_minimap_walls(&window->hud.minimap);
			if (window->hud.bigmap.enabled == true)
				draw_bigmap_player(&window->hud.bigmap);
			window->scene.walls.recast = false;
		}
	}
}

void
	toggle_maps(
		t_window *window,
		t_minimap *minimap,
		t_bigmap *map)
{
	minimap->player_icon->enabled = !minimap->player_icon->enabled;
	minimap->walls->enabled = !minimap->walls->enabled;
	minimap->enabled = !minimap->enabled;
	map->player_icon->enabled = !map->player_icon->enabled;
	map->walls->enabled = !map->walls->enabled;
	map->enabled = !map->enabled;
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
