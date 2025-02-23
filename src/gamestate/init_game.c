/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/23 18:09:42 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_movement_matrix()
{
	g_movement_matrix[0][0] = -1 / sqrtf(2);
	g_movement_matrix[0][1] = 0;
	g_movement_matrix[0][2] = 1 / sqrtf(2);
	g_movement_matrix[1][0] = -1;
	g_movement_matrix[1][1] = 0;
	g_movement_matrix[1][2] = 1;
	g_movement_matrix[2][0] = -1 / sqrtf(2);
	g_movement_matrix[2][1] = 0;
	g_movement_matrix[2][2] = 1 / sqrtf(2);
}

// adapt to fit new archit
static int
	camera_init(
		t_camera *camera,
		int pos_y,
		int pos_x,
		char cardinal)
{
	camera->aspect_ratio = 1.0 * WIDTH / HEIGHT;
	camera->pos_y = pos_y + 0.5;
	camera->pos_x = pos_x + 0.5;
	camera->dir_x = 0;
	camera->dir_y = 0;
	if (cardinal == 'N')
		camera->dir_y = -1;
	if (cardinal == 'E')
		camera->dir_x = 1;
	if (cardinal == 'S')
		camera->dir_y = 1;
	if (cardinal == 'W')
		camera->dir_x = -1;
	camera->plane_x = CAMERA_PLANE * camera->aspect_ratio * -camera->dir_y;
	camera->plane_y = CAMERA_PLANE * camera->aspect_ratio * camera->dir_x;
	camera->movement_speed = MOVEMENT_SPEED;
	camera->rotation_cosin[0] = cos(ROTATION_SPEED);
	camera->rotation_cosin[1] = sin(ROTATION_SPEED);
	camera->sign_rotate = 0;
}

static int
	get_content(
		char ***dest,
		char *input_file)
{
	char	*buffer;
	int		fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		return (RETURN_FAILURE);
	buffer = ft_get_next_line(fd);
	if (buffer == NULL)
		return (RETURN_FAILURE);
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
		char *input_file)
{
	char	**content_start;
	char	**content_progress;

	if (get_content(&content_start, input_file) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	content_progress = content_start;
	read_elements(scene, content_progress);
	if (scene->walls.north_texture == NULL || scene->walls.east_texture == NULL
		|| scene->walls.south_texture == NULL || scene->walls.west_texture == NULL)
		error_exit(mlx_errno, EINVAL, "missing scene.cub texture path");
	if (read_map(scene, content_progress) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	ft_arrclear((void **)content_progress);
	return (RETURN_SUCCESS);
}

int	game_init(
		t_scene *scene,
		char *input_file)
{
	if (parse_input_file(scene, input_file) != RETURN_SUCCESS
		|| camera_init(&scene->player.camera) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	init_movement_matrix();
	scene->walls.recast = true;
	return (RETURN_SUCCESS);
}
