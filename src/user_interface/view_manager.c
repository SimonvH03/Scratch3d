/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/28 01:38:17 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	view_manager(
		void *param)
{
	t_window	*window;
	mlx_t		*mlx;

	window = param;
	mlx = window->mlx;
	if (window->view == wv_game)
	{
		wasd_move(mlx, &window->scene.grid, &window->scene.player.camera);
		arrowkey_turn(mlx, &window->scene.player.camera);
		mouse_pan(mlx, &window->scene.player.camera);
		weapon_animation(mlx, &window->scene.player.weapon);
		update_doors(&window->scene.grid, mlx->delta_time);
		raycast(&window->scene);
		if (window->hud.minimap.enabled == true)
			update_minimap(&window->hud.minimap);
		if (window->hud.bigmap.enabled == true)
			update_bigmap(&window->hud.bigmap);
	}
}

void
	toggle_maps(
		t_minimap *minimap,
		t_bigmap *bigmap)
{
	minimap->player_icon.image->enabled = !minimap->player_icon.image->enabled;
	minimap->walls->enabled = !minimap->walls->enabled;
	minimap->enabled = !minimap->enabled;
	bigmap->player->enabled = !bigmap->player->enabled;
	bigmap->walls->enabled = !bigmap->walls->enabled;
	bigmap->enabled = !bigmap->enabled;
}

void
	toggle_view(
		t_window *window)
{
	size_t	i;

	if (window->view == wv_menu)
		window->view = wv_game;
	else if (window->view == wv_game)
		window->view = wv_menu;
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
