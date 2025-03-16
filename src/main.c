/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:07:41 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message)
{
	if (custom_errno == 0)
		custom_errno = errno;
	if (write(STDERR_FILENO, "Error\n", 7) == -1)
		exit(errno);
	if (mlx_errno)
		printf("mlx_errno: %3d: %s\n", mlx_errno, mlx_strerror(mlx_errno));
	if (custom_errno)
		printf("std_errno: %3d: %s\n", custom_errno, strerror(custom_errno));
	if (message)
		printf("message  :    : %s\n", message);
	exit(errno);
}

static void	cub3d_terminate(t_window *window)
{
	size_t	i;

	mlx_terminate(window->mlx);
	mlx_delete_texture(window->hud.player_icon);
	mlx_delete_texture(window->scene.walls.north_texture);
	mlx_delete_texture(window->scene.walls.east_texture);
	mlx_delete_texture(window->scene.walls.south_texture);
	mlx_delete_texture(window->scene.walls.west_texture);
	mlx_delete_texture(window->menu.background.texture);
	mlx_delete_texture(window->menu.highlight.texture);
	i = 0;
	while (i < MENU_B_COUNT)
		mlx_delete_texture(window->menu.buttons[i++].texture);
	ft_arrclear((void **)window->scene.grid.tilemap);
	free((void *)window->hud.minimap.circle_overlay);
}

static void
	link_loop_hooks(
		t_window *window)
{
	mlx_key_hook(window->mlx, window_keyhook, window);
	mlx_loop_hook(window->mlx, frametime_dependant_variables, window);
	mlx_loop_hook(window->mlx, view_manager, window);
}

int main(int argc, char **argv)
{
	t_window	window;

	ft_bzero(&window, sizeof(t_window));
	if (argc != 2)
	{
		printf("Usage:\n%s <path/to/scene.cub>\n", argv[0]);
		return (EINVAL);
	}
	if (init_window(&window) != RETURN_SUCCESS
		|| init_game(window.mlx, &window.scene, argv[1]) != RETURN_SUCCESS
		|| init_hud(window.mlx, &window.hud, &window.scene) != RETURN_SUCCESS
		|| init_menu(window.mlx, &window.menu) != RETURN_SUCCESS)
	{
		error_exit(mlx_errno, errno, "initialisation failed");
	}
	// draw_textures(&window);
	link_loop_hooks(&window);
	mlx_loop(window.mlx);
	cub3d_terminate(&window);
	return (RETURN_SUCCESS);
}
