/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 03:04:25 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H
# include "MLX42/MLX42_Int.h"
# include "gamestate.h"

// current window view
enum	e_view
{
	MENU,
	GAME,
	MAP
};

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

typedef struct s_minimap
{
	mlx_image_t		*walls;
	mlx_image_t		*player_icon;
	uint8_t			*circle_overlay;
	t_grid			*r_grid;
	t_camera		*r_camera;
	uint32_t		side;
	uint32_t		radius;
	float			block_size;
	bool			enabled;
}	t_minimap;

typedef struct s_bigmap
{
	mlx_image_t		*walls;
	mlx_image_t		*player_icon;
	mlx_texture_t	*r_player_tex;
	t_grid			*r_grid;
	t_camera		*r_camera;
	uint32_t		x_offset;
	uint32_t		y_offset;
	float			block_size;
	bool			enabled;
}	t_bigmap;

typedef struct s_hud
{
	mlx_texture_t	*player_icon;
	mlx_image_t		*weapon;
	mlx_image_t		*ammo;
	mlx_image_t		*healthbar;
	mlx_image_t		*treasure;
	mlx_image_t		*fps;
	t_bigmap		bigmap;
	t_minimap		minimap;
}	t_hud;

#endif