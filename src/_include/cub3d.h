/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/26 23:06:35 by simon         #+#    #+#                 */
/*   Updated: 2025/03/17 00:54:20 by simon         ########   odam.nl         */
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

// UI colours 0xAaBbGgRr
# define C_TRANSPARENT		0x00000000
# define C_TRANSLUCENT		0x42000000
# define C_CEILING			0xBB000000
# define C_FLOOR			0x80424242
# define C_WALL				0xFF2A66C0
# define C_DOOR				0xFF153360
# define C_ERROR			0xFF80FF00

// ratio of wall height / width
# define CAMERA_PLANE		1

# define MLX_FONT_WIDTH		10

# define STANDARD_TOKENS	" 01NESW"

// player defaults
# define STARTING_HEALTH	100
# define MOVEMENT_SPEED		6
# define ROTATION_SPEED		3
# define DOOR_SHIFT_SPEED	1
# define INTERACTION_RANGE	2
# define COLLISION_HITBOX	0.2

// weapons? this should obviously go in the .cub file but I don't like parsing
# define G1_MAG_CAPACITY	9
# define G1_SPARE_MAGS		4
# define G1_DAMAGE			12
# define G1_FRAME_RATE		16
# define G1_TEXTURES_PATH	"./data/textures/g1_fri/"

typedef struct s_window
{
	mlx_t				*mlx;
	t_scene				scene;
	t_menu				menu;
	t_hud				hud;
	enum e_window_view	view;
}	t_window;

// gotta love a strict norm to make things more readable
typedef	int	(imgiter_func)(
				mlx_image_t *image, void *param,
				uint32_t x, uint32_t y);

int			image_iteration(
				mlx_image_t *image,
				imgiter_func function,
				void *param);

void		error_exit(mlx_errno_t mlx_errno, int custom_errno, char *message);

//// PHASE 0: initialising mlx window, game, hud and menu
int			init_window(t_window *window);

int			init_game(mlx_t *mlx, t_scene *scene, const char *input_file);
void		read_elements(t_scene *scene, char *const **content);
int			read_tilemap(t_grid *grid, char *const *content);
int			init_doors(t_grid *grid);
int			init_game_images(mlx_t *mlx, t_scene *scene);
int			init_player(t_player *player, t_grid *grid);
int			init_weapon(mlx_t *mlx, t_weapon *weapon);

int			init_hud(mlx_t *mlx, t_hud *hud, t_scene *scene);
int			new_images_minimap(mlx_t *mlx, t_minimap *minimap);
int			new_images_bigmap(mlx_t *mlx, t_bigmap *map, t_scene *scene);

int			init_menu(mlx_t *mlx, t_menu *menu);
int			new_images_menu(mlx_t *mlx, t_menu *menu);
int			new_scaled_image(mlx_t *mlx, t_scalable *dest);
int			sample_scalable(mlx_image_t *dest, void *param, uint32_t img_x, uint32_t img_y);

// MLX_HOOKS
void		frametime_dependant_variables(void *param);
void		view_manager(void *param);
void		window_keyhook(mlx_key_data_t key_data, void *param);

// user inputs
void		wasd_move(mlx_t *mlx, t_scene *scene, t_camera *camera);
void		arrowkey_turn(mlx_t *mlx, t_scene *scene, t_camera *camera);
void		weapon_animation(mlx_t *mlx, t_weapon *weapon);
void		generic_interaction(t_grid *grid, t_camera *camera);
void		operate_door(t_doors *doors, t_camera *camera, unsigned int index);
void		update_doors(t_doors *doors);
void		select_button(t_menu *menu);
void		confirm_selection(t_menu *menu, t_window *window);
void		toggle_maps(t_window *window, t_minimap *minimap, t_bigmap *map);
void		toggle_view(t_window *window);

// tilemap
t_door		*get_door_at(t_doors *doors, unsigned int y, unsigned int x);

// render
void		raycast(t_scene *scene);
void		draw_texture_column(t_ray *ray, t_walls *walls, uint32_t x);

// hud
void		update_minimap(t_minimap *minimap);
void		update_bigmap(t_bigmap *map);

// modlx
xpm_t		*modlx_load_xpm42(const char *path);
int			modlx_put_string(mlx_image_t *strimage, const char* str);
void		reset_image(mlx_image_t *image);

// arithmetic
float		nearest_power_of_2(float value);
float		ft_max_float(float a, float b);
float		ft_min_float(float a, float b);
float		ft_abs_float(float value);
short		ft_sign_float(float value);
int			ft_max_int(int a, int b);
int			ft_min_int(int a, int b);
int			ft_abs_int(int value);
short		ft_sign_int(int value);

// tilemap_cell
int16_t		set_cell(const bool solid, const int id, const char type);
bool		is_solid(const int cell);
bool		is_door(const char type);
char		get_type(const int cell);
int			get_id(const int cell);

// TEST
// void		print_camera(t_camera *camera);
// void		print_ray(t_ray *ray);
// void		print_minimap(t_minimap *minimap);
// void		print_content(char *const *content);
// void		print_bigmap(t_scene *scene);
void		draw_textures(t_window *window);

#endif