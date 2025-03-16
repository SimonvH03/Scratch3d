/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gamestate.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/03/17 00:51:20 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_H
# define GAMESTATE_H
# include "MLX42/MLX42_Int.h"

# define SOLID_MASK		0x8000
# define SOLID_SHIFT	15
# define ID_MASK		0x7F00
# define ID_SHIFT		8
# define TYPE_MASK		0xFF

enum	e_weapon_state
{
	ws_idle,
	ws_firing,
	ws_reloading
};

enum	e_door_state
{
	ds_open,
	ds_closed,
	ds_opening,
	ds_closing
};

extern float	g_movement_matrix[3][3];

typedef struct s_scalable
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	float			scale;
}	t_scalable;

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
	mlx_texture_t		*rest;
	mlx_texture_t		**fire;
	mlx_texture_t		**reload;
	t_scalable			scalable;
	uint32_t			damage;
	uint32_t			mag_capacity;
	uint32_t			total_ammo;
	uint32_t			ammo;
	unsigned int		frame_index;
	float				frame_time;
	float				frame_time_goal;
	enum e_weapon_state	state;
}	t_weapon;

typedef struct s_player
{
	t_camera		camera;
	t_weapon		weapon;
	uint32_t		health;
	uint32_t		treasure;
}	t_player;

// 8B aligned, 5 x 8 (pointer) + 1 x 1 (bool), 7B padding		| 48 Bytes
typedef struct s_walls
{
	mlx_image_t		*image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*door_texture;
	bool			recast;
}	t_walls;

typedef struct s_door
{
	int16_t				*cell;
	float				position;
	unsigned int		pos_y;
	unsigned int		pos_x;
	enum e_door_state	state;
}	t_door;

typedef struct s_doors
{
	t_door			*list;
	unsigned int	count;
	float			frame_shift;
}	t_doors;

// 8B aligned, 2 x 8 (pointer) + 2 x 4 (int), no padding		| 24 Bytes
typedef struct s_grid
{
	int16_t			**tilemap;
	t_doors			doors;
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