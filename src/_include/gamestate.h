/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gamestate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/03/04 23:54:12 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_H
# define GAMESTATE_H
# include "MLX42/MLX42_Int.h"

typedef struct s_scalable
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	float			scale;
}	t_scalable;

extern float		g_movement_matrix[3][3];

// 4B aligned, 10 x 4 (float) + 1 x 2 (short), 2B padding		| 44 Bytes
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

typedef struct s_weapon
{
	mlx_texture_t	**fire;
	mlx_texture_t	**reload;
	t_scalable		current_frame;
	uint32_t		damage;
	uint32_t		mag_capacity;
	uint32_t		total_ammo;
	uint32_t		ammo;
	unsigned int	frame_index;
	float			frame_time;
	float			frame_time_goal;
	bool			is_firing;
	bool			is_reloading;
}	t_weapon;

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
	unsigned int	y_max;
	unsigned int	x_max;
}	t_grid;

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