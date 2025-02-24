// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   main.c                                             :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/01/31 18:33:20 by svan-hoo      #+#    #+#                 */
// /*   Updated: 2025/02/23 19:19:00 by simon         ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// void
// 	error_exit(
// 		mlx_errno_t mlx_errno,
// 		int custom_errno,
// 		char *message)
// {
// 	if (custom_errno == 0)
// 		custom_errno = errno;
// 	if (write(STDERR_FILENO, "Error\n", 7) == -1)
// 		exit(errno);
// 	if (mlx_errno)
// 		printf("mlx_errno: %3d: %s\n", mlx_errno, mlx_strerror(mlx_errno));
// 	if (custom_errno)
// 		printf("std_errno: %3d: %s\n", custom_errno, strerror(custom_errno));
// 	if (message)
// 		printf("message  :    : %s\n", message);
// 	exit(errno);
// }

// static void
// 	cub3d_terminate(
// 		t_window *window)
// {
// 	size_t	i;

// 	mlx_terminate(window->mlx);
// 	mlx_delete_texture(window->scene.player_icon);
// 	mlx_delete_texture(window->scene.north_texture);
// 	mlx_delete_texture(window->scene.east_texture);
// 	mlx_delete_texture(window->scene.south_texture);
// 	mlx_delete_texture(window->scene.west_texture);
// 	mlx_delete_texture(window->menu.background.texture);
// 	mlx_delete_texture(window->menu.highlight.texture);
// 	i = 0;
// 	while (i < MENU_B_COUNT)
// 	{
// 		mlx_delete_texture(window->menu.buttons[i].texture);
// 		++i;
// 	}
// 	ft_arrclear((void **)window->scene.map);
// 	free((void *)window->minimap.circle_overlay);
// }

// static void
// 	update_time_dependant_variables(
// 		void	*param)
// {
// 	t_window	*window;
// 	t_camera	*camera;
// 	char		*tempf;

// 	window = param;
// 	camera = &window->scene.camera;
// 	tempf = ft_itoa(1 / window->mlx->delta_time);
// 	mlx_delete_image(window->mlx, window->fps);
// 	window->fps = mlx_put_string(window->mlx, tempf,
// 			window->mlx->width / 2, window->mlx->height / 42);
// 	free(tempf);
// 	camera->movement_speed = MOVEMENT_SPEED * window->mlx->delta_time;
// 	if (camera->movement_speed > 0.49)
// 		camera->movement_speed = 0.49;
// 	g_rotation_cosin[0] = cosf(ROTATION_SPEED * window->mlx->delta_time);
// 	g_rotation_cosin[1] = sinf(ROTATION_SPEED * window->mlx->delta_time);
// }

// static void
// 	link_loop_hooks(
// 		t_window *window)
// {
// 	mlx_key_hook(window->mlx, &window_keyhook, window);
// 	mlx_loop_hook(window->mlx, &update_time_dependant_variables, window);
// 	mlx_loop_hook(window->mlx, &view_manager, window);
// }

// int main(int argc, char **argv)
// {
// 	t_window	window;

// 	ft_bzero(&window, sizeof(t_window));
// 	if (argc != 2)
// 	{
// 		printf("Usage: ./%s <path/to/scene.cub>\n", argv[0]);
// 		return (EINVAL);
// 	}
// 	if (init_window(&window) != RETURN_SUCCESS
// 		|| init_menu() != RETURN_SUCCESS
// 		|| init_game(&window.scene, argv[1]) != RETURN_SUCCESS
// 		|| init_hud() != RETURN_SUCCESS)
// 	{
// 		error_exit(mlx_errno, errno, "initialisation failed");
// 	}
// 	link_loop_hooks(&window);
// 	mlx_loop(window.mlx);
// 	cub3d_terminate(&window);
// 	return (RETURN_SUCCESS);
// }
