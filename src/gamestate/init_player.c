/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 23:52:54 by simon         ########   odam.nl         */
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

static void
	find_starting_position(
		t_grid *grid,
		t_camera *camera,
		bool *found_starting_position)
{
	unsigned int	y;
	unsigned int	x;
	uint16_t		cell;

	y = 0;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			cell = grid->tilemap[y][x];
			if (ft_strchr("NESW", get_type(cell)) && get_type(cell) != 0)
			{
				if (*found_starting_position == true)
					error_exit(mlx_errno, EINVAL,
						"invalid map: multiple player positions");
				init_camera(camera, y, x, get_type(cell));
				*found_starting_position = true;
				grid->tilemap[y][x] = set_cell(false, 0, '0');
			}
			x++;
		}
		y++;
	}

}

int
	init_player(
		t_player *player,
		t_grid *grid)
{
	bool	found_starting_position;

	init_movement_matrix();
	found_starting_position = false;
	find_starting_position(grid, &player->camera, &found_starting_position);
	if (found_starting_position == false)
		error_exit(mlx_errno, EINVAL, "invalid map: missing player position");
	player->health = STARTING_HEALTH;
	player->treasure = 0;
	return (RETURN_SUCCESS);
}
