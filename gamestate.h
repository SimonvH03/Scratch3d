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
# include "libft/libft.h"

typedef struct s_camera
{
	float			aspect_ratio;
	float			pos_y;
	float			pos_x;
	float			dir_y;
	float			dir_x;
	float			plane_y;
	float			plane_x;
	float			rotation_cosin[2];
	float			movement_matrix[3][3];
	float			movement_speed;
	short			sign_rotate;
}	t_camera;

// free: scene->map
typedef struct s_scene
{
	mlx_image_t		*walls;
	mlx_image_t		*background;
	t_camera		camera;
	char			*name;
	char			**content;
	char			**r_content;
	int				**map;
	int				y_max;
	int				x_max;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*player_texture;
	uint32_t		floor;
	uint32_t		ceiling;
	bool			recast;
}	t_scene;

#endif