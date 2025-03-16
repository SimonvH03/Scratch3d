/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:18:41 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	get_content(
		char ***dest,
		const char *input_file)
{
	char	*buffer;
	int		fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		return (RETURN_ERROR);
	buffer = ft_get_next_line(fd);
	if (buffer == NULL)
		return (RETURN_ERROR);
	*dest = NULL;
	while (buffer != NULL)
	{
		if (buffer[0] != '\n')
		{
			if (buffer[ft_strlen(buffer) - 1] == '\n')
				buffer[ft_strlen(buffer) - 1] = '\0';
			*dest = ft_arrcat(*dest, buffer);
			if (*dest == NULL)
				error_exit(0, errno, "get_content() ft_arrcat()");
		}
		else
			free(buffer);
		buffer = ft_get_next_line(fd);
	}
	return (RETURN_SUCCESS);
}

static int
	parse_input_file(
		t_scene *scene,
		const char *input_file)
{
	char	**content_start;
	char	*const *content_progress;

	if (get_content(&content_start, input_file) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	content_progress = content_start;
	read_elements(scene, &content_progress);
	if (scene->walls.north_texture == NULL || scene->walls.east_texture == NULL
		|| scene->walls.south_texture == NULL || scene->walls.west_texture == NULL)
		error_exit(mlx_errno, EINVAL, "missing scene.cub texture path");
	if (read_map(&scene->grid, content_progress) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	ft_arrclear((void **)content_start);
	if (interpret_map(&scene->grid) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int
	init_game(
		mlx_t *mlx,
		t_scene *scene,
		const char *input_file)
{
	if (parse_input_file(scene, input_file) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_player(&scene->player, &scene->grid) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_game_images(mlx, scene) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (init_weapon(mlx, &scene->player.weapon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	scene->walls.recast = true;
	return (RETURN_SUCCESS);
}
