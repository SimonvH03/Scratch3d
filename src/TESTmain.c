/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   TESTmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/23 19:34:58 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	error_exit(
		mlx_errno_t mlx_errno,
		int custom_errno,
		char *message)
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

// int main(int argc, char **argv)
// {
// 	t_window	window;

// 	ft_bzero(&window, sizeof(t_window));
// 	if (argc != 2)
// 	{
// 		printf("Usage: ./%s <path/to/scene.cub>\n", argv[0]);
// 		return (EINVAL);
// 	}
// 	if (window_init(&window) != RETURN_SUCCESS
// 		|| menu_init() != RETURN_SUCCESS
// 		|| game_init(&window.scene, argv[1]) != RETURN_SUCCESS
// 		|| hud_init() != RETURN_SUCCESS)
// 	{
// 		error_exit(mlx_errno, errno, "initialisation failed");
// 	}
// 	link_loop_hooks(&window);
// 	mlx_loop(window.mlx);
// 	cub3d_terminate(&window);
// 	return (RETURN_SUCCESS);
// }

int main(int argc, char **argv)
{
	t_window	window;

	ft_bzero(&window, sizeof(t_window));
	if (argc != 2)
	{
		printf("Usage: ./%s <path/to/scene.cub>\n", argv[0]);
		return (EINVAL);
	}
	if (window_init(&window) != RETURN_SUCCESS
		|| game_init(&window.scene, argv[1]) != RETURN_SUCCESS)
	{
		error_exit(mlx_errno, errno, "initialisation failed");
	}
	// link_loop_hooks(&window);
	// mlx_loop(window.mlx);
	// cub3d_terminate(&window);
	return (RETURN_SUCCESS);
}
