/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gamestate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/02/22 23:17:19 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_H
# define GAMESTATE_H
# include "MLX42_Int.h"

float				g_movement_matrix[3][3];

// 8B aligned, 10 x 8 (float) + 1 x 4 (short), 4B padding		| 88 Bytes
typedef struct s_camera
{
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	float			movement_speed;
	float			rotation_cosin[2];
	float			aspect_ratio;
	short			sign_rotate;
}	t_camera;

// 8B aligned, 1 x 8 (pointer) + 3 x 8 (uint32), 0B padding		| 24 Bytes
typedef struct s_weapon
{
	char			*name;
	uint32_t		damage;
	uint32_t		magazine_size;
	uint32_t		ammo;
}	t_weapon;

// 8B aligned, 88 (camera) + 24 (weapon)				| (112B)
//	+ 2 x 8 (uint32), no padding						| (16B)	| 128 Bytes
typedef struct s_player
{
	t_camera		camera;
	t_weapon		weapon;
	uint32_t		health;
	uint32_t		treasure;
}	t_player;

// 8B aligned, 5 x 8 (pointer) + 1 x 1 (bool), 7B padding		| 48 Bytes
typedef	struct s_walls
{
	mlx_image_t		*image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	bool			recast;
}	t_walls;

// 8B aligned, 2 x 8 (pointer) + 2 x 4 (int), no padding		| 24 Bytes
typedef	struct s_grid
{
	int				**walls;
	int				**sprites;
	int				y_max;
	int				x_max;
}	t_grid;

// 8B aligned, 88 (Player) + 48 (Walls) + 24 (grid)		| (160B)
//	+ 1 x 8 (pointers) + 2 x 8 (uint32_t), no padding	| (24B) | 184 Bytes
typedef struct s_scene
{
	t_walls			walls;
	t_grid			grid;
	t_player		player;
	mlx_image_t		*background;
	uint32_t		floor_clr;
	uint32_t		ceiling_clr;
}	t_scene;

#endif