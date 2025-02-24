/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 01:23:08 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "MLX42/MLX42_Int.h"
# include "libft.h"
# include "gamestate.h"
# include "hud.h"
# include "paths.h"
# include "render.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

// mlx window
# define WINDOW_TITLE		"cub3d"
# define WIDTH				1280
# define HEIGHT				720

// colours
# define C_TRANSPARENT		0x00
# define C_TRANSLUCENT		0x42
# define C_CEILING			0x000000BB
# define C_FLOOR			0x42424280
# define C_WALL				0xBF6629FF
# define C_ERROR			0x00FF80FF

// player defaults
# define STARTING_HEALTH	100
# define MOVEMENT_SPEED		6
# define ROTATION_SPEED		3
# define COLLISION_HITBOX	0.3

// ratio of wall height / width
# define CAMERA_PLANE		1

# define VALID_MAP_TOKENS	" 01NESW"

typedef struct s_window
{
	mlx_t			*mlx;
	t_scene			scene;
	t_menu			menu;
	t_hud			hud;
	enum e_view		view;
}	t_window;

// gotta love a strict norm to make things more readable
typedef	int	(imgiter_func)(
				mlx_image_t *image,
				void *param,
				uint32_t x,
				uint32_t y);

int			image_iteration(
				mlx_image_t *image,
				imgiter_func function,
				void *param);

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);
// void		cub3d_terminate(t_window *window);

//// PHASE 0: initialising mlx window, game and hud
int			init_window(t_window *window);

int			init_game(t_scene *scene, const char *input_file);
void		read_elements(t_scene *scene, char *const **content);
int			read_map(t_grid *grid, char *const *content);
int			init_player(t_player *player, t_grid *grid);

int			init_menu(mlx_t *mlx, t_menu *menu);
int			create_menu_images(mlx_t *mlx, t_menu *menu);

int			init_hud(mlx_t *mlx, t_hud *hud, t_scene *scene);
int			new_images_minimap(mlx_t *mlx, t_minimap *minimap,
				mlx_texture_t *ohijustlovemakingmycodereadablewiththeholynorm);
int			new_images_bigmap(mlx_t *mlx, t_bigmap *map, t_camera *camera);



int			init_game_images(mlx_t *mlx, t_scene *scene);
void		draw_minimap_circle_overlay(t_minimap *minimap);
void		draw_bigmap_walls(t_bigmap *map, t_grid *grid);

int			init_menu_structs(mlx_t *mlx, t_menu *menu);
void		draw_scaled_image(t_scalable *scalable);

// interpretation of user inputs
void		view_manager(void *param);
void		window_keyhook(mlx_key_data_t key_data, void *param);
void		wasd_move(t_window *window, t_camera *camera);
void		arrowkey_turn(t_window *window, t_camera *camera);
void		select_button(t_menu *menu);
void		confirm_selection(t_menu *menu, t_window *window);
void		toggle_maps(t_minimap *minimap, t_bigmap *map);
void		toggle_view(t_window *window);

// frame processing
void		draw_raycast(t_scene *scene);
void		draw_texture_column(t_scene *scene, t_ray *ray, uint32_t x);
void		draw_minimap_walls(t_minimap *minimap);
void		draw_bigmap_player(t_bigmap *map);

// arithmetic
float		ft_max_float(float a, float b);
float		ft_min_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);

// modlx
xpm_t		*modlx_load_xpm42(const char *path);
void		reset_image(mlx_image_t *image);

// TEST
// void		print_camera(t_camera *camera);
// void		print_ray(t_ray *ray);
// void		print_minimap(t_minimap *minimap);
void		print_content(char *const *content);
// void		print_bigmap(t_scene *scene);
// void		draw_textures(t_window *window);

#endif