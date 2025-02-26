/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/02/26 00:55:41 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"
# include "gamestate.h"

// current window view
enum	e_view
{
	MENU,
	GAME,
	MAP
};

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	uint8_t			*circle_overlay;
	t_scene			*r_scene;
	uint32_t		side;
	uint32_t		radius;
	float			block_size;
	bool			enabled;
}	t_minimap;

typedef struct s_map
{
	mlx_image_t		*walls;
	mlx_image_t		*player;
	t_scene			*r_scene;
	uint32_t		x_offset;
	uint32_t		y_offset;
	float			block_size;
	bool			enabled;
}	t_map;

typedef struct s_scalable
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	float			scale;
}	t_scalable;

typedef struct s_menu
{
	t_scalable		background;
	t_scalable		highlight;
	t_scalable		buttons[2];
	size_t			selection;
	uint32_t		buttons_x_offset;
	uint32_t		buttons_y_offset;
	uint32_t		buttons_y_margin;
}	t_menu;

typedef struct s_fps
{
	mlx_image_t		*image;
	double			cum_time;
	uint32_t		no_frames;
}	t_fps;

typedef struct s_window
{
	mlx_t			*mlx;
	enum e_view		view;
	t_scene			scene;
	t_minimap		minimap;
	t_map			map;
	t_menu			menu;
	t_fps			fps;
}	t_window;

#endif