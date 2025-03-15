/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_manager.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/15 23:23:25 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	update_fps_image(
		double delta_time,
		t_fps *fps)
{
	char		buffer[12];
	uint32_t	output_fps;

	ft_bzero(buffer, 12);
	fps->cum_time += delta_time;
	++fps->no_frames;
	if (fps->cum_time < 0.01)
		return ;
	output_fps = fps->no_frames / fps->cum_time;
	fps->cum_time = 0;
	fps->no_frames = 0;
	if (output_fps > 99999)
		output_fps = 99999;
	ft_putnbr_ptr(buffer, output_fps);
	reset_image(fps->image);
	modlx_put_string(fps->image, buffer);
}

void
	view_manager(
		void *param)
{
	t_window	*window;

	window = param;
	update_fps_image(window->mlx->loop_time, &window->hud.fps);
	if (window->view == GAME)
	{
		wasd_move(window->mlx, &window->scene, &window->scene.player.camera);
		arrowkey_turn(window->mlx, &window->scene, &window->scene.player.camera);
		weapon_animation(window->mlx, &window->scene.player.weapon);
		door_animation(window->mlx, &window->scene);
		if (window->scene.walls.recast == true || 1)// 1 for consistent frametime
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
