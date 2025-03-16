/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/03/16 04:42:34 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "MLX42/MLX42_Int.h"

enum	e_hit_axis
{
	ha_horizontal,
	ha_vertical
};

typedef struct s_column
{
	int				height;
	int				start;
	int				end;
	mlx_texture_t	*texture;
	float			x;
	float			step;
	float			y;
}	t_column;

typedef struct s_ray
{
	float			camera_x;
	unsigned int	pos_x;
	unsigned int	pos_y;
	float			dir_x;
	float			dir_y;
	float			step_x;
	float			step_y;
	float			total_x;
	float			total_y;
	float			start_x;
	float			start_y;
	float			fraction;
	float			distance;
	float			door_position;
	short			sign_x;
	short			sign_y;
	bool			hit_type;
	bool			has_door;
}	t_ray;

typedef struct s_colour_construct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_colour_construct;

#endif