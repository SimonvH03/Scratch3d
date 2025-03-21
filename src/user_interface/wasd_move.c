/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wasd_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 20:10:07 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void
// 	do_movement(
// 		t_camera *camera,
// 		int	**map,
// 		short forward_backward,
// 		short left_right)
// {
// 	float	cos_sin[2];
// 	float	move_dir_x;
// 	float	move_dir_y;
// 	float	hitbox_x;
// 	float	hitbox_y;
// 	float	wall_dist_x;
// 	float	wall_dist_y;
// 	float	next_x;
// 	float	next_y;

// 	cos_sin[0] = g_movement_matrix[1 + left_right][1 + forward_backward];
// 	cos_sin[1] = g_movement_matrix[1 + forward_backward][1 + left_right];

// 	move_dir_x = camera->dir_x * cos_sin[0] + camera->dir_y * -cos_sin[1];
// 	move_dir_y = camera->dir_x * cos_sin[1] + camera->dir_y * cos_sin[0];

// 	hitbox_x = COLLISION_HITBOX * ft_sign_float(move_dir_x);
// 	hitbox_y = COLLISION_HITBOX * ft_sign_float(move_dir_y);

// 	wall_dist_x = (int)camera->pos_x + (move_dir_x > 0) - camera->pos_x;
// 	wall_dist_y = (int)camera->pos_y + (move_dir_y > 0) - camera->pos_y;

// 	next_x = camera->pos_x + move_dir_x * camera->movement_speed;
// 	next_y = camera->pos_y + move_dir_y * camera->movement_speed;

// 	if ((int)(next_x + hitbox_x) < 0 || (int)(next_x + hitbox_x) > scene->x_max
// 		|| (int)camera->pos_y < 0 || (int)camera->pos_y > scene->y_max
// 		|| map[(int)camera->pos_y][(int)(next_x + hitbox_x)])
// 		move_dir_x = wall_dist_x - hitbox_x;

// 	if ((int)(next_y + hitbox_y) < 0 || (int)(next_y + hitbox_y) > scene->y_max
// 		|| (int)camera->pos_x < 0 || (int)camera->pos_x > scene->x_max
// 		|| map[(int)(next_y + hitbox_y)][(int)camera->pos_x])
// 		move_dir_y = wall_dist_y - hitbox_y;

// 	camera->pos_x += move_dir_x * camera->movement_speed;
// 	camera->pos_y += move_dir_y * camera->movement_speed;
// }

// looks up the sin and cosin values based on which of the 8 directions
//	(9 if you count 0, 0) the player can move
// each directions has precalculated normalized x and y direction components
//  based on the unit circle /pythagoras because why bother with cos45 or sin45
// !this function assumes the camera is not currently outside of the map
// !this function was pretty readable. but norminette. see better version above
static void
	move_camera(
		t_camera *camera,
		int16_t	**map,
		short forward_backward,
		short left_right)
{
	float	cos_sin[2];
	float	move_dir_x;
	float	move_dir_y;

	cos_sin[0] = g_movement_matrix[1 + left_right][1 + forward_backward];
	cos_sin[1] = g_movement_matrix[1 + forward_backward][1 + left_right];
	move_dir_x = camera->dir_x * cos_sin[0] + camera->dir_y * -cos_sin[1];
	move_dir_y = camera->dir_x * cos_sin[1] + camera->dir_y * cos_sin[0];
	if (is_solid(map[(int)camera->pos_y]
		[(int)(camera->pos_x + move_dir_x * camera->movement_speed
			+ COLLISION_HITBOX * ft_sign_float(move_dir_x))]))
		move_dir_x = (int)camera->pos_x + (move_dir_x > 0) - camera->pos_x
			- COLLISION_HITBOX * ft_sign_float(move_dir_x);
	camera->pos_x += move_dir_x * camera->movement_speed;
	if (is_solid(map[(int)(camera->pos_y + move_dir_y * camera->movement_speed
			+ COLLISION_HITBOX * ft_sign_float(move_dir_y))]
			[(int)camera->pos_x]))
		move_dir_y = (int)camera->pos_y + (move_dir_y > 0) - camera->pos_y
			- COLLISION_HITBOX * ft_sign_float(move_dir_y);
	camera->pos_y += move_dir_y * camera->movement_speed;
}

void
	wasd_move(
		mlx_t *mlx,
		t_scene *scene,
		t_camera *camera)
{
	short	forward_backward;
	short	left_right;

	forward_backward = 0;
	left_right = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		forward_backward += 1;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		forward_backward -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		left_right -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		left_right += 1;
	if (forward_backward || left_right)
	{
		move_camera(camera, scene->grid.tilemap, forward_backward, left_right);
		scene->walls.recast = true;
	}
}
