/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/05 18:30:37 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	g_movement_matrix[3][3];

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

static void
	init_camera(
		t_camera *camera,
		const int pos_y,
		const int pos_x,
		const char cardinal)
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

static bool
	norminetteisahorriblewasteoftimethisisnotmorereadable(
		bool grid_has_starting_position)
{
	if (grid_has_starting_position == true)
	{
		printf("invalid map: has multiple starting positions\n");
			return (true);
	}
	return (false);
}

static bool
	find_starting_position(
		t_grid *grid,
		t_camera *camera)
{
	bool			grid_has_starting_position;
	unsigned int	y;
	unsigned int	x;

	grid_has_starting_position = false;
	y = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			if (ft_strchr("NESW", grid->sprites[y][x])
				&& grid->sprites[y][x] != 0)
			{
				if (norminetteisahorriblewasteoftimethisisnotmorereadable(
						grid_has_starting_position) == true)
					return (false);
				init_camera(camera, y, x, grid->sprites[y][x]);
				grid_has_starting_position = true;
			}
			x++;
		}
		y++;
	}
	return (grid_has_starting_position);
}

int
	init_player(
		t_player *player,
		t_grid *grid)
{
	init_movement_matrix();
	player->health = STARTING_HEALTH;
	player->treasure = 0;
	if (find_starting_position(grid, &player->camera) != true)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
