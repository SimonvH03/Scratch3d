/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/02/26 01:01:31 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "gamestate.h"
# include "hud.h"
# include "paths.h"
# include "render.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

// mlx window
# define WINDOW_TITLE "cub3d"
# define WIDTH				1280
# define HEIGHT				720

// colours
# define C_TRANSPARENT		0x00
# define C_TRANSLUCENT		0x42
# define C_CEILING			0x000000BB
# define C_FLOOR			0x42424280
# define C_WALL				0xBF6629FF
# define C_ERROR			0x00FF80FF

// camera defaults
# define MOVEMENT_SPEED		6
# define ROTATION_SPEED		3
# define COLLISION_HITBOX	0.3
// ratio of cube height / width
# define CAMERA_PLANE		1


typedef void	(mlx_hook)(void *);
typedef void	(mlx_key)(struct mlx_key_data, void *);
typedef void	(mlx_close)(void *);
typedef void	(mlx_mouse)(mouse_key_t, action_t, modifier_key_t, void *);
typedef void	(mlx_cursor)(double, double, void *);
typedef void	(mlx_resize)(uint32_t, uint32_t, void *);
typedef void	(mlx_scroll)(double, double, void *);

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);
void		cub3d_terminate(t_window *window);

//// PHASE 0: initialising mlx window, scene and camera
short		window_init(t_window *window);

short		init_game_structs(mlx_t *mlx, t_window *window, char *argv_scene);
short		get_content(t_scene *scene);
void		read_elements(t_scene *scene);
short		read_map(t_scene *scene);

short		init_game_images(mlx_t *mlx, t_window *window);
void		draw_scene_background(t_scene *scene);
void		draw_minimap_circle_overlay(t_minimap *minimap);
void		draw_map_walls(t_map *map);

short		init_menu_structs(mlx_t *mlx, t_menu *menu);
short		init_menu_images(mlx_t *mlx, t_menu *menu);
void		draw_scaled_image(t_scalable *scalable);
// void		draw_menu_highlight(mlx_image_t *image);

// interpretation of user inputs
mlx_key		window_keyhook;
mlx_hook	view_manager;
void		wasd_move(t_window *window, t_camera *camera);
void		arrowkey_turn(t_window *window, t_camera *camera);
void		up_down_select(t_menu *menu);
void		confirm_selection(t_menu *menu, t_window *window);
void		toggle_maps(t_minimap *minimap, t_map *map);
void		toggle_view(t_window *window);

// frame processing
void		draw_raycast(t_scene *scene);
void		draw_texture_column(t_scene *scene, t_ray *ray, uint32_t x);
void		draw_minimap_walls(t_minimap *minimap);
void		draw_map_player(t_map *map);
// arithmetic
float		ft_max_float(float a, float b);
float		ft_min_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
// modlx
int			modlx_put_string(mlx_image_t *strimage, const char* str);
void		reset_image(mlx_image_t *image);

// TEST
// void		print_camera(t_camera *camera);
// void		print_ray(t_ray *ray);
// void		print_minimap(t_minimap *minimap);
// void		print_content(t_scene *scene);
// void		print_map(t_scene *scene);
// void		draw_textures(t_window *window);

#endif