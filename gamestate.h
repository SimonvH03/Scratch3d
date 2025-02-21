/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:06:35 by simon             #+#    #+#             */
/*   Updated: 2024/09/23 02:15:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_H
# define GAMESTATE_H
# include "MLX42/include/MLX42/MLX42_Int.h"

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

// swapback arrays for each enemy state? alerted, shooting, dead
// typedef struct s_sprites
// {

// }	t_sprites;

// 8B aligned, 2 x 8 (pointer) + 2 x 4 (int), no padding		| 24 Bytes
typedef	struct s_grid
{
	int				**walls;
	int				**sprites;
	int				y_max;
	int				x_max;
}	t_grid;

// 8B aligned, 88 (camera) + 48 (walls) + 24 (grid)		| (160B)
//	+ 4 x 8 (pointers) + 2 x 8 (uint32_t), no padding	| (48B) | 208 Bytes
typedef struct s_scene
{
	t_walls			walls;
	t_grid			grid;
	t_camera		camera;
	char			*name;
	char			**content;
	mlx_image_t		*background;
	mlx_texture_t	*player_texture;
	uint32_t		floor_clr;
	uint32_t		ceiling_clr;
}	t_scene;

#endif