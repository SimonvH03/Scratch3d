/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_weapon.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/05 23:59:27 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	load_texture(
		mlx_texture_t **dest,
		const char *directory,
		const char *filename)
{
	char	*texture_path;
	char	*temp_free;
	xpm_t	*temp_xpm;

	texture_path = ft_strjoin(directory, filename);
	if (texture_path == NULL)
		return (RETURN_ERROR);
	temp_free = texture_path;
	texture_path = ft_strjoin(texture_path, ".xpm42");
	free(temp_free);
	if (texture_path == NULL)
		return (RETURN_ERROR);
	temp_xpm = mlx_load_xpm42(texture_path);
	free(texture_path);
	if (temp_xpm == NULL)
		*dest = NULL;
	else
		*dest = &temp_xpm->texture;
	return (RETURN_SUCCESS);
}

static int
	load_animation_textures(
		t_weapon *weapon,
		mlx_texture_t ***dest,
		const char *animation_id)
{
	char			*filename;
	char			*temp_free;
	mlx_texture_t	*temp_dest;
	unsigned int	i;
	int				return_value;

	i = 0;
	while (true)
	{
		filename = ft_itoa(i++);
		if (filename == NULL)
			return (RETURN_ERROR);
		temp_free = filename;
		filename = ft_strjoin(animation_id, filename);
		free(temp_free);
		return_value = load_texture(&temp_dest, G1_TEXTURES_PATH, filename);
		free(filename);
		if (return_value != RETURN_SUCCESS)
			return (RETURN_ERROR);
		if (temp_dest == NULL)
			return (RETURN_SUCCESS);
		*dest = (mlx_texture_t **)ft_arrcat((char **)*dest, (char *)temp_dest);
		if (dest == NULL)
			return (RETURN_ERROR);
	}
}

static int
	load_weapon_textures(
		t_weapon *weapon)
{
	if (load_texture(&weapon->rest, G1_TEXTURES_PATH, "0") != RETURN_SUCCESS)
		return (RETURN_ERROR);
	if (load_animation_textures(weapon, &weapon->fire, "f") != RETURN_SUCCESS)
		return (RETURN_ERROR);
	if (load_animation_textures(weapon, &weapon->reload, "r")
		!= RETURN_SUCCESS)
		return (RETURN_ERROR);
	return (RETURN_SUCCESS);
}

int
	init_weapon(
		mlx_t *mlx,
		t_weapon *weapon)
{
	ft_bzero(weapon, sizeof(t_weapon));
	weapon->mag_capacity = G1_MAG_CAPACITY;
	weapon->ammo = weapon->mag_capacity;
	weapon->total_ammo = weapon->ammo * G1_SPARE_MAGS;
	weapon->damage = G1_DAMAGE;
	weapon->frame_index = -1;
	weapon->frame_time_goal = (1 / (float)G1_FRAME_RATE);
	if (load_weapon_textures(weapon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	weapon->scalable.texture = weapon->rest;
	weapon->scalable.scale = mlx->width / (float)weapon->rest->width;
	weapon->scalable.image = mlx_new_image(mlx,
		mlx->width, weapon->rest->height * weapon->scalable.scale);
	if (weapon->scalable.image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, weapon->scalable.image,
		0, mlx->height - weapon->scalable.image->height) < 0)
		return (EXIT_FAILURE);
	image_iteration(weapon->scalable.image, sample_scalable, &weapon->scalable);
	return (RETURN_SUCCESS);
}
