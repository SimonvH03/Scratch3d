/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_weapon.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/05 00:25:08 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void
    init_weapon_state(
        t_scene *scene)
{
	int i = 0;
	while (i < 34)
	{
		scene->weapon.textures[i] = NULL;
		i++;
	}

	scene->weapon.current_frame = 0;
	scene->weapon.enabled = true;
	scene->weapon.scale = 1.0;
	scene->weapon.is_animating = false;
	scene->weapon.is_reloading = false;
	scene->weapon.frame_time = 0.0f;
	scene->weapon.frame_delay = 0.05f;
	scene->weapon.ammo_count = MAX_AMMO;
}

static char *
	create_texture_path(
		int index)
{
	char	*texture_path;
	char	*temp;
	char	*number;

	number = ft_itoa(index + 1);
	if (!number)
		return (NULL);
	if (ft_strlen(number) == 1)
		texture_path = ft_strjoin("scenes/textures/g1/0", number);
	else
		texture_path = ft_strjoin("scenes/textures/g1/", number);
	free(number);
	if (!texture_path)
		return (NULL);
	temp = texture_path;
	texture_path = ft_strjoin(texture_path, ".xpm42");
	free(temp);
	return (texture_path);
}

static short
	load_single_texture(
		t_scene *scene,
		int index)
{
	char	*texture_path;
	xpm_t   *weapon_xpm;

	texture_path = create_texture_path(index);
	if (!texture_path)
		return (EXIT_FAILURE);
	weapon_xpm = mlx_load_xpm42(texture_path);
	free(texture_path);
	if (!weapon_xpm)
		return (EXIT_FAILURE);
	scene->weapon.textures[index] = &weapon_xpm->texture;
	return (EXIT_SUCCESS);
}

static short
	load_weapon_textures(
		t_scene *scene)
{
	int	 i;

	i = 0;
	while (i < 34)
	{
		if (load_single_texture(scene, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	scene->weapon.texture = scene->weapon.textures[0];
	return (EXIT_SUCCESS);
}

static short
	create_weapon_image(
		mlx_t *mlx,
		t_scene *scene)
{
	scene->weapon.image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!scene->weapon.image)
		return (EXIT_FAILURE);
	scene->weapon.x_pos = 0;
	scene->weapon.y_pos = 0;

	if (mlx_image_to_window(mlx, scene->weapon.image,
		scene->weapon.x_pos, scene->weapon.y_pos) < 0)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

short
	init_weapon(
		mlx_t *mlx,
		t_scene *scene)
{
	init_weapon_state(scene);
	if (load_weapon_textures(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_weapon_image(mlx, scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int
	init_frame_textures()
{
	return (RETURN_SUCCESS);
}

int
	init_weapon(
		t_weapon *weapon)
{
	ft_bzero(weapon, sizeof(t_weapon));
	weapon->ammo = G1_MAG_CAPACITY;
	weapon->total_ammo = weapon->ammo * G1_SPARE_MAGS;
	weapon->damage = G1_DAMAGE;
	weapon->frame_time_goal = (float)(1 / G1_FRAME_RATE);
	if (init_frame_textures() != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
